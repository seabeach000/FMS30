/*
* Copyright 2013 Sveriges Television AB http://casparcg.com/
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

#include "../util/util.h"

#include <common/memory.h>

#include <memory>
#include <string>
#include <cstdint>
#include <future>

#include <boost/noncopyable.hpp>
#include <boost/rational.hpp>

#define invalid_afd_code -1

struct AVFormatContext;
struct AVPacket;

namespace caspar {

namespace diagnostics {

class graph;

}

namespace ffmpeg {

class input : boost::noncopyable
{
public:
	explicit input(const spl::shared_ptr<diagnostics::graph>& graph, const std::wstring& url_or_file, bool loop, uint32_t start, uint32_t length, bool thumbnail_mode, const ffmpeg_options& vid_params);

	bool								try_pop(std::shared_ptr<AVPacket>& packet);
	bool								eof() const;

	void								start(uint32_t value);
	uint32_t							start() const;
	void								length(uint32_t value);
	uint32_t							length() const;
	void								loop(bool value);
	bool								loop() const;

	int									num_audio_streams() const;

	std::future<bool>					seek(uint32_t target);

	spl::shared_ptr<AVFormatContext>	context();

	bool                                hasUpdateAVstarttime();
	uint32_t							source_track_orign();
	double length_time();// seek add1
	uint32_t start_position();//Omn Seek
	unsigned source_afd_code;
private:
	struct implementation;
	std::shared_ptr<implementation> impl_;
};


}}
