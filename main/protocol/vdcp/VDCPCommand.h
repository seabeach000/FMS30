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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CasparCG. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Nicklas P Andersson
*/

#pragma once

#include "../util/ClientInfo.h"
#include "vdcp_shared.h"
#include <core/consumer/frame_consumer.h>
#include <core/producer/frame_producer.h>
#include <accelerator/ogl/util/device.h>

#include <boost/algorithm/string.hpp>

namespace caspar { namespace protocol {

namespace vdcp {
	template <typename ElemT>
	struct HexTo {
		ElemT value;
		operator ElemT() const { return value; }
		friend std::wistream& operator >> (std::wistream& in, HexTo& out) {
			in >> std::hex >> out.value;
			return in;
		}
	};
	enum {
		// System Command
		VDCP_LOCAL_DISABLE = 1,
		VDCP_LOCAL_ENABLE,
		VDCP_DELETE_FROM_ARCH,
		VDCP_DELETE_PROTECT_ID,
		VDCP_UNDEL_PROTECT_ID,

		// Immediate command
		VDCP_STOP, //6
		VDCP_PLAY,
		VDCP_RECORD,
		VDCP_FREEZE,
		VDCP_STILL,//10

		VDCP_STEP,
		VDCP_CONTINUE,
		VDCP_JOG,
		VDCP_JOG_FAR,
		VDCP_VARI_PLAY,//15

		VDCP_UNFREEZE,
		VDCP_EE_MODE,
		VDCP_TGA,
		VDCP_RENAME_ID,
		VDCP_PRESET_STD_TIME,//20

		VDCP_NEW_COPY,
		VDCP_SORT_MODE,
		VDCP_CLOSE_PORT,
		VDCP_SELECT_PORT,
		VDCP_RECORD_INIT, //25

		VDCP_PLAY_CUE,
		VDCP_CUE_WITH_DATA,
		VDCP_DELETE_ID,
		VDCP_GET_FROM_ARCH,
		VDCP_CLEAR,//30

		VDCP_SEND_TO_ARCH,
		VDCP_TO_SIGNAL_FULL,
		VDCP_REC_INIT_WITH_DATA,
		VDCP_SELECT_LOGICAL_DRV,
		VDCP_SYSTEM_DELETE_ID,//35

		VDCP_PRESET,
		VDCP_V_COMPR_RATE,
		VDCP_A_SAMPLE_RATE,
		VDCP_A_COMPR_RATE,
		VDCP_A_IN_LEVEL,//40

		VDCP_A_OUT_LEVEL,
		VDCP_V_COMPR_PARAM,
		VDCP_SELECT_OUTPUT,
		VDCP_SELECT_INPUT,
		VDCP_RECORD_MODE,//45

		VDCP_SC_ADJUST,
		VDCP_H_POS_ADJUST,
		VDCP_DISK_PREROLL,
		VDCP_COPY_FILE_TO,
		VDCP_DELETE_FILE_FROM,//50

		VDCP_ABORT_COPY_FILE_TO,
		// Preset/Select Command
		VDCP_OPEN_PORT,
		VDCP_NEXT,
		VDCP_LAST,
		VDCP_PORT_STATUS_REQ, //55

		VDCP_POSITION_REQ,
		VDCP_ACTIVE_ID_REQ,
		VDCP_DEV_TYPE_REQ,
		VDCP_SYSTEM_STATUS_REQ,
		VDCP_ID_LIST,//60

		VDCP_ID_SIZE_REQ,
		VDCP_ID_ADDED_TO_ARCH,
		VDCP_ID_REQ,
		VDCP_COMPR_SETTINGS_REQ,
		VDCP_ID_ADDED_LIST,//65

		VDCP_ID_DELETED_LIST,
		VDCP_MULTI_PORT_STATUS_REQ,

		// Marco Command
		VDCP_ABORT_MACRO,
		VDCP_ACTIVE_MACRO_LIST,
		VDCP_MARCO_STATUS,//70

		VDCP_MACRO_COPY_FILE_TO,
		VDCP_MACRO_GET_FROM_ARCH,
		VDCP_MACRO_SEND_TO_ARCH,
		VDCP_PREPARE_ID_TO_PLAY,
		VDCP_CLOSE_ID_FROM_PLAY,//75

		VDCP_LAST_COMMAND,
		CLS_INFO,


	};


	// 返回数据类型
	enum {
		VDCP_RET_DATA = 0x02,
		VDCP_RET_ACK = 0x04,
		VDCP_RET_NAK = 0x05,
	};


	// 端口状态
	// PS = PORT STATUS
	enum STATUS_VDCP{
		VDCP_PS_STATE = 0x01,	//0-7:IDLE,CUE/INIT,PLAY/REC,STILL,JOG,VARPLAY,BUSY,CUEDONE
		VDCP_PS_MEDIA_STATUS = 0x02,	//0-7:
		VDCP_PS_ERRORS = 0x04,	// 
		VDCP_PS_SETTING = 0x08,	// 
		VDCP_PS_COMPRESSION_TYPE = 0x10,	// 
		VDCP_PS_STATEEX = 0x0F,   // = VDCP_PS_STATE | VDCP_PS_MEDIA_STATUS |  VDCP_PS_ERRORS | VDCP_PS_SETTING
	};// See DevPortStatusReq


	enum {
		VDCP_PORT_STATE_IDLE = 0x01,
		VDCP_PORT_STATE_CUE = 0x02,
		VDCP_PORT_STATE_PLAY_REC = 0x04,
		VDCP_PORT_STATE_STILL = 0x08,
		VDCP_PORT_STATE_JOG = 0x10,
		VDCP_PORT_STATE_SHUTTLE = 0x20,
		VDCP_PORT_STATE_PORT_BUSY = 0x40,
		VDCP_PORT_STATE_CUE_DONE = 0x80
	};// 当 PortStatus == VDCP_PS_STATE 时返回数值的定义

	enum {
		VDCP_PORT_STATE_ERROR_SYSTEMERROR = 0x01,
		VDCP_PORT_STATE_ERROR_ILLEGALVAL = 0x02,
		VDCP_PORT_STATE_ERROR_INVALIDPORT = 0x04,
		VDCP_PORT_STATE_ERROR_WRONGPORTTYPE = 0x08,
		VDCP_PORT_STATE_ERROR_PORTLOCKED = 0x10,
		VDCP_PORT_STATE_ERROR_NOTENOUGHDISKSPACE = 0x20,
		VDCP_PORT_STATE_ERROR_CMDWHILEBUSY = 0x40,
		VDCP_PORT_STATE_ERROR_NOTSUPPORTED = 0x40,

		VDCP_PORT_STATE_ERROR_INVALIDID = 0x100,
		VDCP_PORT_STATE_ERROR_IDNOTFOUND = 0x200,
		VDCP_PORT_STATE_ERROR_IDALREADYEXISTS = 0x400,
		VDCP_PORT_STATE_ERROR_IDSTILLRECORDING = 0x800,
		VDCP_PORT_STATE_ERROR_IDCUEDORPLAYING = 0x1000,
		VDCP_PORT_STATE_ERROR_XFERFAILED = 0x2000,
		VDCP_PORT_STATE_ERROR_XFERCOMPLETE = 0x4000,
		VDCP_PORT_STATE_ERROR_IDDELETEPROTECTED = 0x8000,


		VDCP_PORT_STATE_ERROR_NOTINCUESTATE = 0x10000,
		VDCP_PORT_STATE_ERROR_CUENOTDONE = 0x20000,
		VDCP_PORT_STATE_ERROR_PORTNOTIDLE = 0x40000,
		VDCP_PORT_STATE_ERROR_PORTACTIVE = 0x80000,
		VDCP_PORT_STATE_ERROR_PORTIDLE = 0x100000,
		VDCP_PORT_STATE_ERROR_OPERATIONFAILED = 0x200000,
		VDCP_PORT_STATE_ERROR_SYSTEMREBOOT = 0x800000
	};// 当 PortStatus == VDCP_PS_ERRORS 时返回数值的定义



	  // 系统状态
	  // SS = System Status
	enum
	{
		VDCP_SS_STORAGE = 0x01,
		VDCP_SS_NUM_OF_ID = 0x02,
		VDCP_SS_DISK_STATUS = 0x04,		// 0-7: DiskFull,SystemDown,DiskDown,RemoteDisable
		VDCP_SS_SUB_SYSTEM = 0x08,
		VDCP_SS_STD_TIME = 0x10,
		VDCP_SS_SIGNAL_FULL_LVL = 0x20,
	};	// See DevSystemStatusReq



	struct command_context
	{
		IO::ClientInfoPtr										client;
		channel_context											channel;
		int														channel_index;
		int														layer_id;
		std::vector<channel_context>							channels;
		spl::shared_ptr<core::help_repository>					help_repo;
		spl::shared_ptr<core::media_info_repository>			media_info_repo;
		spl::shared_ptr<core::cg_producer_registry>				cg_registry;
		spl::shared_ptr<core::system_info_provider_repository>	system_info_repo;
		std::shared_ptr<core::thumbnail_generator>				thumb_gen;
		spl::shared_ptr<const core::frame_producer_registry>	producer_registry;
		spl::shared_ptr<const core::frame_consumer_registry>	consumer_registry;
		std::shared_ptr<accelerator::ogl::device>				ogl_device;
		std::promise<bool>&										shutdown_server_now;
		std::vector<std::wstring>								parameters;

		int layer_index(int default_ = 0) const { return layer_id == -1 ? default_: layer_id; }

		command_context(
				IO::ClientInfoPtr client,
				channel_context channel,
				int channel_index,
				int layer_id,
				std::vector<channel_context> channels,
				spl::shared_ptr<core::help_repository> help_repo,
				spl::shared_ptr<core::media_info_repository> media_info_repo,
				spl::shared_ptr<core::cg_producer_registry> cg_registry,
				spl::shared_ptr<core::system_info_provider_repository> system_info_repo,
				std::shared_ptr<core::thumbnail_generator> thumb_gen,
				spl::shared_ptr<const core::frame_producer_registry> producer_registry,
				spl::shared_ptr<const core::frame_consumer_registry> consumer_registry,
				std::shared_ptr<accelerator::ogl::device> ogl_device,
				std::promise<bool>& shutdown_server_now)
			: client(std::move(client))
			, channel(channel)
			, channel_index(channel_index)
			, layer_id(layer_id)
			, channels(std::move(channels))
			, help_repo(std::move(help_repo))
			, media_info_repo(std::move(media_info_repo))
			, cg_registry(std::move(cg_registry))
			, system_info_repo(std::move(system_info_repo))
			, thumb_gen(std::move(thumb_gen))
			, producer_registry(std::move(producer_registry))
			, consumer_registry(std::move(consumer_registry))
			, ogl_device(std::move(ogl_device))
			, shutdown_server_now(shutdown_server_now)
		{
		}
	};

	typedef std::function<std::wstring(command_context& args)> vdcp_command_func;

	class VDCPCommand
	{
	private:
		command_context		ctx_;
		vdcp_command_func	command_;
		int					min_num_params_;
		std::wstring		name_;
		std::wstring		replyString_;
	public:
		VDCPCommand(const command_context& ctx, const vdcp_command_func& command, int min_num_params, const std::wstring& name)
			: ctx_(ctx)
			, command_(command)
			, min_num_params_(min_num_params)
			, name_(name)
		{
		}

		typedef std::shared_ptr<VDCPCommand> ptr_type;

		bool Execute()
		{
			SetReplyString(command_(ctx_));
			return true;
		}

		int minimum_parameters() const
		{
			return min_num_params_;
		}

		void SendReply()
		{
			if (replyString_.empty())
				return;

			ctx_.client->send(std::move(replyString_));
		}

		std::vector<std::wstring>& parameters() { return ctx_.parameters; }

		IO::ClientInfoPtr client() { return ctx_.client; }

		std::wstring print() const
		{
			return name_;
		}

		void SetReplyString(const std::wstring& str)
		{
			replyString_ = str;
		}
	};
}}}
