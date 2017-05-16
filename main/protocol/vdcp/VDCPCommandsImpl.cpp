/*
* Copyright (c) 2011 Sveriges Television AB <info@casparcg.com>
*
* This file is part of CasparCG (www.casparcg.com).
*
* CasparCG is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CasparCG is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CasparCG. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Nicklas P Andersson
*/

#include "../StdAfx.h"

#if defined(_MSC_VER)
#pragma warning (push, 1) // TODO: Legacy code, just disable warnings
#endif

#include "VDCPCommandsImpl.h"

#include "vdcp_command_repository.h"
#include "VDCPCommandQueue.h"

#include <common/env.h>

#include <common/log.h>
#include <common/param.h>
#include <common/os/system_info.h>
#include <common/os/filesystem.h>
#include <common/base64.h>
#include <common/thread_info.h>
#include <common/filesystem.h>

#include <core/producer/cg_proxy.h>
#include <core/producer/frame_producer.h>
#include <core/help/help_repository.h>
#include <core/help/help_sink.h>
#include <core/help/util.h>
#include <core/video_format.h>
#include <core/producer/transition/transition_producer.h>
#include <core/frame/audio_channel_layout.h>
#include <core/frame/frame_transform.h>
#include <core/producer/text/text_producer.h>
#include <core/producer/stage.h>
#include <core/producer/layer.h>
#include <core/mixer/mixer.h>
#include <core/consumer/output.h>
#include <core/thumbnail_generator.h>
#include <core/producer/media_info/media_info.h>
#include <core/producer/media_info/media_info_repository.h>
#include <core/diagnostics/call_context.h>
#include <core/diagnostics/osd_graph.h>
#include <core/system_info_provider.h>

#include <algorithm>
#include <locale>
#include <fstream>
#include <memory>
#include <cctype>
#include <future>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/regex.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/locale.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include <tbb/concurrent_unordered_map.h>

/* Return codes

102 [action]			Information that [action] has happened
101 [action]			Information that [action] has happened plus one row of data  

202 [command] OK		[command] has been executed
201 [command] OK		[command] has been executed, plus one row of data  
200 [command] OK		[command] has been executed, plus multiple lines of data. ends with an empty line

400 ERROR				the command could not be understood
401 [command] ERROR		invalid/missing channel
402 [command] ERROR		parameter missing
403 [command] ERROR		invalid parameter  
404 [command] ERROR		file not found

500 FAILED				internal error
501 [command] FAILED	internal error
502 [command] FAILED	could not read file
503 [command] FAILED	access denied

600 [command] FAILED	[command] not implemented
*/

namespace caspar { namespace protocol { namespace vdcp {

using namespace core;
//IDLIST
std::list<std::wstring> IDvector;
std::wstring read_file_base64(const boost::filesystem::path& file)
{
	using namespace boost::archive::iterators;

	boost::filesystem::ifstream filestream(file, std::ios::binary);

	if (!filestream)
		return L"";

	auto length = boost::filesystem::file_size(file);
	std::vector<char> bytes;
	bytes.resize(length);
	filestream.read(bytes.data(), length);

	std::string result(to_base64(bytes.data(), length));
	return std::wstring(result.begin(), result.end());
}

std::wstring read_utf8_file(const boost::filesystem::path& file)
{
	std::wstringstream result;
	boost::filesystem::wifstream filestream(file);

	if (filestream) 
	{
		// Consume BOM first
		filestream.get();
		// read all data
		result << filestream.rdbuf();
	}

	return result.str();
}

std::wstring read_latin1_file(const boost::filesystem::path& file)
{
	boost::locale::generator gen;
	gen.locale_cache_enabled(true);
	gen.categories(boost::locale::codepage_facet);

	std::stringstream result_stream;
	boost::filesystem::ifstream filestream(file);
	filestream.imbue(gen("en_US.ISO8859-1"));

	if (filestream)
	{
		// read all data
		result_stream << filestream.rdbuf();
	}

	std::string result = result_stream.str();
	std::wstring widened_result;

	// The first 255 codepoints in unicode is the same as in latin1
	boost::copy(
		result | boost::adaptors::transformed(
				[](char c) { return static_cast<unsigned char>(c); }),
		std::back_inserter(widened_result));

	return widened_result;
}

std::wstring read_file(const boost::filesystem::path& file)
{
	static const uint8_t BOM[] = {0xef, 0xbb, 0xbf};

	if (!boost::filesystem::exists(file))
	{
		return L"";
	}

	if (boost::filesystem::file_size(file) >= 3)
	{
		boost::filesystem::ifstream bom_stream(file);

		char header[3];
		bom_stream.read(header, 3);
		bom_stream.close();

		if (std::memcmp(BOM, header, 3) == 0)
			return read_utf8_file(file);
	}

	return read_latin1_file(file);
}

std::wstring MediaInfo(const boost::filesystem::path& path, const spl::shared_ptr<media_info_repository>& media_info_repo)
{
	if (!boost::filesystem::is_regular_file(path))
		return L"";

	auto media_info = media_info_repo->get(path.wstring());

	if (!media_info)
		return L"";

	//auto is_not_digit = [](char c){ return std::isdigit(c) == 0; };

	auto writeTimeStr = boost::posix_time::to_iso_string(boost::posix_time::from_time_t(boost::filesystem::last_write_time(path)));
	writeTimeStr.erase(std::remove_if(writeTimeStr.begin(), writeTimeStr.end(), [](char c) { return std::isdigit(c) == 0; }), writeTimeStr.end());
	auto writeTimeWStr = std::wstring(writeTimeStr.begin(), writeTimeStr.end());

	auto sizeStr = boost::lexical_cast<std::wstring>(boost::filesystem::file_size(path));
	sizeStr.erase(std::remove_if(sizeStr.begin(), sizeStr.end(), [](wchar_t c) { return std::iswdigit(c) == 0; }), sizeStr.end());
	auto sizeWStr = std::wstring(sizeStr.begin(), sizeStr.end());

	auto relativePath = get_relative_without_extension(path, env::media_folder());
	auto str = relativePath.generic_wstring();

	if (str[0] == '\\' || str[0] == '/')
		str = std::wstring(str.begin() + 1, str.end());

	return std::wstring()
		+ L"\"" + str +
		+ L"\" " + media_info->clip_type +
		+ L" " + sizeStr +
		+ L" " + writeTimeWStr +
		+ L" " + boost::lexical_cast<std::wstring>(media_info->duration) +
		+ L" " + boost::lexical_cast<std::wstring>(media_info->time_base.numerator()) + L"/" + boost::lexical_cast<std::wstring>(media_info->time_base.denominator())
		+ L"\r\n";
}

std::wstring ListMedia(const spl::shared_ptr<media_info_repository>& media_info_repo)
{	
	std::wstringstream replyString;
	for (boost::filesystem::recursive_directory_iterator itr(env::media_folder()), end; itr != end; ++itr)
		replyString << MediaInfo(itr->path(), media_info_repo);
	
	return boost::to_upper_copy(replyString.str());
}

std::wstring ListTemplates(const spl::shared_ptr<core::cg_producer_registry>& cg_registry)
{
	std::wstringstream replyString;

	for (boost::filesystem::recursive_directory_iterator itr(env::template_folder()), end; itr != end; ++itr)
	{		
		if(boost::filesystem::is_regular_file(itr->path()) && cg_registry->is_cg_extension(itr->path().extension().wstring()))
		{
			auto relativePath = get_relative_without_extension(itr->path(), env::template_folder());

			auto writeTimeStr = boost::posix_time::to_iso_string(boost::posix_time::from_time_t(boost::filesystem::last_write_time(itr->path())));
			writeTimeStr.erase(std::remove_if(writeTimeStr.begin(), writeTimeStr.end(), [](char c){ return std::isdigit(c) == 0;}), writeTimeStr.end());
			auto writeTimeWStr = std::wstring(writeTimeStr.begin(), writeTimeStr.end());

			auto sizeStr = boost::lexical_cast<std::string>(boost::filesystem::file_size(itr->path()));
			sizeStr.erase(std::remove_if(sizeStr.begin(), sizeStr.end(), [](char c){ return std::isdigit(c) == 0;}), sizeStr.end());

			auto sizeWStr = std::wstring(sizeStr.begin(), sizeStr.end());

			auto dir = relativePath.parent_path();
			auto file = boost::to_upper_copy(relativePath.filename().wstring());
			relativePath = dir / file;
						
			auto str = relativePath.generic_wstring();
			boost::trim_if(str, boost::is_any_of("\\/"));

			auto template_type = cg_registry->get_cg_producer_name(str);

			replyString << L"\"" << str
						<< L"\" " << sizeWStr
						<< L" " << writeTimeWStr
						<< L" " << template_type
						<< L"\r\n";
		}
	}
	return replyString.str();
}

core::frame_producer_dependencies get_producer_dependencies(const std::shared_ptr<core::video_channel>& channel, const command_context& ctx)
{
	return core::frame_producer_dependencies(
			channel->frame_factory(),
			cpplinq::from(ctx.channels)
					.select([](channel_context c) { return spl::make_shared_ptr(c.channel); })
					.to_vector(),
			channel->video_format_desc(),
			ctx.producer_registry);
}

// Basic Commands
void vdcp_describer(core::help_sink& sink, const core::help_repository& repository)
{
	/*sink.short_description(L"Play a media file or resource.");
	sink.syntax(LR"(PLAY [video_channel:int]{-[layer:int]|-0} {[clip:string]} {"additional parameters"})");
	sink.para()
		->text(L"Moves clip from background to foreground and starts playing it. If a transition (see ")->see(L"LOADBG")
		->text(L") is prepared, it will be executed.");
	sink.para()
		->text(L"If additional parameters (see ")->see(L"LOADBG")
		->text(L") are provided then the provided clip will first be loaded to the background.");
	sink.para()->text(L"Examples:");
	sink.example(L">> PLAY 1 MY_FILE PUSH 20 EASEINSINE");
	sink.example(L">> PLAY 1-1 MY_FILE SLIDE 10 LEFT");
	sink.example(L">> PLAY 1-0 MY_FILE");
	sink.para()->text(L"Note: See ")->see(L"LOADBG")->text(L" for additional details.");*/
}
std::wstring  ack_command(command_context& ctx)
{
	return L"04";
}
std::wstring  nak_command(command_context& ctx)
{
	return L"05";
}
std::wstring  openport_command(command_context& ctx)
{
	std::wstring message = ctx.parameters[0];
	std::wstring sendmessage;
	sendmessage.append(L"02");
	sendmessage.append(L"03");
	sendmessage.append(message.substr(4, 2));
	sendmessage.append(L"81");
	sendmessage.append(L"01");

	wchar_t buf[10] = { 0 };
	
	unsigned Sum = 0x81 + 0x01 + boost::lexical_cast<HexTo<int>>(message.substr(4, 2));
	Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
	if (Sum > 0x0f)
		swprintf(buf, 2, L"%2x", (unsigned char)Sum);
	else
		swprintf(buf, 2, L"0%x", (unsigned char)Sum);
	sendmessage.append(buf);//校验合
	return sendmessage;
}
std::wstring  idlist_command(command_context& ctx)
{

	std::wstring sendmessage;
	std::wstring message = ctx.parameters[0];
	IDvector.clear();
	std::wstring mediaarry = ListMedia(ctx.media_info_repo);

	std::vector<std::wstring> tokens;
	boost::split(tokens, mediaarry, boost::is_any_of(L"\r\n"));
	for (int i =0;i<tokens.size();i++)
	{
		std::wstring express_string = tokens[i];
		std::vector<std::wstring> sdv;
		boost::split(sdv, express_string, boost::is_any_of(L"\""));
		if (sdv.size() > 2)
			IDvector.push_back(sdv[1]);
	}
	int Count = 0;
	int relen = 0;
	std::list<std::wstring>file_vec;
	std::list<std::wstring>::iterator its = IDvector.begin();
	std::list<std::wstring>::iterator itnext;

	for (; ;)
	{
		if (its != IDvector.end()) {
			itnext = its;
			itnext++;
			//判断新老协议
			if (boost::lexical_cast<HexTo<int>>(message.substr(4,2))== 0x30)
			{

				if ((*its).size() == 8)	   //文件名长度大于8的话，这个文件不要了
				{
					if (Count == 10)
						break;
					file_vec.push_back(*its);
					Count++;
				}
			}

			else
			{
				if (Count == 10)
					break;
				wchar_t buff[2] = { 0 };
				swprintf(buff, 1, L"%c", (unsigned char)(*its).size());
				std::wstring s = buff;
				s.append(*its);
				relen += s.size();
				if (relen > 100)
					break;
				file_vec.push_back(s);
				if ((*its) == L"N" || (*its) == L"n")
					CASPAR_LOG(info) << L"exist n in file";
				Count++;
			}

			IDvector.erase(its);
			its = itnext;

		}
		else
			break;
	}
	
	wchar_t buf[20] = { 0 };
	if (!file_vec.empty())
	{
		int datalen = 4;
		std::wstring filearry;
		for (itnext = file_vec.begin(); itnext != file_vec.end(); itnext++)
		{
			std::wstring sd = L"";
			for (int i = 0;i < itnext->size();i ++)
			{
				wchar_t b8[10] = { 0 };
				if (itnext->at(i) > 0x0f)
					swprintf(b8, 2, L"%2x", itnext->at(i));
				else
					swprintf(b8, 2, L"0%x", itnext->at(i));
				sd.append(b8);
			}
			filearry.append(sd);
			datalen += itnext->size();
		}
		if (datalen > 0x0f)
			swprintf(buf, 2, L"%2x", datalen);
		else
			swprintf(buf, 2, L"0%x", datalen);

		sendmessage.append(L"02");	
		sendmessage.append(buf);//字节大小/2
		sendmessage.append(message.substr(4, 2));
		sendmessage.append(L"91");
		sendmessage.append(L"00");
		sendmessage.append(L"02");
		sendmessage.append(filearry);
		unsigned  Sum = 0;
		for (size_t i = 4; i <sendmessage.size(); i+=2)
		{
			int s = boost::lexical_cast<HexTo<int>>(sendmessage.substr(i, 2));
			Sum += s;
		}
		Sum = Sum & 0xFF;

		Sum = (unsigned char)((~Sum) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);
	}
	else
	{
		sendmessage.append(L"0204");
		sendmessage.append(message.substr(4, 2));
		sendmessage.append(L"9100");
		unsigned char Sum = 0x91 + boost::lexical_cast<HexTo<int>>(message.substr(4, 2));

		Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);//校验合
	}
	return sendmessage;
}
std::wstring  nextdata_command(command_context& ctx)
{
	std::wstring sendmessage;
	std::wstring message = ctx.parameters[0];

	int Count = 0;
	int relen = 0;
	std::list<std::wstring>file_vec;
	std::list<std::wstring>::iterator its = IDvector.begin();
	std::list<std::wstring>::iterator itnext;

	for (; ;)
	{
		if (its != IDvector.end()) {
			itnext = its;
			itnext++;
			//判断新老协议
			if (boost::lexical_cast<HexTo<int>>(message.substr(4, 2)) == 0x30)
			{

				if ((*its).size() ==8)	   //文件名长度大于8的话，这个文件不要了
				{
					if (Count == 10)
						break;
					file_vec.push_back(*its);
					Count++;
				}
			}
			else
			{
				if (Count == 10)
					break;
				wchar_t buff[2] = { 0 };
				swprintf(buff, 1, L"%c", static_cast<int>((*its).size()));
				std::wstring s = buff;
				s.append(*its);
				relen += s.size();
				if (relen > 100)
					break;
				file_vec.push_back(s);
				if ((*its) == L"N" || (*its) == L"n")
					CASPAR_LOG(info) << L"exist n in file";
				Count++;
			}

			IDvector.erase(its);
			its = itnext;

		}
		else
			break;
	}
	wchar_t buf[20] = { 0 };
	if (!file_vec.empty())
	{
		int datalen = 4;
		std::wstring filearry;
		for (itnext = file_vec.begin(); itnext != file_vec.end(); itnext++)
		{
			std::wstring sd = L"";
			for (int i = 0;i < itnext->size();i++)
			{
				wchar_t b8[10] = { 0 };
				if (itnext->at(i) > 0x0f)
					swprintf(b8, 2, L"%2x", itnext->at(i));
				else
					swprintf(b8, 2, L"0%x", itnext->at(i));
				sd.append(b8);
			}
			filearry.append(sd);
			datalen += itnext->size();
		}
		if (datalen > 0x0f)
			swprintf(buf, 2, L"%2x", datalen);
		else
			swprintf(buf, 2, L"0%x", datalen);

		sendmessage.append(L"02");
		sendmessage.append(buf);//字节大小/2
		sendmessage.append(message.substr(4, 2));
		sendmessage.append(L"82");
		sendmessage.append(L"00");
		sendmessage.append(L"02");
		sendmessage.append(filearry);
		unsigned  Sum = 0;
		for (size_t i = 4; i < sendmessage.size(); i += 2)
		{
			Sum += boost::lexical_cast<HexTo<int>>(sendmessage.substr(i, 2));
		}
		Sum = Sum & 0xFF;

		Sum = (char)((~Sum) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);
	}
	else
	{
		sendmessage.append(L"0204");
		sendmessage.append(message.substr(4, 2));
		sendmessage.append(L"820000");
		unsigned char Sum = 0x82 + boost::lexical_cast<HexTo<int>>(message.substr(4, 2));

		Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);//校验合
	}
	return sendmessage;
}
std::wstring  portstatus_command(command_context& ctx)
{
	std::wstring sendmessage;
	if (ctx.parameters.size()!=2)
	{
		return nak_command(ctx);
	}
	if (ctx.parameters[0].empty()||ctx.parameters[1].empty())
	{
		return nak_command(ctx);
	}
	std::wstring openportmessage = ctx.parameters[0];
	std::wstring message_current = ctx.parameters[1];
	int nret = ctx.channel.channel->stage().get_layerstatus(ctx.layer_index());
	int port=(unsigned char)boost::lexical_cast<HexTo<int>>(openportmessage.substr(8, 2));
	
	int statustype = boost::lexical_cast<HexTo<int>>(message_current.substr(8, 2));
	wchar_t buf[10] = { 0 };
	if (statustype == VDCP_PS_STATE)
	{
		sendmessage.append(L"02"); // RET
		sendmessage.append(L"05"); //长度
		sendmessage.append(message_current.substr(4, 2)); // 原始的命令字如B0
		sendmessage.append(L"85");//反馈的命令码
		sendmessage.append(L"01");//查询的状态命令字
		if (nret>0x0f)
			swprintf(buf, 2, L"%2x", (unsigned int)nret);
		else
			swprintf(buf, 2, L"0%x",(unsigned int)nret);
		sendmessage.append(buf);//状态吗
		sendmessage.append(openportmessage.substr(8, 2));//打开的端口
		unsigned Sum = 0x85 + 0x01 + nret + port + boost::lexical_cast<HexTo<int>>(message_current.substr(4, 2));
			Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);//校验合
	}
	else if (statustype == VDCP_PS_MEDIA_STATUS||statustype == VDCP_PS_SETTING)
	{
		//暂时还没有返回值，先弄成假数据
		sendmessage.append(L"02"); // RET
		sendmessage.append(L"04"); //参数长度
		sendmessage.append(message_current.substr(4, 2)); // 原始的命令字如B0
		sendmessage.append(L"85");//反馈的命令码 
		if (statustype > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned int)statustype);
		else
			swprintf(buf, 2, L"0%x", (unsigned int)statustype);
		sendmessage.append(buf);
		sendmessage.append(L"0000");
		sendmessage.append(openportmessage.substr(4, 2));//打开的端口
		unsigned Sum = 0x85 + statustype + boost::lexical_cast<HexTo<int>>(message_current.substr(4, 2));
			Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);//校验合
	}
	else if (statustype == VDCP_PS_ERRORS)
	{
		sendmessage.append(L"02");//rek
		sendmessage.append(L"06");//len
		sendmessage.append(message_current.substr(4, 2));//
		sendmessage.append(L"85");//commandcode
		sendmessage.append(L"040000");//VDCP_PS_ERRORS
		if (nret > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned int)nret);
		else
			swprintf(buf, 2, L"0%x", (unsigned int)nret);
		sendmessage.append(buf);//状态吗
		unsigned Sum = 0x85 + statustype + boost::lexical_cast<HexTo<int>>(message_current.substr(4, 2));
		Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);//校验合
	}
	else if (statustype == VDCP_PS_COMPRESSION_TYPE)
	{
		return ack_command(ctx);
	}
	else if (statustype == VDCP_PS_STATEEX)	   //组合命令，查前四种状态，但是setting还不支持，不返回任何码字
	{
		sendmessage.append(L"020A");
		sendmessage.append(message_current.substr(4, 2));
		sendmessage.append(L"85");
		sendmessage.append(L"0F");
		if (nret > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned int)nret);
		else
			swprintf(buf, 2, L"0%x", (unsigned int)nret);
		sendmessage.append(buf);//状态吗
		sendmessage.append(openportmessage.substr(8, 2));//打开的端口
		sendmessage.append(L"00000000");
		if (nret > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned int)nret);
		else
			swprintf(buf, 2, L"0%x", (unsigned int)nret);
		sendmessage.append(buf);//状态

		unsigned Sum = 0x85+0x0f + nret+nret+port + boost::lexical_cast<HexTo<int>>(message_current.substr(4, 2));
		Sum = (unsigned char)(~(Sum & 0xFF) + 0x01);
		if (Sum > 0x0f)
			swprintf(buf, 2, L"%2x", (unsigned char)Sum);
		else
			swprintf(buf, 2, L"0%x", (unsigned char)Sum);
		sendmessage.append(buf);//校验合
	}

	return sendmessage;
}
void cinf_describer(core::help_sink& sink, const core::help_repository& repo)
{
	sink.short_description(L"Get information about a media file.");
	sink.syntax(L"CINF [filename:string]");
	sink.para()->text(L"Returns information about a media file.");
}

std::wstring cinf_command(command_context& ctx)//文件大小
{
	std::wstring sendmessage;
	std::wstring filename_hex;
	std::wstring message = ctx.parameters[0];
	wchar_t buf[20] = { 0 };
	if (boost::iequals(message.substr(4, 2), L"b0"))//新协议
	{
		int flen = boost::lexical_cast<HexTo<int>>(message.substr(8, 2)) * 2;
		filename_hex = message.substr(10, flen);
	}
	else
		filename_hex = message.substr(8, 16);
	std::wstring realname;
	for (int i = 0;i < filename_hex.size();i+=2)
	{
		realname.push_back(boost::lexical_cast<HexTo<int>>(filename_hex.substr(i, 2)));
	}

	std::wstring info;
	for (boost::filesystem::recursive_directory_iterator itr(env::media_folder()), end; itr != end && info.empty(); ++itr)
	{
		auto path = itr->path();
		auto file = path.replace_extension(L"").filename().wstring();
		if (boost::iequals(file, realname))
			info += MediaInfo(itr->path(), ctx.media_info_repo);
	}
	
	if (info.empty())
	{
		//CASPAR_THROW_EXCEPTION(file_not_found());
		//时间为0
		goto err;
	}
	else
	{
		//解析时间
		std::vector<std::wstring> tokens;
		boost::split(tokens,info,boost::is_any_of(L" "));
		if (tokens.size() != 6)
		{
			goto err;
		}
		else
		{
			sendmessage.append(L"02");
			sendmessage.append(L"06");//字节大小/2
			sendmessage.append(message.substr(4, 2));
			sendmessage.append(L"94");
			int sumframe = boost::lexical_cast<int>(tokens[4]);
			std::vector<std::wstring> lrd;
			boost::split(lrd, tokens[5], boost::is_any_of(L"/"));
			if (lrd.size()!=2)
			{
				goto err;
			}
			int frameL = boost::lexical_cast<int>(lrd[0]);
			int frameR = boost::lexical_cast<int>(lrd[1]);
			int ff = sumframe*frameL %frameR;
			
			int sumseconds = sumframe*frameL / frameR;
			int hour = sumseconds / 3600;
			int min = sumseconds % 3600 / 60;
			int second = sumseconds % 3600 % 60;
			std::wstring secondstr = boost::lexical_cast<std::wstring>(second);
			
			if (ff > 9)
			{
				swprintf(buf, 2, L"%d", ff);
			}
			else
				swprintf(buf, 2, L"0%d", ff);
			sendmessage.append(buf);
			if (second > 9)
			{
				swprintf(buf, 2, L"%d", second);
			}
			else
				swprintf(buf, 2, L"0%d", second);
			sendmessage.append(buf);
			if (min > 9)
			{
				swprintf(buf, 2, L"%d", min);
			}
			else
				swprintf(buf, 2, L"0%d", min);
			sendmessage.append(buf);
			if (hour > 9)
			{
				swprintf(buf, 2, L"%d", hour);
			}
			else
				swprintf(buf, 2, L"0%d", hour);
			sendmessage.append(buf);
			goto sus;
		}

		
	}
err:
	sendmessage.clear();
	sendmessage.append(L"02");
	sendmessage.append(L"06");//字节大小/2
	sendmessage.append(message.substr(4, 2));
	sendmessage.append(L"9400000000");
sus:
	unsigned Sum = 0;
	for (size_t i = 4; i < sendmessage.size(); i += 2)
	{
		int s = boost::lexical_cast<HexTo<int>>(sendmessage.substr(i, 2));
		Sum += s;
	}
	Sum = Sum & 0xFF;

	Sum = (unsigned char)((~Sum) + 0x01);
	if (Sum > 0x0f)
		swprintf(buf, 2, L"%2x", (unsigned char)Sum);
	else
		swprintf(buf, 2, L"0%x", (unsigned char)Sum);
	sendmessage.append(buf);
	return sendmessage;
}
std::wstring idexist_command(command_context& ctx)//文件大小
{
	std::wstring sendmessage;
	std::wstring filename_hex;
	std::wstring message = ctx.parameters[0];
	wchar_t buf[20] = { 0 };
	if (boost::iequals(message.substr(4, 2), L"b0"))//新协议
	{
		int flen = boost::lexical_cast<HexTo<int>>(message.substr(8, 2)) * 2;
		filename_hex = message.substr(10, flen);
	}
	else
		filename_hex = message.substr(8, 16);
	std::wstring realname;
	for (int i = 0;i < filename_hex.size();i += 2)
	{
		realname.push_back(boost::lexical_cast<HexTo<int>>(filename_hex.substr(i, 2)));
	}

	std::wstring info;
	for (boost::filesystem::recursive_directory_iterator itr(env::media_folder()), end; itr != end && info.empty(); ++itr)
	{
		auto path = itr->path();
		auto file = path.replace_extension(L"").filename().wstring();
		if (boost::iequals(file, realname))
			info += MediaInfo(itr->path(), ctx.media_info_repo);
	}

	if (info.empty())
	{
		sendmessage.append(L"0205");
		sendmessage.append(message.substr(4, 2));
		sendmessage.append(L"96000000");
	}
	else
	{
		sendmessage.append(L"0205");
		sendmessage.append(message.substr(4,2));
		sendmessage.append(L"96010000");
	}
	unsigned Sum = 0;
	for (size_t i = 4; i < sendmessage.size(); i += 2)
	{
		int s = boost::lexical_cast<HexTo<int>>(sendmessage.substr(i, 2));
		Sum += s;
	}
	Sum = Sum & 0xFF;

	Sum = (unsigned char)((~Sum) + 0x01);
	if (Sum > 0x0f)
		swprintf(buf, 2, L"%2x", (unsigned char)Sum);
	else
		swprintf(buf, 2, L"0%x", (unsigned char)Sum);
	sendmessage.append(buf);
	return sendmessage;
}


std::wstring cuedata_command(command_context& ctx)
{
	//提取文件名和时间
	std::wstring filename_hex;
	std::wstring stime_str;
	std::wstring etime_str;
	std::wstring message = ctx.parameters[0];
	if (boost::lexical_cast<HexTo<int>>(message.substr(4, 2)) > 0x80)//新协议
	{
		int lens = boost::lexical_cast<HexTo<int>>(message.substr(8, 2)) * 2;
		filename_hex = message.substr(10, lens);
		stime_str = message.substr(10+lens, 8);
		etime_str = message.substr(lens+18, 8);

	}
	else
	{
		filename_hex = message.substr(8, 16);
		stime_str = message.substr(24, 8);
		etime_str = message.substr(32, 8);
	}

	std::wstring realname;
	for (int i = 0;i < filename_hex.size();i += 2)
	{
		realname.push_back(boost::lexical_cast<HexTo<int>>(filename_hex.substr(i, 2)));
	}

	//重置参数
	ctx.parameters.clear();
	ctx.parameters.push_back(realname);

	int startframe = 0;
	int endframe = 0;
	std::wstring parameterstr;
	int fframe = boost::lexical_cast<int>(stime_str.substr(0, 2 ));
	int seconds = boost::lexical_cast<int>(stime_str.substr(2, 2));
	int min = boost::lexical_cast<int>(stime_str.substr(4,2));
	int hour = boost::lexical_cast<int>(stime_str.substr(6, 8).c_str());
	int sumsecond = hour * 3600 + min * 60 + seconds;

	startframe = fframe + sumsecond * 25;
	
	fframe = boost::lexical_cast<int>(etime_str.substr(0, 2));
	seconds = boost::lexical_cast<int>(etime_str.substr(2, 2));
	min = boost::lexical_cast<int>(etime_str.substr(4, 2));
	hour = boost::lexical_cast<int>(etime_str.substr(6, 8));
	sumsecond = hour * 3600 + min * 60 + seconds;
	endframe = fframe + sumsecond * 25;
	
	ctx.parameters.push_back(realname);
	ctx.parameters.push_back(L"SEEK");
	ctx.parameters.push_back(boost::lexical_cast<std::wstring>(startframe));
	if (endframe!=0)
	{
		ctx.parameters.push_back(L"LENGTH");
		ctx.parameters.push_back(boost::lexical_cast<std::wstring>(endframe));
	}
	
	

	core::diagnostics::scoped_call_context save;
	core::diagnostics::call_context::for_thread().video_channel = ctx.channel_index + 1;
	core::diagnostics::call_context::for_thread().layer = ctx.layer_index();
	auto pFP = ctx.producer_registry->create_producer(get_producer_dependencies(ctx.channel.channel, ctx), ctx.parameters);
	ctx.channel.channel->stage().load(ctx.layer_index(), pFP, false);

	return ack_command(ctx);
}

std::wstring cue_command(command_context& ctx)
{
	
	//提取文件名
	std::wstring filename_hex;
	std::wstring message = ctx.parameters[0];
	if (boost::lexical_cast<HexTo<int>>(message.substr(4,2))>0x80)//新协议
	{
		int lens = boost::lexical_cast<HexTo<int>>(message.substr(8, 2))*2;
		filename_hex = message.substr(10, lens);
		
	}
	else
	{
		filename_hex = message.substr(8,16);
	}

	std::wstring realname;
	for (int i = 0;i < filename_hex.size();i += 2)
	{
		realname.push_back(boost::lexical_cast<HexTo<int>>(filename_hex.substr(i, 2)));
	}

	//重置参数
	ctx.parameters.clear();
	ctx.parameters.push_back(realname);

	core::diagnostics::scoped_call_context save;
	core::diagnostics::call_context::for_thread().video_channel = ctx.channel_index + 1;
	core::diagnostics::call_context::for_thread().layer = ctx.layer_index();
	auto pFP = ctx.producer_registry->create_producer(get_producer_dependencies(ctx.channel.channel, ctx), ctx.parameters);
	ctx.channel.channel->stage().load(ctx.layer_index(), pFP, true);

	//ack
	return ack_command(ctx);

}

std::wstring play_command(command_context& ctx)
{
	ctx.channel.channel->stage().play(ctx.layer_index());
	return ack_command(ctx);
}
std::wstring still_command(command_context& ctx)
{
	ctx.channel.channel->stage().pause(ctx.layer_index());
	return ack_command(ctx);
}
std::wstring continue_command(command_context& ctx)
{
	ctx.channel.channel->stage().resume(ctx.layer_index());
	return ack_command(ctx);
}

std::wstring stop_command(command_context& ctx)
{
	ctx.channel.channel->stage().stop(ctx.layer_index());
	return ack_command(ctx);
}

void register_commands(vdcp_command_repository& repo)
{
	repo.register_command(			L"Basic Commands",		L"OPENPORT",					vdcp_describer,						openport_command,				0);
	repo.register_command(			L"Basic Commands",		L"ACK",							vdcp_describer,						ack_command,					0);
	repo.register_command(			L"Basic Commands",		L"NCK",							vdcp_describer,						nak_command,					0);
	repo.register_channel_command(	L"Basic Commands",		L"PORTSTATUS",					vdcp_describer,						portstatus_command,				0);
	repo.register_command(			L"Basic Commands",		L"NEXTDATA",					vdcp_describer,						nextdata_command,				0);
	
	repo.register_command(			L"Basic Commands",		L"IDEXIST",						vdcp_describer,						idexist_command,				0);



	repo.register_channel_command(	L"Basic Commands",		L"CUEWITHDATA",					vdcp_describer,						cuedata_command,				1);
	repo.register_channel_command(	L"Basic Commands",		L"CUE",							vdcp_describer,						cue_command,					1);
	repo.register_channel_command(	L"Basic Commands",		L"PLAY",						vdcp_describer,						play_command,					0);
	repo.register_channel_command(	L"Basic Commands",		L"STILL",						vdcp_describer,						still_command,					0);
	repo.register_channel_command(	L"Basic Commands",		L"CONTINUE",					vdcp_describer,						continue_command,				0);
	repo.register_channel_command(	L"Basic Commands",		L"STOP",						vdcp_describer,						stop_command,					0);

	repo.register_command(			L"Query Commands",		L"CINF",						vdcp_describer,						cinf_command,					1);
	repo.register_command(			L"Query Commands",		L"IDLIST",						vdcp_describer,						idlist_command,					0);
}

}	//namespace vdcp
}}	//namespace caspar
