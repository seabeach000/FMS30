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

#pragma once

#include "../util/ProtocolStrategy.h"

#include <core/video_channel.h>
#include <core/thumbnail_generator.h>
#include <core/producer/media_info/media_info_repository.h>
#include <core/producer/cg_proxy.h>
#include <core/system_info_provider.h>

#include <common/memory.h>

#include <boost/noncopyable.hpp>

#include <string>
#include <future>

namespace caspar { namespace protocol { namespace vdcp {
	

class VDCPProtocolStrategy : public IO::IProtocolStrategy, boost::noncopyable
{
public:
	VDCPProtocolStrategy(const std::wstring& name, const spl::shared_ptr<class vdcp_command_repository>& repo,int channel,int layer);

	virtual ~VDCPProtocolStrategy();

	virtual void Parse(const std::wstring& msg, IO::ClientInfoPtr pClientInfo);
	virtual std::string GetCodepage() const { return "UTF-8"; }

private:
	struct impl;
	spl::unique_ptr<impl> impl_;
};
class  CProtocol_VDCP
{
public:
	CProtocol_VDCP();
	~CProtocol_VDCP() {};
public:
	typedef  struct	VDCP_CMD {
		int		CMDID;	// 命令ID
		int		CMD1;
		int		CMD2;
		int		ParamLen;	// 0 表示自己填写
		int		RetLen;
		// 00 表示 VDCP_RET_ACK, 其他表示 VDCP_RET_DATA
		// VDCP_RET_ACK	表示不关系返回的数据
	}VDCP_CMD;

public:
	void AddCmd(VDCP_CMD* pCmd);

public:
	std::vector  <VDCP_CMD*> m_CMD_ByCMDID;
	VDCP_CMD* GetByCMDID(int nID);
	VDCP_CMD* GetCmdIDByCmd(int nCmd1, int nCmd2);

public:
	static CProtocol_VDCP* GetDefProtocol();

};
}}}
