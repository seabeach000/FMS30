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
* Author: Robert Nagy, ronag89@gmail.com
*/

#pragma once

#include <common/except.h>
#include <common/log.h>
#include <core/video_format.h>
#include <core/frame/frame.h>
#include <common/memshfl.h>
#include "../decklink_api.h"

#include <boost/lexical_cast.hpp>

#include <string>
#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/opt.h>
#include <libavutil/pixdesc.h>
#include <libavutil/parseutils.h>
#include <libavcodec/avcodec.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

#define _10bit_data_get

namespace caspar { namespace decklink {
	
static BMDDisplayMode get_decklink_video_format(core::video_format fmt) 
{
	switch(fmt)
	{
	case core::video_format::pal:			return bmdModePAL;
	case core::video_format::ntsc:			return bmdModeNTSC;
	case core::video_format::x576p2500:		return (BMDDisplayMode)ULONG_MAX;
	case core::video_format::x720p2398:		return (BMDDisplayMode)ULONG_MAX;
	case core::video_format::x720p2400:		return (BMDDisplayMode)ULONG_MAX;
	case core::video_format::x720p2500:		return (BMDDisplayMode)ULONG_MAX;
	case core::video_format::x720p5000:		return bmdModeHD720p50;
	case core::video_format::x720p2997:		return (BMDDisplayMode)ULONG_MAX;
	case core::video_format::x720p5994:		return bmdModeHD720p5994;
	case core::video_format::x720p3000:		return (BMDDisplayMode)ULONG_MAX;
	case core::video_format::x720p6000:		return bmdModeHD720p60;
	case core::video_format::x1080p2398:	return bmdModeHD1080p2398;
	case core::video_format::x1080p2400:	return bmdModeHD1080p24;
	case core::video_format::x1080i5000:	return bmdModeHD1080i50;
	case core::video_format::x1080i5994:	return bmdModeHD1080i5994;
	case core::video_format::x1080i6000:	return bmdModeHD1080i6000;
	case core::video_format::x1080p2500:	return bmdModeHD1080p25;
	case core::video_format::x1080p2997:	return bmdModeHD1080p2997;
	case core::video_format::x1080p3000:	return bmdModeHD1080p30;
	case core::video_format::x1080p5000:	return bmdModeHD1080p50;
	case core::video_format::x1080p5994:	return bmdModeHD1080p5994;
	case core::video_format::x1080p6000:	return bmdModeHD1080p6000;
	case core::video_format::x1556p2398:	return bmdMode2k2398;
	case core::video_format::x1556p2400:	return bmdMode2k24;
	case core::video_format::x1556p2500:	return bmdMode2k25;
	case core::video_format::dci1080p2398:	return bmdMode2kDCI2398;
	case core::video_format::dci1080p2400:	return bmdMode2kDCI24;
	case core::video_format::dci1080p2500:	return bmdMode2kDCI25;
	case core::video_format::x2160p2398:	return bmdMode4K2160p2398;
	case core::video_format::x2160p2400:	return bmdMode4K2160p24;
	case core::video_format::x2160p2500:	return bmdMode4K2160p25;
	case core::video_format::x2160p2997:	return bmdMode4K2160p2997;
	case core::video_format::x2160p3000:	return bmdMode4K2160p30;
	case core::video_format::x2160p5000:	return bmdMode4K2160p50;
	case core::video_format::x2160p5994:	return bmdMode4K2160p5994;
	case core::video_format::x2160p6000:	return bmdMode4K2160p60;
	case core::video_format::dci2160p2398:	return bmdMode4kDCI2398;
	case core::video_format::dci2160p2400:	return bmdMode4kDCI24;
	case core::video_format::dci2160p2500:	return bmdMode4kDCI25;
	default:								return (BMDDisplayMode)ULONG_MAX;
	}
}

static core::video_format get_caspar_video_format(BMDDisplayMode fmt) 
{
	switch(fmt)
	{
	case bmdModePAL:						return core::video_format::pal;
	case bmdModeNTSC:						return core::video_format::ntsc;
	case bmdModeHD720p50:					return core::video_format::x720p5000;
	case bmdModeHD720p5994:					return core::video_format::x720p5994;
	case bmdModeHD720p60:					return core::video_format::x720p6000;
	case bmdModeHD1080p2398:				return core::video_format::x1080p2398;
	case bmdModeHD1080p24:					return core::video_format::x1080p2400;
	case bmdModeHD1080i50:					return core::video_format::x1080i5000;
	case bmdModeHD1080i5994:				return core::video_format::x1080i5994;
	case bmdModeHD1080i6000:				return core::video_format::x1080i6000;
	case bmdModeHD1080p25:					return core::video_format::x1080p2500;
	case bmdModeHD1080p2997:				return core::video_format::x1080p2997;
	case bmdModeHD1080p30:					return core::video_format::x1080p3000;
	case bmdModeHD1080p50:					return core::video_format::x1080p5000;
	case bmdModeHD1080p5994:				return core::video_format::x1080p5994;
	case bmdModeHD1080p6000:				return core::video_format::x1080p6000;
	case bmdMode2k2398:						return core::video_format::x1556p2398;
	case bmdMode2k24:						return core::video_format::x1556p2400;
	case bmdMode2k25:						return core::video_format::x1556p2500;
	case bmdMode2kDCI2398:					return core::video_format::dci1080p2398;
	case bmdMode2kDCI24:					return core::video_format::dci1080p2400;
	case bmdMode2kDCI25:					return core::video_format::dci1080p2500;
	case bmdMode4K2160p2398:				return core::video_format::x2160p2398;
	case bmdMode4K2160p24:					return core::video_format::x2160p2400;
	case bmdMode4K2160p25:					return core::video_format::x2160p2500;
	case bmdMode4K2160p2997:				return core::video_format::x2160p2997;
	case bmdMode4K2160p30:					return core::video_format::x2160p3000;
	case bmdMode4kDCI2398:					return core::video_format::dci2160p2398;
	case bmdMode4kDCI24:					return core::video_format::dci2160p2400;
	case bmdMode4kDCI25:					return core::video_format::dci2160p2500;
	default:								return core::video_format::invalid;
	}
}

static std::wstring get_mode_name(const com_ptr<IDeckLinkDisplayMode>& mode)
{
	String mode_name;
	mode->GetName(&mode_name);
	return u16(mode_name);
}

template<typename T, typename F>
BMDDisplayMode get_display_mode(const T& device, BMDDisplayMode format, BMDPixelFormat pix_fmt, F flag, bool& will_attempt_dma)
{
    IDeckLinkDisplayMode* m = nullptr;
    IDeckLinkDisplayModeIterator* iter;
    if(SUCCEEDED(device->GetDisplayModeIterator(&iter)))
	{
        auto iterator = wrap_raw<com_ptr>(iter, true);
        while(SUCCEEDED(iterator->Next(&m)) &&
                m != nullptr &&
                m->GetDisplayMode() != format)
        {
            m->Release();
        }
	}

    if(!m)
		CASPAR_THROW_EXCEPTION(user_error() << msg_info("Device could not find requested video-format: " + boost::lexical_cast<std::string>(format)));

	com_ptr<IDeckLinkDisplayMode> mode = wrap_raw<com_ptr>(m, true);

	BMDDisplayModeSupport displayModeSupport;
	will_attempt_dma = false;

	if (FAILED(device->DoesSupportVideoMode(mode->GetDisplayMode(), pix_fmt, flag, &displayModeSupport, nullptr)))
		CASPAR_THROW_EXCEPTION(caspar_exception() << msg_info(L"Could not determine whether device supports requested video format: " + get_mode_name(mode)));
	else if (displayModeSupport == bmdDisplayModeNotSupported)
		CASPAR_LOG(warning) << L"Device does not support video-format: " << get_mode_name(mode);
	else if (displayModeSupport == bmdDisplayModeSupportedWithConversion)
		CASPAR_LOG(warning) << L"Device supports video-format with conversion: " << get_mode_name(mode);
	else
		will_attempt_dma = true;

	return mode->GetDisplayMode();
}

template<typename T, typename F>
static BMDDisplayMode get_display_mode(const T& device, core::video_format fmt, BMDPixelFormat pix_fmt, F flag, bool& will_attempt_dma)
{	
	return get_display_mode(device, get_decklink_video_format(fmt), pix_fmt, flag, will_attempt_dma);
}

template<typename T>
static std::wstring version(T iterator)
{
    auto info = iface_cast<IDeckLinkAPIInformation>(iterator);
	if (!info)
		return L"Unknown";
	
    String ver;
    info->GetString(BMDDeckLinkAPIVersion, &ver);
		
    return u16(ver);
}

static com_ptr<IDeckLink> get_device(size_t device_index)
{
    auto pDecklinkIterator = create_iterator();
		
	size_t n = 0;
    com_ptr<IDeckLink> decklink;
    IDeckLink* current = nullptr;
    while(n < device_index && pDecklinkIterator->Next(&current) == S_OK)
    {
        ++n;
        decklink = wrap_raw<com_ptr>(current);
        current->Release();
    }

	if(n != device_index || !decklink)
		CASPAR_THROW_EXCEPTION(user_error() << msg_info("Decklink device " + boost::lexical_cast<std::string>(device_index) + " not found."));
		
	return decklink;
}

template <typename T>
static std::wstring get_model_name(const T& device)
{	
    String pModelName;
	device->GetModelName(&pModelName);
    return u16(pModelName);
}

class reference_signal_detector
{
	com_iface_ptr<IDeckLinkOutput>	output_;
	BMDReferenceStatus				last_reference_status_	= static_cast<BMDReferenceStatus>(-1);
public:
	reference_signal_detector(const com_iface_ptr<IDeckLinkOutput>& output)
		: output_(output)
	{
	}

	template<typename Print>
	void detect_change(const Print& print)
	{
		BMDReferenceStatus reference_status;

		if (output_->GetReferenceStatus(&reference_status) != S_OK)
		{
			CASPAR_LOG(error) << print() << L" Reference signal: failed while querying status";
		}
		else if (reference_status != last_reference_status_)
		{
			last_reference_status_ = reference_status;

			if (reference_status == 0)
				CASPAR_LOG(info) << print() << L" Reference signal: not detected.";
			else if (reference_status & bmdReferenceNotSupportedByHardware)
				CASPAR_LOG(info) << print() << L" Reference signal: not supported by hardware.";
			else if (reference_status & bmdReferenceLocked)
				CASPAR_LOG(info) << print() << L" Reference signal: locked.";
			else
				CASPAR_LOG(info) << print() << L" Reference signal: Unhandled enum bitfield: " << reference_status;
		}
	}
};

//modify vanc
//---------------------------------------

static std::vector<int> Empty_;
class ByteArrayHelper
{

public:
	static std::vector<int> Locate(std::vector<unsigned char>& self, std::vector<unsigned char>& candidate)
	{
		if (IsEmptyLocate(self, candidate))
			return Empty_;

		std::vector<int> list;
		for (int i = 0; i < (int)self.size(); i++)
		{
			if (!IsMatch(self, i, candidate))
				continue;

			list.push_back(i);
		}

		return (int)list.size() == 0 ? Empty_ : list;
	}
private:
	static bool IsMatch(std::vector<unsigned char>& array, int position, std::vector<unsigned char>& candidate)
	{
		if ((int)candidate.size() > ((int)array.size() - position))
			return false;

		for (int i = 0; i < (int)candidate.size(); i++)
		{
			if (array[position + i] != candidate[i])
			{
				return false;
			}
		}

		return true;
	}
	static bool IsEmptyLocate(std::vector<unsigned char>& array, std::vector<unsigned char>& candidate)
	{
		return (int)array.size() == 0
			|| (int)candidate.size() == 0
			|| (int)candidate.size() > (int)array.size();
	}
};
static ByteArrayHelper bytearrayHelper;
static uint16_t _adf[] = { 0, 0x3FF, 0x3FF };
static unsigned char _patternAdfSD[] = { 0x00, 0xFC, 0xFF, 0x3F };
static unsigned char _patternAdfHD1[] = { 0x00, 0x02, 0x00, 0x20, 0xFF, 0x03, 0xF8, 0x3F };
static unsigned char _patternAdfHD2[] = { 0x00, 0x00, 0xF8, 0x3F, 0x00, 0xFE, 0x0F, 0x20 };

//class AFDData;
//class CommonAncillaryData;
class AncillaryData;
static AncillaryData* CreateAncillaryDataInstance(unsigned char did, unsigned char sdid_dbn);
class AncillaryData
{
public:
	unsigned char _DID;
	unsigned char _SDID;
	std::vector<unsigned char> _DATA;
public:
	enum ANC_DATA_MODE
	{
		ADM_10Bit,
		ADM_20Bit_Y,
		ADM_20Bit_C
	};

private:
	static bool is_parity(unsigned char data)
	{
		data ^= (unsigned char)(data >> 4);
		data ^= (unsigned char)(data >> 2);
		data ^= (unsigned char)(data >> 1);
		return (data & 1) != 0;
	}
	static std::vector<uint16_t> Convert8BitToXBit(std::vector<unsigned char>& bytes, int numberBits)
	{
		std::vector<uint16_t> results;
		int startBit = 0;
		int i = 0;
		while (i < (int)bytes.size())
		{
			uint16_t value;
			int borrowBits = numberBits - (8 - startBit);
			if (borrowBits > 0)
			{
				if (i + 1 >= (int)bytes.size())
					break;
				unsigned char nextByte = bytes[i + 1];
				value = (uint16_t)((bytes[i] >> startBit) + ((nextByte & (0xFF >> (8 - borrowBits))) << (numberBits - borrowBits)));
				startBit = borrowBits;
				i++;
			}
			else
			{
				value = (uint16_t)((bytes[i] >> startBit) & (0xFF >> (8 - numberBits)));
				startBit += numberBits;
				if (startBit >= 8)
				{
					startBit = 0;
					i++;
				}
			}
			results.push_back(value);
		}
		return results;
	}
	static std::vector<unsigned char> PackXBitTo8Bit(std::vector<uint16_t>& datas, int numberBits, int groupBytes)
	{
		std::vector<unsigned char> results;
		int byteCount = 0;
		int leftBits = 8;
		int startBit = 0;
		unsigned char byteValue = 0;
		int i = 0;
		while (i < (int)datas.size())
		{
			uint16_t dataValue = (uint16_t)(datas[i] & (0xFFFF >> (16 - numberBits)));
			if (numberBits - startBit <= leftBits)
			{
				byteValue += (unsigned char)(((dataValue >> startBit) << (8 - leftBits)) & 0xFF);
				i++;
				leftBits -= numberBits - startBit;
				startBit = 0;

				if (leftBits == 0 || (byteCount == groupBytes - 1 && leftBits < numberBits))
				{
					results.push_back(byteValue);
					byteValue = 0;
					byteCount++;
					if (byteCount == groupBytes)
						byteCount = 0;
					leftBits = 8;
				}
			}
			else
			{
				byteValue += (unsigned char)(((dataValue >> startBit) << (8 - leftBits)) & 0xFF);
				startBit += leftBits;
				results.push_back(byteValue);
				byteValue = 0;
				byteCount++;
				leftBits = 8;
			}
		}
		return results;
	}

	static std::vector<uint16_t> Parse10BitData(std::vector<unsigned char>& hdycBytes, int startPos, int length, ANC_DATA_MODE ancDataMode)
	{
		std::vector<uint16_t> primitiveData;
		std::vector<unsigned char> buffer(4, 0);
		for (int i = 0; i < length; i += 4)
		{
			for (int j = 0; j < 4; j++)
			{
				buffer[j] = (i + j < length) ? hdycBytes[startPos + i + j] : (unsigned char)0;
			}
			std::vector<uint16_t> temp = Convert8BitToXBit(buffer, 10);
			primitiveData.insert(primitiveData.end(), temp.begin(), temp.end());
		}

		if ((int)primitiveData.size() > 0 && ancDataMode != ADM_10Bit)
		{
			std::vector<uint16_t> realDataList;
			int realDataPos = ancDataMode == ADM_20Bit_C ? 0 : 1;
			while (realDataPos < (int)primitiveData.size())
			{
				realDataList.push_back(primitiveData[realDataPos]);
				realDataPos += 2;
			}
			return realDataList;
		}
		return primitiveData;
	}

	static AncillaryData* ParseAncillaryData(std::vector<unsigned char>& hdycBytes, int startPos, ANC_DATA_MODE ancDataMode)
	{
		int adfBytes = ancDataMode == ADM_10Bit ? 4 : 8;
		int dataHeaderBytes = adfBytes;
		if (startPos + adfBytes + dataHeaderBytes >= (int)hdycBytes.size())
			return nullptr;
		std::vector<uint16_t> dataHeader = Parse10BitData(hdycBytes, startPos + adfBytes, dataHeaderBytes, ancDataMode);
		if ((int)dataHeader.size() != 3)
			return nullptr;
		unsigned char did = (unsigned char)(dataHeader[0] & 0xFF);
		unsigned char sdid_dbn = (unsigned char)(dataHeader[1] & 0xFF);
		unsigned char dc = (unsigned char)(dataHeader[2] & 0xFF);

		AncillaryData* ancillaryDataInstance = CreateAncillaryDataInstance(did, sdid_dbn);
		if (ancillaryDataInstance == nullptr)
			return nullptr;

		ancillaryDataInstance->_DID = did;
		ancillaryDataInstance->_SDID = sdid_dbn;

		int dataBodyBytes = (dc*(ancDataMode == ADM_10Bit ? 1 : 2) * 4 + 2) / 3;
		std::vector<uint16_t> dataBody = Parse10BitData(hdycBytes, startPos + adfBytes + dataHeaderBytes, dataBodyBytes, ancDataMode);
		if ((int)dataBody.size() < dc)
			return nullptr;
		std::vector<unsigned char> ancData(dc, 0);
		for (int i = 0; i < dc; i++)
			ancData[i] = (unsigned char)(dataBody[i] & 0xFF);
		ancillaryDataInstance->_DATA = ancData;

		return ancillaryDataInstance;
	}
public:
	unsigned char GetDBN()
	{
		return _SDID;
	}
	void SetDBN(unsigned char v)
	{
		_SDID = v;
	}
	std::vector<unsigned char> GetDATA()
	{
		return _DATA;
	}
	void SetDATA(std::vector<unsigned char> v)
	{
		_DATA = v;
	}
	unsigned char GetDC()
	{
		return (unsigned char)_DATA.size();
	}
	static uint16_t ByteTo10Bit(unsigned char by)
	{
		uint16_t result = by;
		if (is_parity(by))
			result |= 0x100;
		else
			result |= 0x200;
		return result;
	}
	virtual std::vector<uint16_t> Get10BitData()
	{
		std::vector<uint16_t> results;
		results.push_back(_adf[0]);
		results.push_back(_adf[1]);
		results.push_back(_adf[2]);
		results.push_back(ByteTo10Bit(_DID));
		results.push_back(ByteTo10Bit(_SDID));
		results.push_back(ByteTo10Bit(GetDC()));
		std::for_each(_DATA.begin(), _DATA.end(), [&](unsigned char var) 
		{
			results.push_back(ByteTo10Bit(var)); 
		});
		uint16_t checksum = 0;
		for (int i = 3; i < (int)results.size(); i++)
		{
			checksum += (uint16_t)(results[i] & 0x1FF);
		}
		checksum &= 0x1FF;
		if ((checksum & 0x100) == 0)
		{
			checksum |= 0x200;
		}
		results.push_back(checksum);
		return results;
	}
	virtual std::vector<unsigned char> GetHDYCBytesData(ANC_DATA_MODE ancDataMode)
	{
		std::vector<uint16_t> unpackedANCData = Get10BitData();
		if (ancDataMode != ADM_10Bit)
		{
			std::vector<uint16_t> hdModeUnpackedANCData;
			std::for_each(unpackedANCData.begin(), unpackedANCData.end(), [&](uint16_t value)
			{
				if (ancDataMode == ADM_20Bit_Y)
				{
					hdModeUnpackedANCData.push_back(0x200);
					hdModeUnpackedANCData.push_back(value);
			}
				else
				{
					hdModeUnpackedANCData.push_back(value);
					hdModeUnpackedANCData.push_back(0x200);
				}
			});
			unpackedANCData = hdModeUnpackedANCData;
		}
		return PackXBitTo8Bit(unpackedANCData, 10, 4);
	}

	static std::list<AncillaryData> ParseAncillaryDatas(std::vector<unsigned char>& hdycBytes)
	{
		std::list<AncillaryData> ancillaryDatas;
		std::vector<unsigned char> pAdfSD(_patternAdfSD, _patternAdfSD + 4);
		std::vector<int> positions = bytearrayHelper.Locate(hdycBytes, pAdfSD);
		std::for_each(positions.begin(), positions.end(), [&](int position)
		{
			AncillaryData* ancillaryData = ParseAncillaryData(hdycBytes, position, ADM_10Bit);
			if (ancillaryData != nullptr)
				ancillaryDatas.push_back(*ancillaryData);
		});
		std::vector<unsigned char> pAdfHD1(_patternAdfHD1, _patternAdfHD1 + 8);
		positions = bytearrayHelper.Locate(hdycBytes, pAdfHD1);
		std::for_each (positions.begin(),positions.end(),[&](int position)
		{
			AncillaryData* ancillaryData = ParseAncillaryData(hdycBytes, position, ADM_20Bit_Y);
			if (ancillaryData != nullptr)
				ancillaryDatas.push_back(*ancillaryData);
		});
		std::vector<unsigned char> pAdfHD2(_patternAdfHD2, _patternAdfHD2 + 8);
		positions = bytearrayHelper.Locate(hdycBytes, pAdfHD2);
		std::for_each (positions.begin(),positions.end(),[&](int position)
		{
			AncillaryData* ancillaryData = ParseAncillaryData(hdycBytes, position, ADM_20Bit_C);
			if (ancillaryData != nullptr)
				ancillaryDatas.push_back(*ancillaryData);
		});

		return ancillaryDatas;
	}

};

class CommonAncillaryData : public AncillaryData
{
public:
	CommonAncillaryData()
	{}
	unsigned char GetDID()
	{
		return _DID;
	}
	void SetDID(unsigned char did)
	{
		_DID = did;
	}
	unsigned char GetSDID()
	{
		return _SDID;
	}
	void SetSDID(unsigned char sdid)
	{
		_SDID = sdid;
	}
};

class AFDData : public AncillaryData
{
public:
	enum AspectRatio
	{
		AR_16_9,
		AR_4_3
	};

	enum AFD
	{
		AFD_Undefined_0000,
		AFD_Reserved_0001,
		AFD_16_9_Image_Top_0010,
		AFD_14_9_Image_Top_0011,
		AFD_Greater_Than_16_9_Image_0100,
		AFD_Reserved_0101,
		AFD_Reserved_0110,
		AFD_Reserved_0111,
		AFD_Full_Frame_Image_1000,
		AFD_4_3_Image_1001,
		AFD_16_9_Image_Protected_Center_1010,
		AFD_14_9_Image_Center_1011,
		AFD_Reserved_1100,
		AFD_4_3_Image_Alter_14_9_Center_1101,
		AFD_16_9_Image_Alter_14_9_Center_1110,
		AFD_16_9_Image_Alter_4_3_Center_1111
	};

public:
	AFDData()
	{
		_DID = 0x41;
		_SDID = 0x05;
		unsigned char temp[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		_DATA = std::vector<unsigned char>(temp, temp + 8);
	}

	AspectRatio GetAspectRatioOfCodedFrame()
	{
		return (_DATA[0] & 0x04) == 0 ? AR_4_3 : AR_16_9;
	}
	void SetAspectRatioOfCodedFrame(AspectRatio asr)
	{
		if (asr == AR_16_9)
			_DATA[0] |= 0x04;
		else
			_DATA[0] &= 0xFB;
	}

	AFD GetActiveFormatDescription()
	{
		return (AFD)((_DATA[0] & 0x78) >> 3);
	}
	void SetActiveFormatDescription(AFD afd)
	{
		_DATA[0] = (unsigned char)((_DATA[0] & 0x87) | (((unsigned char)afd) << 3));
	}
};

static AncillaryData* CreateAncillaryDataInstance(unsigned char did, unsigned char sdid_dbn)
{
	if (did == 0x41 && sdid_dbn == 0x05)
		return new AFDData();
	else
		return new CommonAncillaryData();
}

typedef std::vector<uint8_t, tbb::cache_aligned_allocator<uint8_t>>	byte_vector;

#ifdef _10bit_data_get
class V210Decoder
{
private:
	std::shared_ptr<SwsContext>				sws_;
	AVCodec *                               pDec;
	AVCodecContext*                         cxt;
	core::video_format_desc					format_desc_;

public:
	V210Decoder(const core::video_format_desc format_desc)
	{
		format_desc_ = format_desc;
		pDec = avcodec_find_decoder(AV_CODEC_ID_V210);
		cxt = avcodec_alloc_context3(pDec);
//3.0
		cxt->pix_fmt = AV_PIX_FMT_UYVY422;
//2.0   cxt->pix_fmt = PIX_FMT_UYVY422;


		cxt->width = format_desc_.width;
		cxt->height = format_desc_.height;
		if (avcodec_open2(cxt, pDec, nullptr) < 0)
		{
			CASPAR_LOG(error) << L"Find V210 Decoder Failed.";
		}
	}

	bool decode_video(IDeckLinkVideoInputFrame* frame, std::shared_ptr<AVFrame> res)
	{
		void* bytes;
		if (frame == nullptr || FAILED(frame->GetBytes(&bytes)) || !bytes)return false;

		AVPacket avpkt;
		av_init_packet(&avpkt);
		avpkt.data = reinterpret_cast<uint8_t*>(bytes);
		avpkt.size = frame->GetRowBytes() * frame->GetHeight();
		avpkt.flags = AV_PKT_FLAG_KEY;

		int frame_finished;
		avcodec_decode_video2(cxt, res.get(), &frame_finished, &avpkt);

		return true;
	}
};
#endif

class V210Encoder
{
private:
	std::shared_ptr<SwsContext>				sws_;
	AVCodec *                               pEnc;
	AVCodecContext*                         cxt;
	byte_vector								key_picture_buf_;
	byte_vector								picture_buf_;
	core::video_format_desc                 format_desc_;
	bool                                    key_only_;
	std::shared_ptr<AVFrame>                out_frame;
public:
	V210Encoder(const core::video_format_desc format_desc, bool key_only)
	{
		key_only_ = key_only;
		format_desc_ = format_desc;
		if (!sws_)
		{
			sws_.reset(
				sws_getContext(
					format_desc_.width,
					format_desc_.height,

//3.0
					AV_PIX_FMT_BGRA,

//					PIX_FMT_BGRA,


					format_desc_.width,
					format_desc_.height,
					AV_PIX_FMT_YUV422P10,
					SWS_BICUBIC,
					nullptr,
					nullptr,
					nullptr
				),
				sws_freeContext);
			if (sws_ == nullptr)
				BOOST_THROW_EXCEPTION(caspar_exception() << msg_info(L"Cannot initialize the conversion context"));
		}
//3.0
		out_frame = std::shared_ptr<AVFrame>(av_frame_alloc(), av_free);

		//out_frame = std::shared_ptr<AVFrame>(avcodec_alloc_frame(), av_free);


		picture_buf_.resize(avpicture_get_size(AV_PIX_FMT_YUV422P10, format_desc_.width, format_desc_.height));
		avpicture_fill(reinterpret_cast<AVPicture*>(out_frame.get()), picture_buf_.data(), AV_PIX_FMT_YUV422P10, format_desc_.width, format_desc_.height);

		pEnc = avcodec_find_encoder(AV_CODEC_ID_V210);
		cxt = avcodec_alloc_context3(pEnc);
		cxt->pix_fmt = AV_PIX_FMT_YUV422P10;
		cxt->width = format_desc_.width;
		cxt->height = format_desc_.height;
		cxt->time_base.den = format_desc_.framerate.denominator();
		cxt->time_base.num = format_desc_.framerate.numerator();
	//	AVRational t = 
	//	cxt->framerate = format_desc_.framerate;
		int nRetCode = avcodec_open2(cxt, cxt->codec, nullptr);
		if (nRetCode < 0)
		{
			CASPAR_LOG(error) << L" mutable_decklink_frame() Find V210 Coder Failed.";
		}
	}

	void encode_video(std::shared_ptr<core::const_frame>	frame_, byte_vector& encode_buf)
	{
//3.0
		std::shared_ptr<AVFrame> in_frame(av_frame_alloc(), av_free);

//		std::shared_ptr<AVFrame> in_frame(avcodec_alloc_frame(), av_free);

		auto in_picture = reinterpret_cast<AVPicture*>(in_frame.get());
		byte_vector key_picture_buf;
		if (key_only_)
		{
			key_picture_buf.resize(frame_->image_data().size());
			in_picture->linesize[0] = format_desc_.width * 4;
			in_picture->data[0] = key_picture_buf.data();
			//2.0的函数，3.0不存在
			//fast_memshfl(in_picture->data[0], frame_->image_data().begin(), frame_->image_data().size(), 0x0F0F0F0F, 0x0B0B0B0B, 0x07070707, 0x03030303);
			aligned_memshfl(in_picture->data[0], frame_->image_data().begin(), frame_->image_data().size(), 0x0F0F0F0F, 0x0B0B0B0B, 0x07070707, 0x03030303);
		}
		else
		{
			avpicture_fill(
				in_picture,
				const_cast<uint8_t*>(
					frame_->image_data().begin()),

//3.0
				AV_PIX_FMT_BGRA,

//				PIX_FMT_BGRA,


				format_desc_.width,
				format_desc_.height
			);
		}
		sws_scale(sws_.get(), in_frame->data, in_frame->linesize, 0, format_desc_.height, out_frame->data, out_frame->linesize);

		int out_size = 0;


//3.0
		AVPacket pkt = {};
		av_init_packet(&pkt);
		pkt.data = encode_buf.data();
		pkt.size = static_cast<int>(encode_buf.size());
		out_frame->height = format_desc_.height;
		out_frame->width = format_desc_.width;
		out_frame->format = AV_PIX_FMT_YUV422P10;
		int got_packet = 0;
		out_size = avcodec_encode_video2(cxt, &pkt, out_frame.get(), &got_packet);
		av_packet_unref(&pkt);
/////////////
	
//2.0
//		out_size = avcodec_encode_video(cxt, encode_buf.data(), encode_buf.size(), out_frame.get());
		if (out_size != 0)

		{
			CASPAR_LOG(error) << L" mutable_decklink_frame() V210 Coder Codec Failed.";
		}
	}
};


class mutable_decklink_frame : public IDeckLinkMutableVideoFrame
{
	tbb::atomic<int>											ref_count_;
	std::shared_ptr<core::const_frame>							frame_;
	core::video_format_desc								        format_desc_;

	bool													    key_only_;
	std::vector<uint8_t, tbb::cache_aligned_allocator<uint8_t>> data_;
	IDeckLinkVideoFrameAncillary*                               anc_data_;

	std::shared_ptr<V210Encoder>            V210Encoder_;
	std::shared_ptr<AVFrame>                ret_frame;
	byte_vector                             ret_picture_buf_;
public:
	mutable_decklink_frame(const std::shared_ptr<core::const_frame>& frame, const core::video_format_desc& format_desc, bool key_only, std::shared_ptr<V210Encoder> VE)
		: frame_(frame)
		, format_desc_(format_desc)
		, key_only_(key_only)
		, anc_data_(nullptr)
		, V210Encoder_(VE)
	{
		ref_count_ = 0;
//3.0
		ret_frame = std::shared_ptr<AVFrame>(av_frame_alloc(), av_free);
//2.0
//		ret_frame = std::shared_ptr<AVFrame>(avcodec_alloc_frame(), av_free);


		ret_picture_buf_.resize((((format_desc_.width + 47) / 48) * 128) * format_desc_.height);
		avpicture_fill(reinterpret_cast<AVPicture*>(ret_frame.get()), ret_picture_buf_.data(), AV_PIX_FMT_YUV422P10, format_desc_.width, format_desc_.height);
	}

	mutable_decklink_frame(const std::shared_ptr<core::const_frame>& frame, const core::video_format_desc& format_desc, std::vector<uint8_t, tbb::cache_aligned_allocator<uint8_t>>&& key_data, std::shared_ptr<V210Encoder> VE)
		: frame_(frame)
		, format_desc_(format_desc)
		, key_only_(true)
		, data_(std::move(key_data))
		, anc_data_(nullptr)
		, V210Encoder_(VE)
	{
		ref_count_ = 0;
//3.0
		ret_frame = std::shared_ptr<AVFrame>(av_frame_alloc(), av_free);
//2.0
//		ret_frame = std::shared_ptr<AVFrame>(avcodec_alloc_frame(), av_free);

		ret_picture_buf_.resize((((format_desc_.width + 47) / 48) * 128) * format_desc_.height);
		avpicture_fill(reinterpret_cast<AVPicture*>(ret_frame.get()), ret_picture_buf_.data(), AV_PIX_FMT_YUV422P10, format_desc_.width, format_desc_.height);
	}

	// IUnknown

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID*)
	{
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{
		return ++ref_count_;
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		if (--ref_count_ == 0)
		{
			delete this;
			return 0;
		}

		return ref_count_;
	}

	// IDecklinkVideoFrame

	long STDMETHODCALLTYPE GetWidth() { return format_desc_.width; }
	long STDMETHODCALLTYPE GetHeight() { return format_desc_.height; }
	long STDMETHODCALLTYPE GetRowBytes() { return ((format_desc_.width + 47) / 48) * 128; }
	BMDPixelFormat STDMETHODCALLTYPE GetPixelFormat() { return bmdFormat10BitYUV; }
	BMDFrameFlags STDMETHODCALLTYPE GetFlags() { return bmdFrameFlagDefault; }

	HRESULT STDMETHODCALLTYPE GetBytes(void** buffer)
	{
		try
		{
			if (static_cast<size_t>(frame_->image_data().size()) != format_desc_.size)
			{
				data_.resize(format_desc_.size, 0);
				*buffer = data_.data();
			}
			else if (key_only_)
			{
				if (data_.empty())
				{
					data_.resize(frame_->image_data().size());
					aligned_memshfl(data_.data(), frame_->image_data().begin(), frame_->image_data().size(), 0x0F0F0F0F, 0x0B0B0B0B, 0x07070707, 0x03030303);
				}
				*buffer = data_.data();
			}
			else
			{
				V210Encoder_->encode_video(frame_, ret_picture_buf_);
				*buffer = ret_frame->data[0];
			}
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
			return E_FAIL;
		}
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetTimecode(BMDTimecodeFormat format, IDeckLinkTimecode** timecode) { return S_FALSE; }
	HRESULT STDMETHODCALLTYPE GetAncillaryData(IDeckLinkVideoFrameAncillary** ancillary)
	{
		*ancillary = anc_data_;
		return S_OK;
	}

	//IDeckLinkMutableFrame
	HRESULT STDMETHODCALLTYPE SetFlags(BMDFrameFlags newFlags) { return S_OK; }

	HRESULT STDMETHODCALLTYPE SetTimecode(BMDTimecodeFormat format, IDeckLinkTimecode *timecode) { return S_OK; }

	HRESULT STDMETHODCALLTYPE SetTimecodeFromComponents(
		BMDTimecodeFormat format,
		unsigned char hours,
		unsigned char minutes,
		unsigned char seconds,
		unsigned char frames,
		BMDTimecodeFlags flags)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE SetAncillaryData(IDeckLinkVideoFrameAncillary *ancillary)
	{
		anc_data_ = ancillary;
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE SetTimecodeUserBits(
		BMDTimecodeFormat format,
		BMDTimecodeUserBits userBits
	)
	{
		return S_OK;
	}


	// decklink_frame	

	const boost::iterator_range<const int32_t*> audio_data()
	{
		return frame_->audio_data();
	}

	int64_t get_age_millis() const
	{
		return frame_->get_age_millis();
	}
};
//---------------------------------------

#if 0
static void set_latency(
	const CComQIPtr<IDeckLinkConfiguration>& config,
	configuration::latency_t latency,
	const std::wstring& print)
{
	if (latency == configuration::low_latency)
	{
		config->SetFlag(bmdDeckLinkConfigLowLatencyVideoOutput, true);
		CASPAR_LOG(info) << print << L" Enabled low-latency mode.";
	}
	else if (latency == configuration::normal_latency)
	{
		config->SetFlag(bmdDeckLinkConfigLowLatencyVideoOutput, false);
		CASPAR_LOG(info) << print << L" Disabled low-latency mode.";
	}
}

static void set_keyer(
	const CComQIPtr<IDeckLinkAttributes>& attributes,
	const CComQIPtr<IDeckLinkKeyer>& decklink_keyer,
	configuration::keyer_t keyer,
	const std::wstring& print)
{
	if (keyer == configuration::internal_keyer
		|| keyer == configuration::external_separate_device_keyer)
	{
		BOOL value = true;
		if (SUCCEEDED(attributes->GetFlag(BMDDeckLinkSupportsInternalKeying, &value)) && !value)
			CASPAR_LOG(error) << print << L" Failed to enable internal keyer.";
		else if (FAILED(decklink_keyer->Enable(FALSE)))
			CASPAR_LOG(error) << print << L" Failed to enable internal keyer.";
		else if (FAILED(decklink_keyer->SetLevel(255)))
			CASPAR_LOG(error) << print << L" Failed to set key-level to max.";
		else
			CASPAR_LOG(info) << print << L" Enabled internal keyer.";
	}
	else if (keyer == configuration::external_keyer)
	{
		BOOL value = true;
		if (SUCCEEDED(attributes->GetFlag(BMDDeckLinkSupportsExternalKeying, &value)) && !value)
			CASPAR_LOG(error) << print << L" Failed to enable external keyer.";
		else if (FAILED(decklink_keyer->Enable(TRUE)))
			CASPAR_LOG(error) << print << L" Failed to enable external keyer.";
		else if (FAILED(decklink_keyer->SetLevel(255)))
			CASPAR_LOG(error) << print << L" Failed to set key-level to max.";
		else
			CASPAR_LOG(info) << print << L" Enabled external keyer.";
	}
}
#endif
}}
