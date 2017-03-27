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

#include "VDCPProtocolStrategy.h"
#include "vdcp_shared.h"
#include "VDCPCommand.h"
#include "VDCPCommandQueue.h"
#include "vdcp_command_repository.h"

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

namespace caspar { namespace protocol { namespace vdcp {

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

CProtocol_VDCP* CProtocol_VDCP::GetDefProtocol()
{
	static CProtocol_VDCP VdcpCommands;
	return &VdcpCommands;
};

CProtocol_VDCP::CProtocol_VDCP()
{
	static  VDCP_CMD global_VDCP[69] =
	{
		{ VDCP_STOP					,0x10,0x00,0x02,0x00 },
		{ VDCP_PLAY					,0x10,0x01,0x02,0x00 },
		{ VDCP_RECORD				,0x10,0x02,0x02,0x00 },
		{ VDCP_FREEZE				,0x10,0x03,0x02,0x00 },
		{ VDCP_STILL				,0x10,0x04,0x02,0x00 },
		{ VDCP_STEP					,0x10,0x05,0x02,0x00 },
		{ VDCP_CONTINUE				,0x10,0x06,0x02,0x00 },
		{ VDCP_JOG					,0x10,0x07,0x03,0x00 },	// 还有4个字节的格式
		{ VDCP_JOG_FAR				,0x10,0x07,0x06,0x00 },	// 4个字节的格式
		{ VDCP_VARI_PLAY			,0x10,0x08,0x05,0x00 },	// ?
		{ VDCP_UNFREEZE				,0x10,0x09,0x02,0x00 },
		{ VDCP_EE_MODE				,0x10,0x0A,0x03,0x00 },	// 0: EE_OFF  1:EE_ON  2:EE_AUTO


		{ VDCP_RENAME_ID			,0x20,0x1D,0x12,0x00 },
		{ VDCP_PRESET_STD_TIME		,0x20,0x1E,0x07,0x00 },	// 0:DF  1: non_Drop 2:PAL
		{ VDCP_NEW_COPY				,0x20,0x1F,0x18,0x00 },
		{ VDCP_SORT_MODE			,0x20,0x20,0x03,0x00 },
		{ VDCP_CLOSE_PORT			,0x20,0x21,0x03,0x00 },
		{ VDCP_SELECT_PORT			,0x20,0x22,0x03,0x00 },
		{ VDCP_RECORD_INIT			,0x20,0x23,0x0E,0x00 },
		{ VDCP_PLAY_CUE				,0x20,0x24,0x0A,0x00 },	// 还有一种方式 + PreparedID
		{ VDCP_CUE_WITH_DATA		,0x20,0x25,0x12,0x00 },	// 0x0B
		{ VDCP_DELETE_ID			,0x20,0x26,0x0A,0x00 },

		{ VDCP_GET_FROM_ARCH		,0x20,0x27,0x00,0x00 },
		{ VDCP_CLEAR				,0x20,0x29,0x02,0x00 },
		{ VDCP_SEND_TO_ARCH			,0x20,0x2A,0x00,0x00 },
		{ VDCP_TO_SIGNAL_FULL		,0x20,0x2B,0x03,0x00 },

		{ VDCP_REC_INIT_WITH_DATA	,0x20,0x2C,0x12,0x00 },
		{ VDCP_SELECT_LOGICAL_DRV	,0x20,0x2D,0x03,0x00 },
		{ VDCP_SYSTEM_DELETE_ID		,0x20,0x2E,0x0A,0x00 },

		{ VDCP_PRESET				,0x20,0x30,0x02,0x00 },
		{ VDCP_V_COMPR_RATE			,0x20,0x31,0x06,0x00 },
		{ VDCP_A_SAMPLE_RATE		,0x20,0x32,0x03,0x00 },
		{ VDCP_A_COMPR_RATE			,0x20,0x33,0x03,0x00 },
		{ VDCP_A_IN_LEVEL			,0x20,0x34,0x04,0x00 },
		{ VDCP_A_OUT_LEVEL			,0x20,0x35,0x04,0x00 },

		{ VDCP_V_COMPR_PARAM		,0x20,0x37,0x06,0x00 },
		{ VDCP_SELECT_OUTPUT		,0x20,0x38,0x03,0x00 },
		{ VDCP_SELECT_INPUT			,0x20,0x39,0x03,0x00 },
		{ VDCP_RECORD_MODE			,0x20,0x3A,0x04,0x00 },

		{ VDCP_SC_ADJUST			,0x20,0x41,0x04,0x00 },
		{ VDCP_H_POS_ADJUST			,0x20,0x42,0x04,0x00 },
		{ VDCP_DISK_PREROLL			,0x20,0x43,0x04,0x00 },

		{ VDCP_COPY_FILE_TO			,0x20,0x50,0x0C,0x00 },
		{ VDCP_DELETE_FILE_FROM		,0x20,0x51,0x04,0x00 },
		{ VDCP_ABORT_COPY_FILE_TO	,0x20,0x52,0x05,0x00 },

		{ VDCP_OPEN_PORT			,0x30,0x01,0x04,0x01 },
		{ VDCP_NEXT					,0x30,0x02,0x02,0x52 },
		{ VDCP_LAST					,0x30,0x03,0x02,-1 },

		{ VDCP_PORT_STATUS_REQ		,0x30,0x05,0x03,-1 },
		{ VDCP_POSITION_REQ			,0x30,0x06,0x03,0x05 },
		{ VDCP_ACTIVE_ID_REQ		,0x30,0x07,0x02,0x09 },
		{ VDCP_DEV_TYPE_REQ			,0x30,0x08,0x02,-1 },

		{ VDCP_SYSTEM_STATUS_REQ	,0x30,0x10,0x03,-1 },
		{ VDCP_ID_LIST				,0x30,0x11,0x02,0x52 },
		{ VDCP_ID_SIZE_REQ			,0x30,0x14,0x0A,0x04 },
		{ VDCP_ID_ADDED_TO_ARCH		,0x30,0x15,0x02,0x52 },
		{ VDCP_ID_REQ				,0x30,0x16,0x0A,0x01 },
		{ VDCP_COMPR_SETTINGS_REQ	,0x30,0x17,0x03,-1 },
		{ VDCP_ID_ADDED_LIST		,0x30,0x18,0x02,0x52 },
		{ VDCP_ID_DELETED_LIST		,0x30,0x19,0x02,0x52 },

		{ VDCP_MULTI_PORT_STATUS_REQ,0x30,0x25,0x0A,0x00 },	// ?
		{ VDCP_ABORT_MACRO			,0x30,0x61,0x0A,0x00 },	// ?
		{ VDCP_ACTIVE_MACRO_LIST	,0x30,0x62,0x0A,0x00 },	// ?
		{ VDCP_MACRO_COPY_FILE_TO	,0x30,0x63,0x0A,0x00 },	// ?
		{ VDCP_MACRO_GET_FROM_ARCH	,0x30,0x64,0x0A,0x00 },	// ?
		{ VDCP_MACRO_SEND_TO_ARCH	,0x30,0x65,0x0A,0x00 },	// ?

		{ VDCP_PREPARE_ID_TO_PLAY	,0x30,0x66,0x0A,0x00 },	// ?
		{ VDCP_CLOSE_ID_FROM_PLAY	,0x30,0x67,0x0A,0x00 },	// ?

		{ 0 }
	};

	for (VDCP_CMD* vdcp = global_VDCP; vdcp->CMDID > 0; vdcp++)
	{
		AddCmd(vdcp);
	}
};

CProtocol_VDCP::VDCP_CMD* CProtocol_VDCP::GetByCMDID(int nCMD)
{
	VDCP_CMD* pCmd = NULL;
	for (int i = 0;i < m_CMD_ByCMDID.size();i++)
	{
		pCmd = m_CMD_ByCMDID[i];
		if (pCmd && pCmd->CMDID == nCMD)
		{
			break;
		}

	}
	return pCmd;
};

CProtocol_VDCP::VDCP_CMD* CProtocol_VDCP::GetCmdIDByCmd(int nCmd1, int nCmd2)
{
	if ((nCmd1 == 0) && (nCmd2 == 0))
	{
		return NULL;
	}

	VDCP_CMD* pCmd = NULL;
	for (int i = 0; i< m_CMD_ByCMDID.size(); i++)
	{
		if ((m_CMD_ByCMDID[i]->CMD1 == nCmd1) && (m_CMD_ByCMDID[i]->CMD2 == nCmd2))
		{
			pCmd = m_CMD_ByCMDID[i];
			break;
		}

	}
	return pCmd;
}
void CProtocol_VDCP::AddCmd(VDCP_CMD* pCmd)
{
	m_CMD_ByCMDID.push_back(pCmd);
};

struct VDCPProtocolStrategy::impl
{
public:
	
private:
	typedef CProtocol_VDCP::VDCP_CMD VDCP_CMD;
	std::vector<VDCPCommandQueue::ptr_type>		commandQueues_;
	spl::shared_ptr<vdcp_command_repository>	repo_;
	CProtocol_VDCP *	m_pProtocol;				   //所用协议
	std::list<std::wstring>	history_;//参数列表，用之前要清理，如果是关联的参数不用清理
	std::wstring				ack;
	std::wstring				nak;
	std::wstring				openportstring;//查询状态需要将这个参数带进history中
	int channel_index ;//这个参数是配置文件中得来的，暂时在这里写死
	int layer_index;//这个值可以是固定值也可在配置文件中写

public:
	impl(const std::wstring& name, const spl::shared_ptr<vdcp_command_repository>& repo,int channel,int layer)
		: repo_(repo)
	{
		channel_index = channel>1?channel-1:0;
		layer_index = layer;
		openportstring = L"";
		m_pProtocol = CProtocol_VDCP::GetDefProtocol();
		ack = L"04";
		nak = L"05";
		commandQueues_.push_back(spl::make_shared<VDCPCommandQueue>(L"General Queue for " + name));
		for (int i = 0; i < repo_->channels().size(); ++i)
		{
			commandQueues_.push_back(spl::make_shared<VDCPCommandQueue>(
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
		VDCPCommand::ptr_type						command;
		error_state									error			= error_state::no_error;
		std::shared_ptr<VDCPCommandQueue>			queue;
	};

	
	//校验 协议格式或者码不对都要返回错误
	bool  SpellCheck(std::wstring message)
	{
		//vdcp协议的长度必须大于5个字节
		//一个头数居+ 一个参数长度 一个校验位 + 两个命令位 表示数据不完整
		if (message.size()<10)
		{
			CASPAR_LOG(error) << L"<vdcp> the command missing data";
			return false;
		}
		std::wstring comhead = message.substr(0, 2);
		
		if (boost::lexical_cast<HexTo<int>>(comhead) != VDCP_RET_DATA)
		{
			CASPAR_LOG(error) << L"<vdcp> the command head error must is 0x02";
			return false;
		}
		//验证长度
		//信息中存在的表示数据的长度
		int len_text = boost::lexical_cast<HexTo<int>>(message.substr(2,2))*2;
		//信息中的长度加上三个字节的信息的长度 一个头数居+ 一个参数长度 加上一个校验位,所以要加上 3
		int datalen_text = len_text + 6;
		if (message.size()!=datalen_text)
		{
			CASPAR_LOG(error) << L"<vdcp> check miss data!";
			return false;
		}
		//校验和
		unsigned long Sum = 0;
		//头 长度  data（只对data校验）
		for (int i = 4;i < message.size();i+=2)//把ES也加上
		{
			Sum += boost::lexical_cast<HexTo<int>>(message.substr(i,2));
		}
		Sum = Sum & 0xFF;

		if (Sum != 0)
		{
			CASPAR_LOG(error) << L"<vdcp>  check Sum Error";
			return false;			// 校验和检验错误
		}
		return true;
	}
	void Parse(const std::wstring& message, ClientInfoPtr client)
	{
		CASPAR_LOG_COMMUNICATION(info) << L"VDCP message from " << client->address() << ": " << message << L"\\r\\n";
		//校正message,出错返回nak
		if (!SpellCheck(message))
		{
			std::wstringstream answer;
			answer << nak;
			client->send(answer.str());
			return;
		}
		command_interpreter_result result;
		if (interpret_command_string(message, result, client))
		{
			if (result.lock && !result.lock->check_access(client))
				result.error = error_state::access_error;
			else
				result.queue->AddCommand(result.command);
		}
		else
		{
			std::wstringstream answer;
			answer << ack;
			client->send(answer.str());
		}
	}

private:
bool interpret_command_string(const std::wstring& message, command_interpreter_result& result, ClientInfoPtr client)
{
	try
	{
		std::string str;
		bool is_channel_command = false;//是否是带有chanel的信息的判断
		// 查找命令	
		char  cmd1 = 0;
		int cmdsd =boost::lexical_cast<HexTo<int>>(message.substr(4, 2));
		if ( cmdsd > 0x80)
		{
			cmd1 = cmdsd - 0x80; //新协议
		}
		else
		{
			cmd1 = cmdsd;	  //老协议
		}
		cmdsd = boost::lexical_cast<HexTo<int>>(message.substr(6, 2));
		//切换客户端的代码
		/*	std::wstring protocal;
			std::wstring ID;
			int channel;
			env::getSwitchMode(protocal, channel, ID);*/

		/*if (!((protocal == L"VDCP" && (m_channel == channel || channel == 0)) || (protocal == L"") || (protocal == L"NULL")))
		//		{
		//			if (pCmd->CMDID == VDCP_PLAY_CUE || pCmd->CMDID == VDCP_CUE_WITH_DATA ||
		//				pCmd->CMDID == VDCP_PLAY || pCmd->CMDID == VDCP_STOP ||
		//				pCmd->CMDID == VDCP_STILL ||
		//				pCmd->CMDID == VDCP_CONTINUE)
		//			{
		//				std::wstring relaystring;
		//				std::wstring protocal;
		//				std::wstring ID;
		//				int channel = 0;

		//				relaystring += L"400 err\r\nprotocol " + protocal + L" channel " + boost::lexical_cast<std::wstring>(channel)
		//					+ L" ID " + ID;
		//				relaystring += L"\r\n";
		//				CASPAR_LOG(debug) << L"VDCP:" << relaystring;
		//				return -1;
		//			}
		//		}*/

		VDCP_CMD* pCmd = m_pProtocol->GetCmdIDByCmd(cmd1, cmdsd);
		if (!pCmd)
		{
			CASPAR_LOG(error) << L"<vdcp> no find the matching command";
			history_.clear();
			result.command_name = L"NAK";
			is_channel_command = false;
			history_.push_back(message);
			
		}
		else
		{
			switch (pCmd->CMDID)
			{

			case VDCP_PLAY_CUE:		 //新老协议这个地方不同新协议多了一个文件名称的长度标识
			{
				history_.clear();
				result.command_name = L"CUE";
				is_channel_command = true;
				history_.push_back(message);
			}
			break;
			case VDCP_CUE_WITH_DATA:	//	新老协议这个地方不同新协议多了一个文件名称的长度标识
			{
				history_.clear();
				result.command_name = L"CUEWITHDATA";
				is_channel_command = true;
				history_.push_back(message);
			}
			break;
			case VDCP_PLAY:
			{
				history_.clear();
				result.command_name = L"PLAY";
				is_channel_command = true;
				history_.push_back(message);
			}
			break;
			case VDCP_STOP:
			{
				history_.clear();
				result.command_name = L"STOP";
				is_channel_command = true;
				history_.push_back(message);

			}
			break;
			case VDCP_PORT_STATUS_REQ:
			{
				history_.clear();
				result.command_name = L"PORTSTATUS";
				is_channel_command = true;
				history_.push_back(openportstring);
				history_.push_back(message);
			}
			break;
			case VDCP_ID_SIZE_REQ://查看文件大小
			{
				history_.clear();
				result.command_name = L"CINF";
				is_channel_command = false;
				history_.push_back(message);
			}
			break;
			case VDCP_ID_REQ://文件是否存在
			{

				history_.clear();
				result.command_name = L"IDEXIST";
				is_channel_command = false;
				history_.push_back(message);
			}
			break;
			case VDCP_STILL:
			{

				history_.clear();
				result.command_name = L"STILL";
				is_channel_command = true;
				history_.push_back(message);
			}
			break;
			case VDCP_CONTINUE:
			{

				history_.clear();
				result.command_name = L"CONTINUE";
				is_channel_command = true;
				history_.push_back(message);
			}
			break;
			case VDCP_ID_LIST:
			{
				history_.clear();
				result.command_name = L"IDLIST";
				is_channel_command = false;
				history_.push_back(message);
			}
			break;
			case VDCP_NEXT:
			{
				history_.clear();
				result.command_name = L"NEXTDATA";
				is_channel_command = false;
				history_.push_back(message);
			}
			break;
			case VDCP_OPEN_PORT:
			{
				history_.clear();
				result.command_name = L"OPENPORT";
				is_channel_command = false;
				history_.push_back(message);
				openportstring = message;//记录openport命令，laystatus命令需要用的参数
			}
			break;
			case VDCP_SELECT_PORT:
			{
				history_.clear();
				result.command_name = L"ACK";
				is_channel_command = false;
				history_.push_back(message);
			}
			break;
			case VDCP_CLOSE_PORT:
			{
				history_.clear();
				result.command_name = L"ACK";
				is_channel_command = false;
				history_.push_back(message);
			}
			break;
			default:
			{
				history_.clear();
				result.command_name = L"NAK";
				is_channel_command = false;
				history_.push_back(message);
				CASPAR_LOG(error) << L"Don't support the command of vdcp! text:" << str;
			}
			break;
			}
		}
		
		if (is_channel_command)
		{
			result.command = repo_->create_channel_command(result.command_name, client, channel_index, layer_index, history_);

			if (result.command)
			{
				result.lock = repo_->channels().at(channel_index).lock;
				result.queue = commandQueues_.at(channel_index + 1);
			}
			else
			{
				CASPAR_LOG(error) << L"<vdcp> result.command false";
			}
		}
		else
		{
			result.command = repo_->create_command(result.command_name, client, history_);

			if (result.command)
				result.queue = commandQueues_.at(0);
		}

		if (!result.command)
			result.error = error_state::command_error;
		else
		{
			std::vector<std::wstring> parameters(history_.begin(), history_.end());

			result.command->parameters() = std::move(parameters);

			if (result.command->parameters().size() < result.command->minimum_parameters())
				result.error = error_state::parameters_error;
		}
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

VDCPProtocolStrategy::VDCPProtocolStrategy(const std::wstring& name, const spl::shared_ptr<vdcp_command_repository>& repo,int channel,int layer)
	: impl_(spl::make_unique<impl>(name, repo,channel,layer))
{
}
VDCPProtocolStrategy::~VDCPProtocolStrategy() {}
void VDCPProtocolStrategy::Parse(const std::wstring& msg, IO::ClientInfoPtr pClientInfo) { impl_->Parse(msg, pClientInfo); }


}	//namespace vdcp
}}	//namespace caspar
