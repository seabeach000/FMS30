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

#include "ndi_producer.h"

#include "../../ffmpeg/producer/filter/filter.h"
#include "../../ffmpeg/producer/util/util.h"
#include "../../ffmpeg/producer/muxer/frame_muxer.h"
#include "../../ffmpeg/producer/muxer/display_mode.h"
#include <common/executor.h>
#include <common/diagnostics/graph.h>
#include <common/except.h>
#include <common/log.h>
#include <common/param.h>
#include <common/timer.h>
#include <common/memcpy.h>

#include <core/frame/audio_channel_layout.h>
#include <core/frame/frame.h>
#include <core/frame/draw_frame.h>
#include <core/frame/frame_transform.h>
#include <core/frame/frame_factory.h>
#include <core/producer/frame_producer.h>
#include <core/producer/framerate/framerate_producer.h>
#include <core/monitor/monitor.h>
#include <core/diagnostics/call_context.h>
#include <core/mixer/audio/audio_mixer.h>
#include <core/help/help_repository.h>
#include <core/help/help_sink.h>


#include <tbb/concurrent_queue.h>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/range/adaptor/transformed.hpp>

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
	#define __STDC_CONSTANT_MACROS
	#define __STDC_LIMIT_MACROS
	#include <libavcodec/avcodec.h>
	#include <libswresample/swresample.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

#include <functional>
#include <Processing.NDI.Lib.h>
#define AUDIO32_t 0x7fffffff	
namespace caspar { namespace ndi {
	struct paramlist
	{
		std::wstring ndi_source;
		std::wstring machine;
		bool ndi_showlocal;
		std::wstring ndi_groups;
		std::wstring p_extra_ips;
		int  color_format;
		core::audio_channel_layout get_adjusted_channel_layout(core::audio_channel_layout layout)
		{
			if (layout.num_channels <= 2)
				layout.num_channels = 2;
			else if (layout.num_channels <= 8)
				layout.num_channels = 8;
			else
				layout.num_channels = 16;

			return layout;
		}

		template <typename T>
		std::wstring to_string(const T& cadence)
		{
			return boost::join(cadence | boost::adaptors::transformed([](size_t i) { return boost::lexical_cast<std::wstring>(i); }), L", ");
		}

		ffmpeg::audio_input_pad create_input_pad(const core::video_format_desc& in_format, int num_channels)
		{
			return ffmpeg::audio_input_pad(
				boost::rational<int>(1, in_format.audio_sample_rate),
				in_format.audio_sample_rate,
				AVSampleFormat::AV_SAMPLE_FMT_S32,
				av_get_default_channel_layout(num_channels));
		}
	};
	

class ndi_producer : boost::noncopyable
{
	std::wstring 									ndi_source_;
	NDIlib_recv_instance_t							pNDI_recv;
	core::monitor::subject							monitor_subject_;
	spl::shared_ptr<diagnostics::graph>				graph_;
	caspar::timer									tick_timer_;

	const std::wstring								filter_;

	core::video_format_desc							in_format_desc_;
	core::video_format_desc							out_format_desc_;
	std::vector<int>								audio_cadence_ = in_format_desc_.audio_cadence;
	
	spl::shared_ptr<core::frame_factory>			frame_factory_;
	core::audio_channel_layout						channel_layout_;
	ffmpeg::frame_muxer								muxer_{
		in_format_desc_.framerate,
		{ config_.create_input_pad(in_format_desc_, channel_layout_.num_channels) },
		frame_factory_,
		out_format_desc_,
		channel_layout_,
		filter_,
		ffmpeg::filter::is_deinterlacing(filter_)
	};
	std::shared_ptr<SwrContext>				swr_;
	core::constraints								constraints_{ in_format_desc_.width, in_format_desc_.height };

	tbb::concurrent_bounded_queue<core::draw_frame>	frame_buffer_;
	core::draw_frame								last_frame_ = core::draw_frame::empty();

	std::exception_ptr								exception_;

	tbb::atomic<bool>									is_running_;
	boost::thread										thread_;
	int 												buffer_[1920 * 20];
	paramlist											config_;
public:
	ndi_producer(
		const core::video_format_desc& in_format_desc,
		paramlist params,
		const spl::shared_ptr<core::frame_factory>& frame_factory,
		const core::video_format_desc& out_format_desc,
		const core::audio_channel_layout& channel_layout,
		const std::wstring& filter)
		:ndi_source_(params.ndi_source)
		,config_(params)
		,filter_(filter)
		, in_format_desc_(in_format_desc)
		, out_format_desc_(out_format_desc)
		, frame_factory_(frame_factory)
		, channel_layout_(params.get_adjusted_channel_layout(channel_layout))

	{		
		frame_buffer_.set_capacity(4);

		graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
		graph_->set_color("late-frame", diagnostics::color(0.6f, 0.3f, 0.3f));
		graph_->set_color("frame-time", diagnostics::color(1.0f, 0.0f, 0.0f));
		graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
		graph_->set_color("output-buffer", diagnostics::color(0.0f, 1.0f, 0.0f));
		graph_->set_text(print());
		diagnostics::register_graph(graph_);

		const NDIlib_find_create_t NDI_find_create_desc = { params.ndi_showlocal,u8(params.ndi_groups).c_str(),u8(params.p_extra_ips).c_str() };
		NDIlib_find_instance_t pNDI_find = NDIlib_find_create(&NDI_find_create_desc);
		

		int no_sources = 0;
		
		NDIlib_source_t load_source_;
		
			
		if (!pNDI_find)
		{
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(L"NDI find error")
				<< boost::errinfo_api_function("init_ndi_producer"));
			return;
		}
		int breakint = 0;
		const NDIlib_source_t* p_sources = NULL;
		while (true)
		{
			p_sources = NULL;
			p_sources = NDIlib_find_get_sources(pNDI_find, &no_sources, 10000);//这个函数必须用，否则，收不到任何东西
			if (no_sources != 0)
			{
				if (no_sources == breakint)
				{
					break;
				}
				else
					breakint = no_sources;
			}
		}

		if (!p_sources)
		{
			NDIlib_find_destroy(pNDI_find);
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(L"NDI find error")
				<< boost::errinfo_api_function("init_ndi_producer"));
			return;
		}
			
		bool findout = false;
		std::string machine = u8(params.machine);
		for (int i = 0; i < no_sources;i++)
		{
			std::string ndi_name = "";
			ndi_name = p_sources[i].p_ndi_name;
			ndi_name =boost::to_lower_copy(ndi_name);
			if (machine.empty())
			{
				int pos = ndi_name.find("(");
				if (pos != std::string::npos)
				{
					ndi_name = ndi_name.substr(pos + 1, ndi_name.size() - pos - 2);
				}
				if (ndi_name == u8(boost::to_lower_copy(ndi_source_)))
				{
					load_source_ = p_sources[i];
					findout = true;
					break;
				}
			}
			else
			{
				std::string s = machine + " (" + u8(boost::to_lower_copy(ndi_source_))+")";
				
				if (ndi_name ==s)
				{
					load_source_ = p_sources[i];
					findout = true;
					break;
				}
			}
				
		}
		if (!findout)
		{
			NDIlib_find_destroy(pNDI_find);
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(L"NDI find error")
				<< boost::errinfo_api_function("init_ndi_producer"));
			return;
		}
			

	
		int color_format = NDIlib_recv_color_format_e_BGRX_BGRA;
		if (params.color_format == NDIlib_recv_color_format_e_UYVY_BGRA)
		{
			color_format = NDIlib_recv_color_format_e_UYVY_BGRA;
		}
		
		NDIlib_recv_create_t NDI_recv_create_desc = { load_source_, (NDIlib_recv_color_format_e)color_format, /* Highest quality */NDIlib_recv_bandwidth_highest, /* Allow fielded video */true };
		pNDI_recv = NDIlib_recv_create2(&NDI_recv_create_desc);
		if (!pNDI_recv)
		{
			NDIlib_find_destroy(pNDI_find);
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(L"NDI NDIlib_recv_create2 error")
				<< boost::errinfo_api_function("init_ndi_producer"));
			return;
		}
		NDIlib_find_destroy(pNDI_find);
		// Destroy the NDI finder. We needed to have access to the pointers to p_sources[0]
		

		// We are now going to mark this source as being on program output for tally purposes (but not on preview)
		const NDIlib_tally_t tally_state = { true, true };
		NDIlib_recv_set_tally(pNDI_recv, &tally_state);
		
		is_running_ = true;
		thread_ = boost::thread([this] {run(); });
	}

	~ndi_producer()
	{
		release();
		
	}
	void release()
	{
		is_running_ = false;
		thread_.join();
	
		CASPAR_LOG(info) << L" NID virtual source successfully released.";
	}
	//收到Meta之后开始收视音频 
	void run()
	{

		bool meta = false;
		//统计包数量
		int count = 0;
		while (is_running_)
		{	// The descriptors
			NDIlib_video_frame_t ndi_video_frame;
			NDIlib_audio_frame_t ndi_audio_frame;
			NDIlib_metadata_frame_t metadata_frame;
			
			switch (NDIlib_recv_capture(pNDI_recv, &ndi_video_frame, &ndi_audio_frame, &metadata_frame, 10))
			{
				// No data
			case NDIlib_frame_type_none:
				//printf("No data received.\n");
				break;

				// Video data
			case NDIlib_frame_type_video:
			{

				core::field_mode dd;
				switch (ndi_video_frame.frame_format_type)
				{
				case NDIlib_frame_format_type_progressive:
					dd = core::field_mode::progressive;
					break;
				case NDIlib_frame_format_type_interleaved:
					dd = core::field_mode::empty;
					break;
				case NDIlib_frame_format_type_field_0:
					dd = core::field_mode::lower;
					break;
				case NDIlib_frame_format_type_field_1:
					dd = core::field_mode::upper;
					break;
				default:
					break;
				}
				int sdd = AV_PIX_FMT_BGRA;
				switch (ndi_video_frame.FourCC)
				{
				case NDIlib_FourCC_type_UYVY:
					sdd = AV_PIX_FMT_UYVY422;
					break;
				case NDIlib_FourCC_type_BGRA:
					sdd = AV_PIX_FMT_BGRA;
					break;
				case NDIlib_FourCC_type_BGRX:
					sdd = AV_PIX_FMT_BGRA;
					break;
				case NDIlib_FourCC_type_UYVA:
					sdd = AV_PIX_FMT_UYVY422;
					break;
				default:
					break;
				}
				
				auto video_frame = ffmpeg::create_frame();
				video_frame->data[0] = reinterpret_cast<uint8_t*>(ndi_video_frame.p_data);
				video_frame->linesize[0] = ndi_video_frame.xres*4;
				
				video_frame->format = sdd;//这个值有需要矫正

				video_frame->width = ndi_video_frame.xres;
				video_frame->height = ndi_video_frame.yres;
				video_frame->interlaced_frame = in_format_desc_.field_mode != dd;
				video_frame->top_field_first = in_format_desc_.field_mode == dd ? 1 : 0;
				video_frame->key_frame = 1;

				
				if (meta)
				{
					muxer_.push(static_cast<std::shared_ptr<AVFrame>>(video_frame));
				}

				NDIlib_recv_free_video(pNDI_recv, &ndi_video_frame);
			}
				break;
			case NDIlib_frame_type_audio:
			{
				if (meta)
				{
					std::shared_ptr<core::mutable_audio_buffer>	audio_buffer;
					{
						int32_t * vestd = (int32_t*)malloc(ndi_audio_frame.no_samples *ndi_audio_frame.no_channels * sizeof(int32_t));
						float * p_ch = ndi_audio_frame.p_data;
						for (int ch = 0; ch<ndi_audio_frame.no_channels;ch++)
						{
							for (int no_sample = ch;no_sample<ndi_audio_frame.no_channels*ndi_audio_frame.no_samples;)
							{
								int32_t sf= (int32_t)((*p_ch) * (float)AUDIO32_t);
								vestd[no_sample] = sf;
								no_sample += ndi_audio_frame.no_channels;
								//no_sample++;
								p_ch++;
							}
							//break;
						}
						
					
						
						memset(buffer_, 0, 1920 * 20);
					
						const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&vestd);
						
						uint8_t *out[] = { reinterpret_cast<uint8_t*>(buffer_)};

						const auto channel_samples = swr_convert(
							swr_.get(),
							out,
							1920 * 20,
							in,
							ndi_audio_frame.no_samples);

					
						auto audio_data = reinterpret_cast<int32_t*>((int32_t*)buffer_);

						audio_buffer = std::make_shared<core::mutable_audio_buffer>(
							audio_data,
							audio_data + channel_samples * channel_layout_.num_channels);
						free(vestd);

					}
					muxer_.push({ audio_buffer });
				}
				NDIlib_recv_free_audio(pNDI_recv, &ndi_audio_frame);
			}
				break;

				// Meta data
			case NDIlib_frame_type_metadata:
			{
				//printf("Meta data received.\n");
				int outchannel = av_get_default_channel_layout(channel_layout_.num_channels);
				int intchannel = av_get_default_channel_layout(ndi_audio_frame.no_channels);
				NDIlib_recv_free_metadata(pNDI_recv, &metadata_frame);
				swr_ = {
					swr_alloc_set_opts(
						nullptr,
						outchannel,
						AV_SAMPLE_FMT_S32,// 需要配置的
						out_format_desc_.audio_sample_rate,//需要
						intchannel,
						AV_SAMPLE_FMT_S32,
						ndi_audio_frame.sample_rate,
						0,
						nullptr),
						[](SwrContext* p)
					{
						swr_free(&p);
					}
				};
				swr_init(swr_.get());
				meta = true;
			}
				break;
			default:
				break;
			}
			//没有收到有效的就返回
			if (!meta)
			{
				continue;
			}
			for (auto frame = muxer_.poll(); frame != core::draw_frame::empty(); frame = muxer_.poll())
			{
				if (!frame_buffer_.try_push(frame))
				{
					auto dummy = core::draw_frame::empty();
					frame_buffer_.try_pop(dummy);

					frame_buffer_.try_push(frame);

					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
				}
			}

			/*graph_->set_value("frame-time", frame_timer.elapsed()*out_format_desc_.fps*0.5);
			monitor_subject_ << core::monitor::message("/profiler/time") % frame_timer.elapsed() % out_format_desc_.fps;

			graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));
			monitor_subject_ << core::monitor::message("/buffer") % frame_buffer_.size() % frame_buffer_.capacity();

			graph_->set_value("tick-time", tick_timer_.elapsed()*out_format_desc_.fps*0.5);
			tick_timer_.restart();*/

			caspar::timer frame_timer;
		}
		NDIlib_recv_destroy(pNDI_recv);
		
	}
	core::constraints& pixel_constraints()
	{
		return constraints_;
	}

	core::draw_frame get_frame()
	{

		core::draw_frame frame = last_frame_;

		if (!frame_buffer_.try_pop(frame))
			graph_->set_tag(diagnostics::tag_severity::WARNING, "late-frame");
		else
			last_frame_ = frame;

		graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size()) / static_cast<float>(frame_buffer_.capacity()));

		return frame;
	}

	std::wstring print() const
	{
		return L" [" + boost::lexical_cast<std::wstring>(ndi_source_) + L"|" + in_format_desc_.name + L"]";
	}

	boost::rational<int> get_out_framerate() const
	{
		return muxer_.out_framerate();
	}
	core::monitor::subject& monitor_output()
	{
		return monitor_subject_;
	}
};

class ndi_producer_proxy : public core::frame_producer_base
{
	std::unique_ptr<ndi_producer>	producer_;
	const uint32_t						length_;
	executor							executor_;
	std::wstring						sourcename_;

public:
	explicit ndi_producer_proxy( 
		const core::video_format_desc& in_format_desc,
		const spl::shared_ptr<core::frame_factory>& frame_factory,
		const core::video_format_desc& out_format_desc,
		const core::audio_channel_layout& channel_layout,
		paramlist params,
		const std::wstring& filter_str,
		uint32_t length)
		: sourcename_(params.ndi_source)
		,executor_(L"ndi_producer[" + params.ndi_source + L"]")
		, length_(length)
	{
		auto ctx = core::diagnostics::call_context::for_thread();
		executor_.invoke([=]
		{
			core::diagnostics::call_context::for_thread() = ctx;
			producer_.reset(new ndi_producer(in_format_desc, params, frame_factory, out_format_desc, channel_layout, filter_str));
		});
	}

	~ndi_producer_proxy()
	{
		executor_.invoke([=]
		{
			producer_.reset();
		});
	}

	core::monitor::subject& monitor_output()
	{
		return producer_->monitor_output();
	}

	// frame_producer

	core::draw_frame receive_impl() override
	{
		return producer_->get_frame();
	}

	int producer_type()
	{
		return FFMPEG_Resource::FFMPEG_FILE;
	}

	core::constraints& pixel_constraints() override
	{
		return producer_->pixel_constraints();
	}

	std::wstring print() const override
	{
		return producer_->print();
	}

	std::wstring name() const override
	{
		return L"decklink";
	}

	boost::property_tree::wptree info() const override
	{
		boost::property_tree::wptree info;
		info.add(L"type", L"decklink");
		return info;
	}

	boost::rational<int> get_out_framerate() const
	{
		return producer_->get_out_framerate();
	}
};

void describe_producer(core::help_sink& sink, const core::help_repository& repo)
{
	sink.short_description(L"Allows video sources to be input from BlackMagic Design cards.");
	sink.syntax(L"ndi [source:string]");
	sink.para()->text(L"Allows video sources to be input from BlackMagic Design cards. Parameters:");
	sink.definitions()
		->item(L"source", L"The ndi source to stream the input from.");
	sink.para()->text(L"Examples:");
	sink.example(L">> PLAY 1-10 NDI source ndivideo grops fcl ips 192.168.1.14,172.16.3.0.0.0 showlocal 1 colorformat RGB(YUV)", L"Play using decklink device 2 expecting the video signal to have the same video format as the channel.");
}

spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params)
{
	if (params.empty() || !boost::iequals(boost::to_upper_copy(params.at(0)), L"NDI"))
		return core::frame_producer::empty();

	paramlist vidparams;

	if (params.empty() || !boost::iequals(params.at(0), "ndi"))
		return core::frame_producer::empty();

	auto ndi_source = get_param(L"source", params);
	if (ndi_source.empty())
	{
		CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"NDI SOURCE NAME IS EMPTY"));
	}
	vidparams.ndi_source = ndi_source;
	vidparams.machine = get_param(L"machine",params);
	auto showlocal = get_param(L"showlocal", params);
	if (showlocal.empty()|| showlocal == L"1")
	{
		vidparams.ndi_showlocal = true;
	}
	else if (showlocal == L"0")
	{
		vidparams.ndi_showlocal = false;
	}
	else
		vidparams.ndi_showlocal = true;

	vidparams.ndi_groups = get_param(L"groups", params);
	vidparams.p_extra_ips = get_param(L"ips", params);

	auto colorformat = get_param(L"colorformat", params);
	if (boost::iequals(boost::to_upper_copy(colorformat), L"YUV"))
	{
		vidparams.color_format = NDIlib_recv_color_format_e_UYVY_BGRA;
	}
	else
		vidparams.color_format = NDIlib_recv_color_format_e_BGRX_BGRA;


	auto filter_str = get_param(L"FILTER", params);
	auto length = get_param(L"LENGTH", params, std::numeric_limits<uint32_t>::max());
	auto in_format_desc = core::video_format_desc(get_param(L"FORMAT", params, L"INVALID"));

	if (in_format_desc.format == core::video_format::invalid)
		in_format_desc = dependencies.format_desc;

	auto channel_layout_spec = get_param(L"CHANNEL_LAYOUT", params);
	auto channel_layout = *core::audio_channel_layout_repository::get_default()->get_layout(L"stereo");

	if (!channel_layout_spec.empty())
	{
		auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout_spec);

		if (!found_layout)
			CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout not found."));

		channel_layout = *found_layout;
	}

	boost::ireplace_all(filter_str, L"DEINTERLACE_BOB", L"YADIF=1:-1");
	boost::ireplace_all(filter_str, L"DEINTERLACE_LQ", L"SEPARATEFIELDS");
	boost::ireplace_all(filter_str, L"DEINTERLACE", L"YADIF=0:-1");

	auto producer = spl::make_shared<ndi_producer_proxy>(
		in_format_desc,
		dependencies.frame_factory,
		dependencies.format_desc,
		channel_layout,
		vidparams,
		filter_str,
		length);

	auto get_source_framerate = [=] { return producer->get_out_framerate(); };
	auto target_framerate = dependencies.format_desc.framerate;

	return core::create_destroy_proxy(core::create_framerate_producer(
		producer,
		get_source_framerate,
		target_framerate,
		dependencies.format_desc.field_mode,
		dependencies.format_desc.audio_cadence));
}
}}
