//
// Created by zibj 2016/10/25.
//

#pragma once

#include <common/memory.h>

#include <core/fwd.h>

#include <vector>
#include <boost/property_tree/ptree.hpp>


namespace caspar {	namespace dshow	{

	void describe_consumer(core::help_sink& sink, const core::help_repository& repo);

	spl::shared_ptr<core::frame_consumer> create_consumer(
		const std::vector<std::wstring>& params, 
		core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels);

	spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(
		const boost::property_tree::wptree& ptree, 
		core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels);
}}