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

#include <core/fwd.h>

#include <string>
#include <vector>

namespace caspar { namespace decklink {
	//logo killer
	//----------------------------
	struct logo_killer_params
	{
		bool                logo_killer_enable;
		int                 logo_killer_left;
		int                 logo_killer_top;
		int                 logo_killer_width;
		int                 logo_killer_height;
		bool                logo_killer_is_smooth;
		int                 logo_killer_smooth_value;
		logo_killer_params()
			: logo_killer_enable(false)
			, logo_killer_left(-1)
			, logo_killer_top(-1)
			, logo_killer_width(-1)
			, logo_killer_height(-1)
			, logo_killer_is_smooth(true)
			, logo_killer_smooth_value(10)
		{
		}
	};
void describe_producer(core::help_sink& sink, const core::help_repository& repo);
spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params);

}}
