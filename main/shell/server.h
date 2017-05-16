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

#include <common/memory.h>
#include <common/future_fwd.h>

#include <core/monitor/monitor.h>
#include <core/fwd.h>

#include <boost/noncopyable.hpp>

#include <vector>

FORWARD3(caspar, protocol, amcp, class amcp_command_repository);
FORWARD3(caspar, protocol, vdcp, class vdcp_command_repository);

namespace caspar {
	enum {
		VDCP_PORT_STATE_IDLE = 0x01,
		VDCP_PORT_STATE_CUE = 0x02,
		VDCP_PORT_STATE_PLAY_REC = 0x04,
		VDCP_PORT_STATE_STILL = 0x08,
		VDCP_PORT_STATE_JOG = 0x10,
		VDCP_PORT_STATE_SHUTTLE = 0x20,
		VDCP_PORT_STATE_PORT_BUSY = 0x40,
		VDCP_PORT_STATE_CUE_DONE = 0x80
	};
class server final : public boost::noncopyable
{
public:
	explicit server(std::promise<bool>& shutdown_server_now,int channel_nums);
	void start();
	spl::shared_ptr<core::system_info_provider_repository> get_system_info_provider_repo() const;
	spl::shared_ptr<protocol::amcp::amcp_command_repository> get_amcp_command_repository() const;
	spl::shared_ptr<protocol::vdcp::vdcp_command_repository> get_vdcp_command_repository() const;

	core::monitor::subject& monitor_output();
private:
	struct impl;
	spl::shared_ptr<impl> impl_;
};

}