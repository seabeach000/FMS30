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

#include "AMCPProtocolStrategy.h"
#include "amcp_shared.h"
#include "AMCPCommand.h"
#include "AMCPCommandQueue.h"
#include "amcp_command_repository.h"

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cctype>
#include <future>

#include <core/help/help_repository.h>
#include <core/help/help_sink.h>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

#if defined(_MSC_VER)
#pragma warning (push, 1) // TODO: Legacy code, just disable warnings
#endif

namespace caspar { namespace protocol { namespace amcp {

using IO::ClientInfoPtr;

template <typename Out, typename In>
bool try_lexical_cast(const In& input, Out& result)
{
	Out saved = result;
	bool success = boost::conversion::detail::try_lexical_convert(input, result);

	if (!success)
		result = saved; // Needed because of how try_lexical_convert is implemented.

	return success;
}
struct AMCPProtocolStrategy::impl
{
private:
	std::vector<AMCPCommandQueue::ptr_type>		commandQueues_;
	spl::shared_ptr<amcp_command_repository>	repo_;
	std::map<std::wstring, ClientInfoPtr >	IDmap;//记录客户端的ID
	std::wstring								Control_ID;

public:
	impl(const std::wstring& name, const spl::shared_ptr<amcp_command_repository>& repo)
		: repo_(repo)
	{
		Control_ID = L"";
		IDmap.clear();
		commandQueues_.push_back(spl::make_shared<AMCPCommandQueue>(L"General Queue for " + name));

		for (int i = 0; i < repo_->channels().size(); ++i)
		{
			commandQueues_.push_back(spl::make_shared<AMCPCommandQueue>(
					L"Channel " + boost::lexical_cast<std::wstring>(i + 1) + L" for " + name));
		}
	}

	~impl() {}

	enum class error_state {
		no_error = 0,
		command_error,
		channel_error,
		parameters_error,
		unknown_error,
		access_error
	};

	struct command_interpreter_result
	{
		std::shared_ptr<caspar::IO::lock_container>	lock;
		std::wstring								command_name;
		AMCPCommand::ptr_type						command;
		error_state									error			= error_state::no_error;
		std::shared_ptr<AMCPCommandQueue>			queue;
	};
	bool RegisterInfo(const std::wstring& message, ClientInfoPtr pClientInfo)
	{
		std::vector<std::wstring> split;
		std::wstring instr;
		instr = boost::to_upper_copy(boost::trim_copy(message));
		boost::split(split, instr, boost::is_any_of(" "));

		if (boost::iequals(split[0], L"REGISTER"))
		{
			if (split.size() < 2)
			{
				pClientInfo->send(L"404 ERROR\r\n");
				return true;
			}
			std::wstring  id = pClientInfo->get_id();
			if (!boost::iequals(split[1] ,pClientInfo->get_id()))//新的ID，不重复
			{

				if (IDmap.find(pClientInfo->get_id()) != IDmap.end())//更换ID，先将原来的ID从表中去掉，不要断开
				{
					IDmap.erase(IDmap.find(pClientInfo->get_id()));
				}
				if (IDmap.find(split[1]) != IDmap.end())//目标ID如果存在，则断开连接删除节点
				{
					//IDmap[split[1]]->disconnect();
					IDmap.find(split[1])->second->disconnect();
					IDmap.erase(IDmap.find(split[1]));
				}
			}
			//注册ID
			pClientInfo->set_id(boost::to_upper_copy(boost::trim_copy(split[1])));
			pClientInfo->send(L"200 OK REGISTER SUCCESS\r\n");
			//IDmap[boost::to_upper_copy(boost::trim_copy(split[1]))] = pClientInfo;
			IDmap.insert(std::pair<std::wstring, ClientInfoPtr>(boost::to_upper_copy(boost::trim_copy(split[1])), pClientInfo));
			return true;
		}
		return false;
	}
	bool InfoSwitch(const std::wstring& message, IO::ClientInfoPtr pClientInfo)
	{

		std::vector<std::wstring> tokens;
		std::wstring instr;
		instr = boost::to_upper_copy(boost::trim_copy(message));
		boost::split(tokens, instr, boost::is_any_of(" "));
		if (tokens.size() < 1)
		{
			return false;
		}
		if (boost::iequals(tokens[0], L"INFOSWITCH"))
		{

			if (tokens.size() > 1)
			{
				Control_ID = tokens[1];
			}
			std::wstring Switchstr;
			Switchstr += L"200 OK INFOSWITCH SUCCESS\r\n";
			Switchstr += L"Control ";
			Switchstr += Control_ID;
			Switchstr += L"\r\n";
			for (BOOST_AUTO(it, IDmap.begin()); it != IDmap.end(); ++it)
			{
				Switchstr += it->first;
				Switchstr += L"\r\n";
			}
			pClientInfo->send(Switchstr.c_str());
			return true;
		}

		return false;
	}

	bool CommandEnable(const std::wstring& message, IO::ClientInfoPtr pClientInfo)
	{

		std::vector<std::wstring> tokens;
		std::wstring instr;
		instr = boost::to_upper_copy(boost::trim_copy(message));
		boost::split(tokens, instr, boost::is_any_of(" "));

		std::wstring relaystring;
		std::wstring protocal;
		std::wstring ID;
		int channel = 0;
		if (pClientInfo->get_id()==L"")
		{
			return true;
		}
		if (Control_ID!=L""&&pClientInfo->get_id()!=L""&&!boost::iequals(pClientInfo->get_id(),Control_ID))
		{
			relaystring += L"400 ERROR\r\n";
			relaystring += L"Control ";
			relaystring += Control_ID;
			relaystring += L"\r\n";
			pClientInfo->send(relaystring.c_str());
			return false;
		}
		return true;
	}

	bool Filer(const std::wstring& message, ClientInfoPtr pClientInfo)
	{
		//注册信息，过滤注册和重复注册
		if (RegisterInfo(message, pClientInfo))
		{
			return true;
		}

		//设置，查看id
		if (InfoSwitch(message, pClientInfo))
			return true;
		//amcp 是否有效	如果不是主控制则无效
		if (!CommandEnable(message, pClientInfo))
			return true;
		return false;
	}

	//The paser method expects message to be complete messages with the delimiter stripped away.
	//Thesefore the AMCPProtocolStrategy should be decorated with a delimiter_based_chunking_strategy
	void Parse(const std::wstring& message, ClientInfoPtr client)
	{
		if (message.empty())
		{
			CASPAR_LOG_COMMUNICATION(info) << L"Received message empty";
			return;
		}
		CASPAR_LOG_COMMUNICATION(info) << L"Received message from " << client->address() << ": " << message << L"\\r\\n";
		if (Filer(message, client))
			return;
		command_interpreter_result result;
		if(interpret_command_string(message, result, client))
		{
			if(result.lock && !result.lock->check_access(client))
				result.error = error_state::access_error;
			else
				result.queue->AddCommand(result.command);
		}
		
		if (result.error != error_state::no_error)
		{
			std::wstringstream answer;

			switch(result.error)
			{
			case error_state::command_error:
				answer << L"400 ERROR\r\n" << message << "\r\n";
				break;
			case error_state::channel_error:
				answer << L"401 " << result.command_name << " ERROR\r\n";
				break;
			case error_state::parameters_error:
				answer << L"402 " << result.command_name << " ERROR\r\n";
				break;
			case error_state::access_error:
				answer << L"503 " << result.command_name << " FAILED\r\n";
				break;
			case error_state::unknown_error:
				answer << L"500 FAILED\r\n";
				break;
			default:
				CASPAR_THROW_EXCEPTION(programming_error()
						<< msg_info(L"Unhandled error_state enum constant " + boost::lexical_cast<std::wstring>(static_cast<int>(result.error))));
			}
			client->send(answer.str());
		}
	}

private:
	bool interpret_command_string(const std::wstring& message, command_interpreter_result& result, ClientInfoPtr client)
	{
		try
		{
			std::list<std::wstring> tokens;
			tokenize(message, tokens);

			// Discard GetSwitch
			if (!tokens.empty() && tokens.front().at(0) == L'/')
				tokens.pop_front();

			std::wstring request_id;

			if (!tokens.empty() && boost::iequals(tokens.front(), L"REQ"))
			{
				tokens.pop_front();

				if (tokens.empty())
				{
					result.error = error_state::parameters_error;
					return false;
				}

				request_id = tokens.front();
				tokens.pop_front();
			}

			// Fail if no more tokens.
			if (tokens.empty())
			{
				result.error = error_state::command_error;
				return false;
			}

			// Consume command name
			result.command_name = boost::to_upper_copy(tokens.front());
			tokens.pop_front();

			// Determine whether the next parameter is a channel spec or not
			int channel_index = -1;
			int layer_index = -1;
			std::wstring channel_spec;

			if (!tokens.empty())
			{
				channel_spec = tokens.front();
				std::wstring channelid_str = boost::trim_copy(channel_spec);
				std::vector<std::wstring> split;
				boost::split(split, channelid_str, boost::is_any_of("-"));

				// Use non_throwing lexical cast to not hit exception break point all the time.
				if (try_lexical_cast(split[0], channel_index))
				{
					--channel_index;

					if (split.size() > 1)
						try_lexical_cast(split[1], layer_index);

					// Consume channel-spec
					tokens.pop_front();
				}
			}

			bool is_channel_command = channel_index != -1;

			//add by zibj 20161103
			/*替换bridge命令为route://命令 
			 *如下n、m为整形：
			 *play n-10 bridge m-10  ==》 play n-10 route://m-10
			 *play n-10 bridge m     ==》 play n-10 route://m
			*/
			if (2 == tokens.size())
			{
				std::wstring strparam = boost::to_lower_copy(tokens.front());
				if (0 == strparam.compare(L"bridge"))
				{
					strparam = L"route://" + tokens.back();
					tokens.pop_back();
					tokens.front() = strparam;
				}
			}
			//add by zibj 20161103 end

			// Create command instance
			if (is_channel_command)
			{
				result.command = repo_->create_channel_command(result.command_name, client, channel_index, layer_index, tokens);

				if (result.command)
				{
					result.lock = repo_->channels().at(channel_index).lock;
					result.queue = commandQueues_.at(channel_index + 1);
				}
				else // Might be a non channel command, although the first argument is numeric
				{
					// Restore backed up channel spec string.
					tokens.push_front(channel_spec);
					result.command = repo_->create_command(result.command_name, client, tokens);

					if (result.command)
						result.queue = commandQueues_.at(0);
				}
			}
			else
			{
				result.command = repo_->create_command(result.command_name, client, tokens);

				if (result.command)
					result.queue = commandQueues_.at(0);
			}

			if (!result.command)
				result.error = error_state::command_error;
			else
			{
				std::vector<std::wstring> parameters(tokens.begin(), tokens.end());

				result.command->parameters() = std::move(parameters);

				if (result.command->parameters().size() < result.command->minimum_parameters())
					result.error = error_state::parameters_error;
			}

			if (result.command)
				result.command->set_request_id(std::move(request_id));
		}
		catch (std::out_of_range&)
		{
			CASPAR_LOG(error) << "Invalid channel specified.";
			result.error = error_state::channel_error;
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
			result.error = error_state::unknown_error;
		}

		return result.error == error_state::no_error;
	}

	template<typename C>
	std::size_t tokenize(const std::wstring& message, C& pTokenVector)
	{
		//split on whitespace but keep strings within quotationmarks
		//treat \ as the start of an escape-sequence: the following char will indicate what to actually put in the string

		std::wstring currentToken;

		bool inQuote = false;
		bool getSpecialCode = false;

		for(unsigned int charIndex=0; charIndex<message.size(); ++charIndex)
		{
			if(getSpecialCode)
			{
				//insert code-handling here
				switch(message[charIndex])
				{
				case L'\\':
					currentToken += L"\\";
					break;
				case L'\"':
					currentToken += L"\"";
					break;
				case L'n':
					currentToken += L"\n";
					break;
				default:
					break;
				};
				getSpecialCode = false;
				continue;
			}

			if(message[charIndex]==L'\\')
			{
				getSpecialCode = true;
				continue;
			}

			if(message[charIndex]==L' ' && inQuote==false)
			{
				if(!currentToken.empty())
				{
					pTokenVector.push_back(currentToken);
					currentToken.clear();
				}
				continue;
			}

			if(message[charIndex]==L'\"')
			{
				inQuote = !inQuote;

				if(!currentToken.empty() || !inQuote)
				{
					pTokenVector.push_back(currentToken);
					currentToken.clear();
				}
				continue;
			}

			currentToken += message[charIndex];
		}

		if(!currentToken.empty())
		{
			pTokenVector.push_back(currentToken);
			currentToken.clear();
		}

		return pTokenVector.size();
	}
};

AMCPProtocolStrategy::AMCPProtocolStrategy(const std::wstring& name, const spl::shared_ptr<amcp_command_repository>& repo)
	: impl_(spl::make_unique<impl>(name, repo))
{
}
AMCPProtocolStrategy::~AMCPProtocolStrategy() {}
void AMCPProtocolStrategy::Parse(const std::wstring& msg, IO::ClientInfoPtr pClientInfo) { impl_->Parse(msg, pClientInfo); }


}	//namespace amcp
}}	//namespace caspar
