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

#include "StdAfx.h"

#include "video_channel.h"

#include "video_format.h"

#include "producer/stage.h"
#include "mixer/mixer.h"
#include "consumer/output.h"
#include "frame/frame.h"
#include "frame/draw_frame.h"
#include "frame/frame_factory.h"
#include "frame/audio_channel_layout.h"

#include <common/diagnostics/graph.h>
#include <common/env.h>
#include <common/lock.h>
#include <common/executor.h>
#include <common/timer.h>
#include <common/future.h>

#include <core/mixer/image/image_mixer.h>
#include <core/diagnostics/call_context.h>

#include <tbb/spin_mutex.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <unordered_map>

//wxg20170222
#include <core/frame/pixel_format.h>
#include <core/frame/frame.h>
#include <common/memcpy.h>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>
#include <common/prec_timer.h>

using namespace boost::interprocess;
namespace caspar { namespace core {

struct video_channel::impl final
{
	spl::shared_ptr<monitor::subject>					monitor_subject_;

	const int											index_;

	mutable tbb::spin_mutex								format_desc_mutex_;
	core::video_format_desc								format_desc_;
	mutable tbb::spin_mutex								channel_layout_mutex_;
	core::audio_channel_layout							channel_layout_;

	const spl::shared_ptr<caspar::diagnostics::graph>	graph_					= [](int index)
																				  {
																					  core::diagnostics::scoped_call_context save;
																					  core::diagnostics::call_context::for_thread().video_channel = index;
																					  return spl::make_shared<caspar::diagnostics::graph>();
																				  }(index_);

	caspar::core::output								output_;
	std::future<void>									output_ready_for_frame_	= make_ready_future();
	spl::shared_ptr<image_mixer>						image_mixer_;
	caspar::core::mixer									mixer_;
	caspar::core::stage									stage_;

	mutable tbb::spin_mutex								tick_listeners_mutex_;
	int64_t												last_tick_listener_id = 0;
	std::unordered_map<int64_t, std::function<void()>>	tick_listeners_;

	executor											executor_				{ L"video_channel " + boost::lexical_cast<std::wstring>(index_) };

	std::vector<spl::shared_ptr<afd_item>> afd_items;

	bool                                                isDelayEnable_ = false;
	file_mapping										fileMap_read_;
	file_mapping                                        fileMap_write_;
	mapped_region                                       region_read_;
	mapped_region                                       region_write_;
	std::size_t                                         totalFrames_;
	//const int64_t                                       flushFrequency_ = 1;   //单位帧
	const int64_t                                       fileMappingFrequency_ = 1;
	int64_t                                             firstReadInterval_ = 0;
	int64_t												regionIndex_;
	int64_t												currentFrameNum_;
	int64_t											    regionIndexR_;
	//int64_t		                                        currentFrameNumR_;
	executor											producer_executor_{ L"video_channel_Producer " + boost::lexical_cast<std::wstring>(index_) };
	executor											consumer_executor_{ L"video_channel_Consumer " + boost::lexical_cast<std::wstring>(index_) };
	//prec_timer							                sync_timerProuducer_;
	int64_t                                             regoinIndexMax_;
	executor											flush_executor_{ L"video_channel_Consumer " + boost::lexical_cast<std::wstring>(index_) };

	bool                                                isInternalDelay_ = false;
	tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
public:
	impl(
			int index,
			const core::video_format_desc& format_desc,
			const core::audio_channel_layout& channel_layout,
			std::unique_ptr<image_mixer> image_mixer)
		: monitor_subject_(spl::make_shared<monitor::subject>(
				"/channel/" + boost::lexical_cast<std::string>(index)))
		, index_(index)
		, format_desc_(format_desc)
		, channel_layout_(channel_layout)
		, output_(graph_, format_desc, channel_layout, index)
		, image_mixer_(std::move(image_mixer))
		, mixer_(index, graph_, image_mixer_)
		, stage_(index, graph_)
	{
		graph_->set_color("tick-time", caspar::diagnostics::color(0.0f, 0.6f, 0.9f));
		graph_->set_color("write-time", caspar::diagnostics::color(0.9f, 0.9f, 0.9f));
		graph_->set_color("ticksrc-time", caspar::diagnostics::color(0.0f, 0.6f, 0.6f));
		graph_->set_text(print());
		caspar::diagnostics::register_graph(graph_);

		output_.monitor_output().attach_parent(monitor_subject_);
		mixer_.monitor_output().attach_parent(monitor_subject_);
		stage_.monitor_output().attach_parent(monitor_subject_);

		//wxg20170301
		int delayFrames = boost::lexical_cast<int>(format_desc.delayFrames);
		if (delayFrames > 0 && delayFrames <= 15000)
		{
			if (delayFrames <= 15)
				isInternalDelay_ = true;
			else
				isDelayEnable_ = true;
		}

		if (isDelayEnable_)
		{
			currentFrameNum_ = 0;
			regionIndex_ = 0;
			auto format_desc1 = video_format_desc();
			auto channel_layout1 = audio_channel_layout();
			audio_mixer		audio_mixer_{ graph_ };
			auto audio = audio_mixer_(format_desc1, channel_layout1);
			int frameSize = format_desc1.width * format_desc1.height * 4 + (int)audio.size()*sizeof(int32_t);
			totalFrames_ = (delayFrames / fileMappingFrequency_ + 0)*fileMappingFrequency_;

			firstReadInterval_ = fileMappingFrequency_;
			totalFrames_ += firstReadInterval_;
			totalFrames_ += fileMappingFrequency_;   
			regoinIndexMax_ = totalFrames_ / fileMappingFrequency_;

			regionIndexR_ = regionIndex_ + 1 + firstReadInterval_ / fileMappingFrequency_;  //regionindex 单位为fileMappingFrequency_

			//wxg20170307
			regionIndexR_ += 12;   //提前12帧播放

			char* fileName = "D:\\famous.bin";
			createFileMapping(totalFrames_*frameSize, fileName);
			//producer_executor_.begin_invoke([=] {srcTick(); });
			//consumer_executor_.begin_invoke([=] {dstTick(); });
			executor_.begin_invoke([=] {tick_new(); });
		}
		else if(isInternalDelay_)
		{
			frame_buffer_.set_capacity(delayFrames);
			producer_executor_.begin_invoke([=] {srcTick(); });
			consumer_executor_.begin_invoke([=] {dstTick(); });
			
		}
		else
		{
			executor_.begin_invoke([=] {tick(); });
		}

		CASPAR_LOG(info) << print() << " Successfully Initialized.";
	}

	~impl()
	{
		if (isDelayEnable_)
		{
			if (executor_.is_running())
			{
				executor_.stop();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
			}
			char* fileName = "D:\\famous.bin";
			removeFileMapping(fileName);
		}
		else if(isInternalDelay_)
		{
			if (producer_executor_.is_running())
			{
				producer_executor_.stop();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
				auto frame = const_frame::empty();
				frame_buffer_.try_pop(frame);
			}
			if (consumer_executor_.is_running())
			{
				consumer_executor_.stop();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
				frame_buffer_.try_push(core::const_frame::empty());
			}		
		}
		CASPAR_LOG(info) << print() << " Uninitializing.";
	}

	core::video_format_desc video_format_desc() const
	{
		return lock(format_desc_mutex_, [&]
		{
			return format_desc_;
		});
	}

	void video_format_desc(const core::video_format_desc& format_desc)
	{
		lock(format_desc_mutex_, [&]
		{
			format_desc_ = format_desc;
			stage_.clear();
		});
	}

	core::audio_channel_layout audio_channel_layout() const
	{
		return lock(channel_layout_mutex_, [&]
		{
			return channel_layout_;
		});
	}

	void audio_channel_layout(const core::audio_channel_layout& channel_layout)
	{
		lock(channel_layout_mutex_, [&]
		{
			channel_layout_ = channel_layout;
			stage_.clear();
		});
	}
	void invoke_tick_listeners()
	{
		auto listeners = lock(tick_listeners_mutex_, [=] { return tick_listeners_; });

		for (auto listener : listeners)
		{
			try
			{
				listener.second();
			}
			catch (...)
			{
				CASPAR_LOG_CURRENT_EXCEPTION();
			}
		}
	}
	//wxg20170222
	bool createFileMapping(int64_t size,char* fileName)
	{
		try
		{
			std::size_t page_size = mapped_region::get_page_size();
			std::size_t fileSize = (size / page_size + 1)*page_size;
			file_mapping::remove(fileName);
			std::filebuf fbuf;
			fbuf.open(fileName, std::ios_base::in | std::ios_base::out
				| std::ios_base::trunc | std::ios_base::binary);
			fbuf.pubseekoff(fileSize - 1, std::ios_base::beg);
			fbuf.sputc(0);

			fileMap_read_ = file_mapping(fileName, read_only);
			fileMap_write_ = file_mapping(fileName, read_write);
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}

		return true;
	}

	void removeFileMapping(char* fileName)
	{
		file_mapping::remove(fileName);
	}

	void srcTick()
	{
		try
		{

			auto format_desc = video_format_desc();
			auto channel_layout = audio_channel_layout();

			caspar::timer frame_timer;

			// Produce

			auto stage_frames = stage_(format_desc);

			// Mix

			auto mixed_frame = mixer_(std::move(stage_frames), format_desc, channel_layout);

			frame_buffer_.push(mixed_frame);
			//auto imageSize = mixed_frame.image_data().size();
			//int audio_frame_size = ((boost::iterator_range<const int32_t*>)mixed_frame.audio_data()).size() * sizeof(int32_t);
			//int mappedSize = imageSize + audio_frame_size;
			//regionIndex_ = regionIndex_%regoinIndexMax_;
			//if (currentFrameNum_%flushFrequency_ == 0)
			//{
			//	region_write_.flush();
			//	CASPAR_LOG(info) << "write write write   " << regionIndex_;
			//	mapped_region regionW(fileMap_write_, read_write, regionIndex_*mappedSize, flushFrequency_*mappedSize);
			//	region_write_.swap(regionW);
			//	currentFrameNum_ = 0;
			//	regionIndex_++;
			//	//通知可以更换Readindex
			//}
			//void* addr = region_write_.get_address();
			//std::uint8_t* dst = static_cast<std::uint8_t*>(addr) + currentFrameNum_*mappedSize;
			//std::uint8_t* dstAudio = dst + imageSize;
			//fast_memcpy((void*)dst, mixed_frame.image_data().begin(), mixed_frame.image_data().size());
			//fast_memcpy((void*)dstAudio, mixed_frame.audio_data().begin(), audio_frame_size);			
			//currentFrameNum_++;
			//sync_timerProuducer_.tick(1.0 / format_desc.fps);
			auto frame_time = frame_timer.elapsed()*format_desc.fps*0.5;
			graph_->set_value("ticksrc-time", frame_time);
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}

		if (producer_executor_.is_running())
			producer_executor_.begin_invoke([=] {srcTick(); });
	}

	void dstTick()
	{
		try
		{

			auto format_desc = video_format_desc();
			auto channel_layout = audio_channel_layout();

			caspar::timer frame_timer;

			const_frame frame = const_frame::empty();
			frame_buffer_.pop(frame);
			if(frame_buffer_.size() < 3)
				CASPAR_LOG(info) << "frame_buffer_  size   " << frame_buffer_.size();
			//audio_mixer		audio_mixer_{ graph_ };
			//auto image = (*image_mixer_)(format_desc, false);
			//auto audio = audio_mixer_(format_desc, channel_layout);
			//auto desc = core::pixel_format_desc(core::pixel_format::bgra);
			//desc.planes.push_back(core::pixel_format_desc::plane(format_desc.width, format_desc.height, 4));
			//frame = const_frame(std::move(image), std::move(audio), this, desc, channel_layout);

			//auto imageSize = frame.image_data().size();
			//int audio_frame_size = ((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);
			//int mappedSize = imageSize + audio_frame_size;
			//regionIndexR_ = regionIndexR_% regoinIndexMax_;
			////while(regionIndexR_-regionIndex_ != (1 + firstReadInterval_ / flushFrequency_))
			////{
			////	boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
			////}
			//if (currentFrameNumR_%flushFrequency_ == 0)
			//{	
			//	CASPAR_LOG(info) << "read read read   "<< regionIndexR_;
			//	mapped_region regionR(fileMap_read_, read_only, regionIndexR_*mappedSize, flushFrequency_*mappedSize);
			//	region_read_.swap(regionR);
			//	currentFrameNumR_ = 0;
			//	regionIndexR_++;
			//}
			//
			//void* addrR = region_read_.get_address();
			//std::uint8_t* src = static_cast<std::uint8_t*>(addrR) + currentFrameNumR_*mappedSize;
			//std::uint8_t* srcAudio = src + imageSize;
			//fast_memcpy((void*)frame.image_data().begin(), src, frame.image_data().size());
			//fast_memcpy((void*)frame.audio_data().begin(), srcAudio, audio_frame_size);
			//currentFrameNumR_++;

			// Consume
			output_ready_for_frame_ = output_(std::move(frame), format_desc, channel_layout);        //必须使用这句话来控制速度																									 
			output_ready_for_frame_.get();

			auto frame_time = frame_timer.elapsed()*format_desc.fps*0.5;
			graph_->set_value("tick-time", frame_time);

			*monitor_subject_ << monitor::message("/profiler/time") % frame_timer.elapsed() % (1.0 / format_desc_.fps)
				<< monitor::message("/format") % format_desc.name;
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}

		if (consumer_executor_.is_running())
			consumer_executor_.begin_invoke([=] {dstTick(); });
	}

	void tick_new()
	{
		try
		{

			auto format_desc = video_format_desc();
			auto channel_layout = audio_channel_layout();

			caspar::timer frame_timer;

			// Produce

			auto stage_frames = stage_(format_desc);

			// Mix

			auto mixed_frame = mixer_(std::move(stage_frames), format_desc, channel_layout);

			caspar::timer write_timer;
			//
			auto imageSize = mixed_frame.image_data().size();
			int audio_frame_size = (int)((boost::iterator_range<const int32_t*>)mixed_frame.audio_data()).size() * sizeof(int32_t);
			int mappedSize = (int)imageSize + audio_frame_size;
			regionIndex_ = regionIndex_%regoinIndexMax_;
			if (currentFrameNum_%fileMappingFrequency_ == 0)
			{
				mapped_region regionW(fileMap_write_, read_write, (int64_t)regionIndex_*(fileMappingFrequency_*mappedSize), fileMappingFrequency_*mappedSize);
				region_write_.swap(regionW);
				currentFrameNum_ = 0;
				regionIndex_ = (regionIndex_ + 1) % regoinIndexMax_;
			}
			void* addr = region_write_.get_address();

			std::uint8_t* dst = static_cast<std::uint8_t*>(addr) + currentFrameNum_*mappedSize;
			std::uint8_t* dstAudio = dst + imageSize;
			fast_memcpy((void*)dst, mixed_frame.image_data().begin(), mixed_frame.image_data().size());
			fast_memcpy((void*)dstAudio, mixed_frame.audio_data().begin(), audio_frame_size);
			//caspar::timer write_timer;
			//region_write_.flush(currentFrameNum_*mappedSize, mappedSize, true);
			flush_executor_.begin_invoke([=]
			{
				region_write_.flush(currentFrameNum_*mappedSize, mappedSize, true);
			});

			auto write_time = write_timer.elapsed()*format_desc.fps*0.5;
			graph_->set_value("write-time", write_time);
			//此时索引regionIndex_已经加一，但是帧数没变			
			if (currentFrameNum_ == 0)
			{
				mapped_region regionR(fileMap_read_, read_only, (int64_t)regionIndexR_*(fileMappingFrequency_*mappedSize), fileMappingFrequency_*mappedSize);
				region_read_.swap(regionR);
				regionIndexR_ = (regionIndexR_ + 1) % regoinIndexMax_;
			}
			const_frame frame = const_frame::empty();
			audio_mixer		audio_mixer_{ graph_ };
			auto image = (*image_mixer_)(format_desc, false);
			auto audio = audio_mixer_(format_desc, channel_layout);
			auto desc = core::pixel_format_desc(core::pixel_format::bgra);
			desc.planes.push_back(core::pixel_format_desc::plane(format_desc.width, format_desc.height, 4));
			frame = const_frame(std::move(image), std::move(audio), this, desc, channel_layout);
			//
			void* addrR = region_read_.get_address();
			std::uint8_t* src = static_cast<std::uint8_t*>(addrR) + currentFrameNum_*mappedSize;
			std::uint8_t* srcAudio = src + imageSize;
			fast_memcpy((void*)frame.image_data().begin(), src, mixed_frame.image_data().size());
			fast_memcpy((void*)frame.audio_data().begin(), srcAudio, audio_frame_size);
			currentFrameNum_++;

			// Consume

			output_ready_for_frame_ = output_(std::move(frame), format_desc, channel_layout);
			output_ready_for_frame_.get();

			auto frame_time = frame_timer.elapsed()*format_desc.fps*0.5;
			graph_->set_value("tick-time", frame_time);

			*monitor_subject_ << monitor::message("/profiler/time") % frame_timer.elapsed() % (1.0 / video_format_desc().fps)
				<< monitor::message("/format") % format_desc.name;
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}

		if (executor_.is_running())
			executor_.begin_invoke([=] {tick_new(); });
	}
	void tick()
	{
		try
		{
			invoke_tick_listeners();

			auto format_desc = video_format_desc();
			auto channel_layout = audio_channel_layout();

			caspar::timer frame_timer;

			// Produce

			auto stage_frames = stage_(format_desc);

			// Mix

			auto mixed_frame = mixer_(std::move(stage_frames), format_desc, channel_layout);

			// Consume

			output_ready_for_frame_ = output_(std::move(mixed_frame), format_desc, channel_layout);
			output_ready_for_frame_.get();

			auto frame_time = frame_timer.elapsed()*format_desc.fps*0.5;
			graph_->set_value("tick-time", frame_time);

			*monitor_subject_ << monitor::message("/profiler/time") % frame_timer.elapsed() % (1.0 / video_format_desc().fps)
				<< monitor::message("/format") % format_desc.name;
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}

		if (executor_.is_running())
			executor_.begin_invoke([=] {tick(); });
	}

	std::wstring print() const
	{
		return L"video_channel[" + boost::lexical_cast<std::wstring>(index_) + L"|" +  video_format_desc().name + L"]";
	}

	int index() const
	{
		return index_;
	}

	boost::property_tree::wptree info() const
	{
		boost::property_tree::wptree info;

		auto stage_info  = stage_.info();
		auto mixer_info  = mixer_.info();
		auto output_info = output_.info();

		info.add(L"video-mode", video_format_desc().name);
		info.add(L"audio-channel-layout", audio_channel_layout().print());
		info.add_child(L"stage", stage_info.get());
		info.add_child(L"mixer", mixer_info.get());
		info.add_child(L"output", output_info.get());

		return info;
	}

	boost::property_tree::wptree delay_info() const
	{
		boost::property_tree::wptree info;

		auto stage_info = stage_.delay_info();
		auto mixer_info = mixer_.delay_info();
		auto output_info = output_.delay_info();

		// TODO: because of std::async deferred timed waiting does not work so for now we have to block
		info.add_child(L"layers", stage_info.get());
		info.add_child(L"mix-time", mixer_info.get());
		info.add_child(L"output", output_info.get());

		return info;
	}

	std::shared_ptr<void> add_tick_listener(std::function<void()> listener)
	{
		return lock(tick_listeners_mutex_, [&]
		{
			auto tick_listener_id = last_tick_listener_id++;
			tick_listeners_.insert(std::make_pair(tick_listener_id, listener));

			return std::shared_ptr<void>(nullptr, [=](void*)
			{
				lock(tick_listeners_mutex_, [&]
				{
					tick_listeners_.erase(tick_listener_id);
				});
			});
		});
	}

	void set_logokiller(int index, std::wstring str)
	{
		if (str == format_desc_.wstr_logo_killer)
		{
			return;
		}
		else
		{
			format_desc_.wstr_logo_killer = str;
		}
		stage_.set_logokiller(index, str);
	}
};

void video_channel::add_afd_item(spl::shared_ptr<afd_item> item)
{
	impl_->afd_items.push_back(item);
}

void video_channel::find_afd_msg_by_afd_code(int afd_code, std::wstring& des)
{
	if (!(afd_code > 0 && afd_code < 16))
	{
		des = L"stretch";

		return;
	}
	BOOST_FOREACH(auto& item, impl_->afd_items)
	{
		if (item->afd_code == afd_code)
		{
			des = item->transform;
			return;
		}
	}

	des = impl_->format_desc_.table_afd_default;
}

video_channel::video_channel(
		int index,
		const core::video_format_desc& format_desc,
		const core::audio_channel_layout& channel_layout,
		std::unique_ptr<image_mixer> image_mixer) : impl_(new impl(index, format_desc, channel_layout, std::move(image_mixer))){}
video_channel::~video_channel(){}
const stage& video_channel::stage() const { return impl_->stage_;}
stage& video_channel::stage() { return impl_->stage_;}
const mixer& video_channel::mixer() const{ return impl_->mixer_;}
mixer& video_channel::mixer() { return impl_->mixer_;}
const output& video_channel::output() const { return impl_->output_;}
output& video_channel::output() { return impl_->output_;}
spl::shared_ptr<frame_factory> video_channel::frame_factory() { return impl_->image_mixer_;}
core::video_format_desc video_channel::video_format_desc() const{return impl_->video_format_desc();}
void core::video_channel::video_format_desc(const core::video_format_desc& format_desc){impl_->video_format_desc(format_desc);}
core::audio_channel_layout video_channel::audio_channel_layout() const { return impl_->audio_channel_layout(); }
void core::video_channel::audio_channel_layout(const core::audio_channel_layout& channel_layout) { impl_->audio_channel_layout(channel_layout); }
boost::property_tree::wptree video_channel::info() const{return impl_->info();}
boost::property_tree::wptree video_channel::delay_info() const { return impl_->delay_info(); }
int video_channel::index() const { return impl_->index(); }
monitor::subject& video_channel::monitor_output(){ return *impl_->monitor_subject_; }
std::shared_ptr<void> video_channel::add_tick_listener(std::function<void()> listener) { return impl_->add_tick_listener(std::move(listener)); }
void video_channel::set_logokiller(int index, std::wstring s)
{
	return impl_->set_logokiller(index, s);
}

}}
