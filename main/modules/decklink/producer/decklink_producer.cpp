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

#include "../StdAfx.h"

#include "decklink_producer.h"

#include "../util/util.h"

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
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

#include "../decklink_api.h"

#include <functional>

namespace caspar { namespace decklink {
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

class decklink_producer : boost::noncopyable, public IDeckLinkInputCallback
{
	const int										device_index_;
	core::monitor::subject							monitor_subject_;
	spl::shared_ptr<diagnostics::graph>				graph_;
	caspar::timer									tick_timer_;

	com_ptr<IDeckLink>								decklink_			= get_device(device_index_);
	com_iface_ptr<IDeckLinkInput>					input_				= iface_cast<IDeckLinkInput>(decklink_);
	com_iface_ptr<IDeckLinkAttributes>				attributes_			= iface_cast<IDeckLinkAttributes>(decklink_);

	const std::wstring								model_name_			= get_model_name(decklink_);
	const std::wstring								filter_;

	core::video_format_desc							in_format_desc_;
	core::video_format_desc							out_format_desc_;
	std::vector<int>								audio_cadence_		= in_format_desc_.audio_cadence;
	boost::circular_buffer<size_t>					sync_buffer_		{ audio_cadence_.size() };
	spl::shared_ptr<core::frame_factory>			frame_factory_;
	core::audio_channel_layout						channel_layout_;
	ffmpeg::frame_muxer								muxer_				{
																			in_format_desc_.framerate,
																			{ create_input_pad(in_format_desc_, channel_layout_.num_channels) },
																			frame_factory_,
																			out_format_desc_,
																			channel_layout_,
																			filter_,
																			ffmpeg::filter::is_deinterlacing(filter_)
																		};

	core::constraints								constraints_		{ in_format_desc_.width, in_format_desc_.height };

	tbb::concurrent_bounded_queue<core::draw_frame>	frame_buffer_;
	core::draw_frame								last_frame_			= core::draw_frame::empty();

	std::exception_ptr								exception_;
	bool											m_bInputChanged;
	//logo killer wxg20170105
	//------------------
	std::shared_ptr<SwsContext>				        sws_;
	typedef std::vector<uint8_t, tbb::cache_aligned_allocator<uint8_t>>	byte_vector;
	logo_killer_params                              logo_killer_params_;
	//------------------
public:
	decklink_producer(
			const core::video_format_desc& in_format_desc,
			int device_index,
			const spl::shared_ptr<core::frame_factory>& frame_factory,
			const core::video_format_desc& out_format_desc,
			const core::audio_channel_layout& channel_layout,
			const std::wstring& filter)
		: device_index_(device_index)
		, filter_(filter)
		, in_format_desc_(in_format_desc)
		, out_format_desc_(out_format_desc)
		, frame_factory_(frame_factory)
		, channel_layout_(get_adjusted_channel_layout(channel_layout))
		, m_bInputChanged(false)
	{
		frame_buffer_.set_capacity(4);

		graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
		graph_->set_color("late-frame", diagnostics::color(0.6f, 0.3f, 0.3f));
		graph_->set_color("frame-time", diagnostics::color(1.0f, 0.0f, 0.0f));
		graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
		graph_->set_color("output-buffer", diagnostics::color(0.0f, 1.0f, 0.0f));
		graph_->set_text(print());
		diagnostics::register_graph(graph_);

		start();
	}

	~decklink_producer()
	{
		if(input_ != nullptr)
		{
			input_->StopStreams();
			input_->DisableVideoInput();
		}
	}
	//logo killer
	//-----------------------------------
	int LSR0;
	int LSR1;
	int USR0;
	int USR1;
	int VSR0;
	int VSR1;
	int LSC0[768];
	int LSC1[768];
	int USC0[768];
	int USC1[768];
	int VSC0[768];
	int VSC1[768];
	void LogoKiller_YUV422(AVFrame* avFrame, int left, int top, int width, int height, bool smoothing, int smoothing_value)
	{
		long Pitch_Y = avFrame->linesize[0];
		long Pitch_U = avFrame->linesize[1];
		long Pitch_V = avFrame->linesize[2];

		left = std::max(left, 2);
		left = std::min(left, avFrame->width - 3);
		top = std::max(top, 2);
		top = std::min(top, avFrame->height - 3);
		if (left + width > avFrame->width - 2)
			width = avFrame->width - 2 - left;
		if (top + height > avFrame->height - 2)
			height = avFrame->height - 2 - top;

		// align Left and Width to 2 pixels to make calculations with chroma easier
		left = left & ~1;                           // align towards left
		width += width % 2;                         // align towards right

		uint8_t* lpLogoStart_Y = avFrame->data[0] + left + top * Pitch_Y;
		uint8_t* lpLogoStart_U = avFrame->data[1] + left / 2 + top * Pitch_U;
		uint8_t* lpLogoStart_V = avFrame->data[2] + left / 2 + top * Pitch_V;

		uint8_t *pFirstLine_Y = lpLogoStart_Y;
		uint8_t *pFirstLine_U = lpLogoStart_U;
		uint8_t *pFirstLine_V = lpLogoStart_V;
		uint8_t *pLastLine_Y = lpLogoStart_Y + height * Pitch_Y;
		uint8_t *pLastLine_U = lpLogoStart_U + height * Pitch_U;
		uint8_t *pLastLine_V = lpLogoStart_V + height * Pitch_V;

		for (int j = 1; j < height; j++)
		{
			uint8_t *pCurrentLine_Y = lpLogoStart_Y + j * Pitch_Y;
			uint8_t *pCurrentLine_U = lpLogoStart_U + j * Pitch_U;
			uint8_t *pCurrentLine_V = lpLogoStart_V + j * Pitch_V;

			for (int i = 1; i < width / 2; i++)
			{
				uint8_t h_lumi1 = static_cast<uint8_t>((pCurrentLine_Y[1] * (width - i * 2) + pCurrentLine_Y[width - 1] * (i * 2)) / (width));
				uint8_t h_lumi2 = static_cast<uint8_t>((pCurrentLine_Y[1] * (width - i * 2 - 1) + pCurrentLine_Y[width - 1] * (i * 2 + 1)) / (width));
				uint8_t h_chroma1 = static_cast<uint8_t>((pCurrentLine_U[0] * (width - i * 2) + pCurrentLine_U[width / 2] * (i * 2)) / (width));
				uint8_t h_chroma2 = static_cast<uint8_t>((pCurrentLine_V[0] * (width - i * 2) + pCurrentLine_V[width / 2] * (i * 2)) / (width));

				uint8_t v_lumi1 = static_cast<uint8_t>((pFirstLine_Y[i * 2] * (height - j) + pLastLine_Y[i * 2] * j) / (height));
				uint8_t v_lumi2 = static_cast<uint8_t>((pFirstLine_Y[i * 2 + 1] * (height - j) + pLastLine_Y[i * 2 + 1] * j) / (height));
				uint8_t v_chroma1 = static_cast<uint8_t>((pFirstLine_U[i] * (height - j) + pLastLine_U[i] * j) / (height));
				uint8_t v_chroma2 = static_cast<uint8_t>((pFirstLine_V[i] * (height - j) + pLastLine_V[i] * j) / (height));

				pCurrentLine_Y[i * 2] = (h_lumi1 + v_lumi1) / 2;
				pCurrentLine_Y[i * 2 + 1] = (h_lumi2 + v_lumi2) / 2;
				pCurrentLine_U[i] = (h_chroma1 + v_chroma1) / 2;
				pCurrentLine_V[i] = (h_chroma2 + v_chroma2) / 2;
			}
		}

		// Patch from Jochen Trener to add adjustable smoothing (Gaussian blur)
		// It is based n the paper ' An efficient algorithm for Gaussian
		// blur using finite state machines' by F. Waltz and J. Miller
		if (smoothing)
		{
			int i, j, n = 0;
			int Ltmp1, Ltmp2;
			int Utmp1, Utmp2;
			int Vtmp1, Vtmp2;
			int smoothing_runs = smoothing_value;

			lpLogoStart_Y -= (2 + Pitch_Y);
			lpLogoStart_U -= (1 + Pitch_U);
			lpLogoStart_V -= (1 + Pitch_V);

			for (n = 0; n < smoothing_runs; ++n)
			{
				memset(LSC0, 0, 768 * sizeof(int));
				memset(USC0, 0, 768 * sizeof(int));
				memset(USC1, 0, 768 * sizeof(int));
				memset(VSC0, 0, 768 * sizeof(int));
				memset(VSC1, 0, 768 * sizeof(int));

				for (j = 0; j < height + 2; j++)
				{
					uint8_t *pAboveLine_Y = lpLogoStart_Y + (j - 1) * Pitch_Y;
					uint8_t *pCurrentLine_Y = lpLogoStart_Y + j * Pitch_Y;
					uint8_t *pAboveLine_U = lpLogoStart_U + (j - 1) * Pitch_U;
					uint8_t *pCurrentLine_U = lpLogoStart_U + j * Pitch_U;
					uint8_t *pAboveLine_V = lpLogoStart_V + (j - 1) * Pitch_V;
					uint8_t *pCurrentLine_V = lpLogoStart_V + j * Pitch_V;

					LSR0 = 0;
					LSR1 = 0;
					USR0 = 0;
					USR1 = 0;
					VSR0 = 0;
					VSR1 = 0;
					for (i = 0; i < width + 2; ++i)
					{
						Ltmp1 = pCurrentLine_Y[i];
						Ltmp2 = LSR0 + Ltmp1;
						LSR0 = Ltmp1;
						Ltmp1 = LSR1 + Ltmp2;
						LSR1 = Ltmp2;
						Ltmp2 = LSC0[i] + Ltmp1;
						LSC0[i] = Ltmp1;
						if (i > 1 && j > 1)
						{
							pAboveLine_Y[i - 1] = (uint8_t)((8 + LSC1[i] + Ltmp2) / 16);
						}
						LSC1[i] = Ltmp2;
					}
					for (i = 0; i < width / 2 + 1; i++)
					{
						Utmp1 = pCurrentLine_U[i];
						Vtmp1 = pCurrentLine_V[i];
						Utmp2 = USR0 + Utmp1;
						Vtmp2 = VSR0 + Vtmp1;
						USR0 = Utmp1;
						VSR0 = Vtmp1;
						Utmp1 = USR1 + Utmp2;
						Vtmp1 = VSR1 + Vtmp2;
						USR1 = Utmp2;
						VSR1 = Vtmp2;
						Utmp2 = USC0[i] + Utmp1;
						Vtmp2 = VSC0[i] + Vtmp1;
						USC0[i] = Utmp1;
						VSC0[i] = Vtmp1;
						if (i > 1 && j > 1)
						{
							pAboveLine_U[i - 1] = (uint8_t)((8 + USC1[i] + Utmp2) / 16);
							pAboveLine_V[i - 1] = (uint8_t)((8 + VSC1[i] + Vtmp2) / 16);
						}
						USC1[i] = Utmp2;
						VSC1[i] = Vtmp2;
					}
				}
			}
		}
	}
	//-----------------------------------
	void start()
	{
		//logo_killer wxg20170105
		//------------------
		sws_.reset(sws_getContext(in_format_desc_.width, in_format_desc_.height, AV_PIX_FMT_UYVY422, in_format_desc_.width, in_format_desc_.height, AV_PIX_FMT_YUV422P, SWS_BICUBIC, nullptr, nullptr, nullptr), sws_freeContext);
		if (sws_ == nullptr)
			BOOST_THROW_EXCEPTION(caspar_exception() << msg_info("Cannot initialize the conversion context"));
		//------------------

		bool will_attempt_dma;
		auto display_mode = get_display_mode(input_, in_format_desc_.format, bmdFormat8BitYUV, bmdVideoInputFlagDefault, will_attempt_dma);

		// NOTE: bmdFormat8BitARGB is currently not supported by any decklink card. (2011-05-08)
		BOOL doesDetectFormat = FALSE;
		IDeckLinkAttributes *decklinkAttributes = nullptr;
		if (input_->QueryInterface(IID_IDeckLinkAttributes, (void**)&decklinkAttributes) == S_OK)
		{
			if (decklinkAttributes->GetFlag(BMDDeckLinkSupportsInputFormatDetection, &doesDetectFormat) != S_OK)
				doesDetectFormat = FALSE;
		}
		BMDVideoInputFlags flags = doesDetectFormat ? bmdVideoInputEnableFormatDetection : bmdVideoInputFlagDefault;

		if (FAILED(input_->EnableVideoInput(display_mode, bmdFormat8BitYUV, flags)))
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(print() + L" Could not enable video input.")
				<< boost::errinfo_api_function("EnableVideoInput"));

		if (FAILED(input_->EnableAudioInput(bmdAudioSampleRate48kHz, bmdAudioSampleType32bitInteger, static_cast<int>(channel_layout_.num_channels))))
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(print() + L" Could not enable audio input.")
				<< boost::errinfo_api_function("EnableAudioInput"));

		if (FAILED(input_->SetCallback(this)) != S_OK)
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(print() + L" Failed to set input callback.")
				<< boost::errinfo_api_function("SetCallback"));

		if (FAILED(input_->StartStreams()))
			CASPAR_THROW_EXCEPTION(caspar_exception()
				<< msg_info(print() + L" Failed to start input stream.")
				<< boost::errinfo_api_function("StartStreams"));

		CASPAR_LOG(info) << print() << L" Initialized";

	}
	bool stop()
	{
		CASPAR_LOG(debug) << L"DECKLINK  ##########  decklink_producer stop";
		input_->StopStreams();
		input_->DisableVideoInput();
		input_->DisableAudioInput();
		frame_buffer_.clear();
		sws_ = nullptr;
		return true;
	}
	core::constraints& pixel_constraints()
	{
		return constraints_;
	}

	virtual HRESULT STDMETHODCALLTYPE	QueryInterface (REFIID, LPVOID*)	{return E_NOINTERFACE;}
	virtual ULONG STDMETHODCALLTYPE		AddRef ()							{return 1;}
	virtual ULONG STDMETHODCALLTYPE		Release ()							{return 1;}

	virtual HRESULT STDMETHODCALLTYPE VideoInputFormatChanged(BMDVideoInputFormatChangedEvents notificationEvents, IDeckLinkDisplayMode* newDisplayMode, BMDDetectedVideoInputFormatFlags /*detectedSignalFlags*/)
	{
		if (notificationEvents & bmdVideoInputDisplayModeChanged)
		{
			m_bInputChanged = true;
			in_format_desc_.width = newDisplayMode->GetWidth();
			in_format_desc_.height = newDisplayMode->GetHeight();
			in_format_desc_.format = get_caspar_video_format(newDisplayMode->GetDisplayMode());
			CASPAR_LOG(debug) << L"Could enable video input. EnableVideoInput";

			stop();
			start();
			m_bInputChanged = false;
		}
		else
		{
			CASPAR_LOG(debug) << L"Could not enable video input. EnableVideoInput.VideoInputFormatChanged and  EnableVideoInput";

		}

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE VideoInputFrameArrived(IDeckLinkVideoInputFrame* video, IDeckLinkAudioInputPacket* audio)
	{
		ensure_gpf_handler_installed_for_thread("decklink-VideoInputFrameArrived");
		if(!video)
			return S_OK;

		try
		{
			graph_->set_value("tick-time", tick_timer_.elapsed()*out_format_desc_.fps*0.5);
			tick_timer_.restart();

			caspar::timer frame_timer;

			// Video

			void* video_bytes = nullptr;
			if(FAILED(video->GetBytes(&video_bytes)) || !video_bytes)
				return S_OK;

			auto video_frame = ffmpeg::create_frame();

			video_frame->data[0]			= reinterpret_cast<uint8_t*>(video_bytes);
			video_frame->linesize[0]		= video->GetRowBytes();
			//video_frame->format = PIX_FMT_UYVY422;
//3.0
			video_frame->format				= AV_PIX_FMT_UYVY422;

			video_frame->width				= video->GetWidth();
			video_frame->height				= video->GetHeight();
			video_frame->interlaced_frame	= in_format_desc_.field_mode != core::field_mode::progressive;
			video_frame->top_field_first	= in_format_desc_.field_mode == core::field_mode::upper ? 1 : 0;
			video_frame->key_frame			= 1;

			monitor_subject_
					<< core::monitor::message("/file/name")					% model_name_
					<< core::monitor::message("/file/path")					% device_index_
					<< core::monitor::message("/file/video/width")			% video->GetWidth()
					<< core::monitor::message("/file/video/height")			% video->GetHeight()
					<< core::monitor::message("/file/video/field")			% u8(!video_frame->interlaced_frame ? "progressive" : (video_frame->top_field_first ? "upper" : "lower"))
					<< core::monitor::message("/file/audio/sample-rate")	% 48000
					<< core::monitor::message("/file/audio/channels")		% 2
					<< core::monitor::message("/file/audio/format")			% u8(av_get_sample_fmt_name(AV_SAMPLE_FMT_S32))
					<< core::monitor::message("/file/fps")					% in_format_desc_.fps;

			// Audio

			std::shared_ptr<core::mutable_audio_buffer>	audio_buffer;
			void*										audio_bytes		= nullptr;

			// It is assumed that audio is always equal or ahead of video.
			if (audio && SUCCEEDED(audio->GetBytes(&audio_bytes)) && audio_bytes)
			{
				auto sample_frame_count = audio->GetSampleFrameCount();
				auto audio_data = reinterpret_cast<int32_t*>(audio_bytes);

				audio_buffer = std::make_shared<core::mutable_audio_buffer>(
					audio_data,
					audio_data + sample_frame_count * channel_layout_.num_channels);
			}
			else
				audio_buffer = std::make_shared<core::mutable_audio_buffer>(audio_cadence_.front() * channel_layout_.num_channels, 0);

			// Note: Uses 1 step rotated cadence for 1001 modes (1602, 1602, 1601, 1602, 1601)
			// This cadence fills the audio mixer most optimally.

			sync_buffer_.push_back(audio_buffer->size() / channel_layout_.num_channels);
			if(!boost::range::equal(sync_buffer_, audio_cadence_))
			{
				CASPAR_LOG(trace) << print() << L" Syncing audio. Expected cadence: " << to_string(audio_cadence_) << L" Got cadence: " << to_string(sync_buffer_);
				return S_OK;
			}
			boost::range::rotate(audio_cadence_, std::begin(audio_cadence_)+1);

			//logokiller wxg201170105
			int nPlanes = av_pix_fmt_count_planes(AV_PIX_FMT_UYVY422);
			if (nPlanes != 3)
			{
				auto decoded_frame_sws = av_frame_clone(video_frame.get());
				byte_vector	picture_buf_;
				picture_buf_.resize(avpicture_get_size(AV_PIX_FMT_YUV422P, video_frame->width, video_frame->height));
				avpicture_fill(reinterpret_cast<AVPicture*>(video_frame.get()), picture_buf_.data(), AV_PIX_FMT_YUV422P, in_format_desc_.width, in_format_desc_.height);
				sws_scale(sws_.get(), decoded_frame_sws->data, decoded_frame_sws->linesize, 0, in_format_desc_.height, video_frame->data, video_frame->linesize);
				av_frame_free(&decoded_frame_sws);
				video_frame->format = AV_PIX_FMT_YUV422P;
			}
			if (logo_killer_params_.logo_killer_enable)
			{
				LogoKiller_YUV422(video_frame.get(), logo_killer_params_.logo_killer_left, logo_killer_params_.logo_killer_top
					, logo_killer_params_.logo_killer_width, logo_killer_params_.logo_killer_height
					, logo_killer_params_.logo_killer_is_smooth, logo_killer_params_.logo_killer_smooth_value);
			}
			//------------------------
			// PUSH

			muxer_.push({ audio_buffer });
			muxer_.push(static_cast<std::shared_ptr<AVFrame>>(video_frame));

			// POLL

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

			graph_->set_value("frame-time", frame_timer.elapsed()*out_format_desc_.fps*0.5);
			monitor_subject_ << core::monitor::message("/profiler/time") % frame_timer.elapsed() % out_format_desc_.fps;

			graph_->set_value("output-buffer", static_cast<float>(frame_buffer_.size())/static_cast<float>(frame_buffer_.capacity()));
			monitor_subject_ << core::monitor::message("/buffer") % frame_buffer_.size() % frame_buffer_.capacity();
		}
		catch(...)
		{
			exception_ = std::current_exception();
			return E_FAIL;
		}

		return S_OK;
	}

	core::draw_frame get_frame()
	{
		if (m_bInputChanged)
		{
			return core::draw_frame::empty();
		}

		if(exception_ != nullptr)
			std::rethrow_exception(exception_);

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
		return model_name_ + L" [" + boost::lexical_cast<std::wstring>(device_index_) + L"|" + in_format_desc_.name + L"]";
	}

	boost::rational<int> get_out_framerate() const
	{
		return muxer_.out_framerate();
	}

	core::monitor::subject& monitor_output()
	{
		return monitor_subject_;
	}

	//logo killer wxg201170105
	//-----------------------
	void set_logo_killer_params(logo_killer_params& params)
	{
		logo_killer_params_.logo_killer_enable = params.logo_killer_enable;
		logo_killer_params_.logo_killer_left = params.logo_killer_left;
		logo_killer_params_.logo_killer_top = params.logo_killer_top;
		logo_killer_params_.logo_killer_width = params.logo_killer_width;
		logo_killer_params_.logo_killer_height = params.logo_killer_height;
		logo_killer_params_.logo_killer_is_smooth = params.logo_killer_is_smooth;
		logo_killer_params_.logo_killer_smooth_value = params.logo_killer_smooth_value;
	}
	//-----------------------
};

class decklink_producer_proxy : public core::frame_producer_base
{
	std::unique_ptr<decklink_producer>	producer_;
	const uint32_t						length_;
	executor							executor_;
public:
	explicit decklink_producer_proxy(
			const core::video_format_desc& in_format_desc,
			const spl::shared_ptr<core::frame_factory>& frame_factory,
			const core::video_format_desc& out_format_desc,
			const core::audio_channel_layout& channel_layout,
			int device_index,
			const std::wstring& filter_str,
			uint32_t length,
		    logo_killer_params& logoparams)
		: executor_(L"decklink_producer[" + boost::lexical_cast<std::wstring>(device_index) + L"]")
		, length_(length)
	{
		auto ctx = core::diagnostics::call_context::for_thread();
		executor_.invoke([=]
		{
			core::diagnostics::call_context::for_thread() = ctx;
			com_initialize();
			producer_.reset(new decklink_producer(in_format_desc, device_index, frame_factory, out_format_desc, channel_layout, filter_str));
		});
		//logo killer wxg20170105
		//------------------------
		if (logoparams.logo_killer_left == -1 || logoparams.logo_killer_top == -1 ||
			logoparams.logo_killer_width == -1 || logoparams.logo_killer_height == -1)
		{
			logoparams.logo_killer_enable = false;
		}
		if (!logoparams.logo_killer_enable)
		{
			set_logokiller(out_format_desc.wstr_logo_killer);
		}
		else
			producer_->set_logo_killer_params(logoparams);
		//------------------------
	}

	~decklink_producer_proxy()
	{
		executor_.invoke([=]
		{
			producer_.reset();
			com_uninitialize();
		});
	}

	void set_logokiller(std::wstring  paramstr)
	{
		logo_killer_params vid_params;
		std::string logo_killer_str = u8(paramstr);
		if (logo_killer_str != "")
		{
			logo_killer_str = logo_killer_str.erase(0, 1);
			logo_killer_str = logo_killer_str.erase(logo_killer_str.length() - 1, 1);
			try
			{
				std::string::size_type find = logo_killer_str.find_first_of(",");
				std::string strEnable = logo_killer_str.substr(0, find);
				logo_killer_str = logo_killer_str.erase(0, find + 1);
				vid_params.logo_killer_enable = (bool)atoi(strEnable.c_str());
				if (vid_params.logo_killer_enable)
				{
					find = logo_killer_str.find_first_of(",");
					std::string strLeft = logo_killer_str.substr(0, find);
					logo_killer_str = logo_killer_str.erase(0, find + 1);
					vid_params.logo_killer_left = atoi(strLeft.c_str());

					find = logo_killer_str.find_first_of(",");
					std::string strTop = logo_killer_str.substr(0, find);
					logo_killer_str = logo_killer_str.erase(0, find + 1);
					vid_params.logo_killer_top = atoi(strTop.c_str());

					find = logo_killer_str.find_first_of(",");
					std::string strWidth = logo_killer_str.substr(0, find);
					logo_killer_str = logo_killer_str.erase(0, find + 1);
					vid_params.logo_killer_width = atoi(strWidth.c_str());

					find = logo_killer_str.find_first_of(",");
					std::string strHeight = logo_killer_str.substr(0, find);
					logo_killer_str = logo_killer_str.erase(0, find + 1);
					vid_params.logo_killer_height = atoi(strHeight.c_str());

					find = logo_killer_str.find_first_of(",");
					std::string strIsSmooth = logo_killer_str.substr(0, find);
					logo_killer_str = logo_killer_str.erase(0, find + 1);
					vid_params.logo_killer_is_smooth = (bool)atoi(strIsSmooth.c_str());

					std::string strSmoothValue = logo_killer_str;
					vid_params.logo_killer_smooth_value = atoi(strSmoothValue.c_str());

				}
				if (vid_params.logo_killer_left == -1 || vid_params.logo_killer_top == -1 ||
					vid_params.logo_killer_width == -1 || vid_params.logo_killer_height == -1)
				{
					vid_params.logo_killer_enable = false;
				}
				producer_->set_logo_killer_params(vid_params);

			}
			catch (...)
			{
				CASPAR_LOG_CURRENT_EXCEPTION();
				CASPAR_LOG(error) << L" logo killer params error.";
			}
		}

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

	uint32_t nb_frames() const override
	{
		return length_;
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
	sink.syntax(L"DECKLINK [device:int],DEVICE [device:int] {FILTER [filter:string]} {LENGTH [length:int]} {FORMAT [format:string]} {CHANNEL_LAYOUT [channel_layout:string]}");
	sink.para()->text(L"Allows video sources to be input from BlackMagic Design cards. Parameters:");
	sink.definitions()
		->item(L"device", L"The decklink device to stream the input from. See the Blackmagic control panel for the order of devices in your system.")
		->item(L"filter", L"If specified, sets an FFmpeg video filter to use.")
		->item(L"length", L"Optionally specify a limit on how many frames to produce.")
		->item(L"format", L"Specifies what video format to expect on the incoming SDI/HDMI signal. If not specified the video format of the channel is assumed.")
		->item(L"channel_layout", L"Specifies what audio channel layout to expect on the incoming SDI/HDMI signal. If not specified, stereo is assumed.");
	sink.para()->text(L"Examples:");
	sink.example(L">> PLAY 1-10 DECKLINK DEVICE 2", L"Play using decklink device 2 expecting the video signal to have the same video format as the channel.");
	sink.example(L">> PLAY 1-10 DECKLINK DEVICE 2 FORMAT PAL FILTER yadif=1:-1", L"Play using decklink device 2 expecting the video signal to be in PAL and deinterlace it.");
	sink.example(L">> PLAY 1-10 DECKLINK DEVICE 2 LENGTH 1000", L"Play using decklink device 2 but only produce 1000 frames.");
	sink.example(L">> PLAY 1-10 DECKLINK DEVICE 2 CHANNEL_LAYOUT smpte", L"Play using decklink device 2 and expect smpte surround sound.");
}

spl::shared_ptr<core::frame_producer> create_producer(const core::frame_producer_dependencies& dependencies, const std::vector<std::wstring>& params)
{
	if(params.empty() || !boost::iequals(params.at(0), "decklink"))
		return core::frame_producer::empty();

	auto device_index	= get_param(L"DEVICE", params, -1);
	if(device_index == -1)
		device_index = boost::lexical_cast<int>(params.at(1));

	auto filter_str		= get_param(L"FILTER", params);
	auto length			= get_param(L"LENGTH", params, std::numeric_limits<uint32_t>::max());
	auto in_format_desc = core::video_format_desc(get_param(L"FORMAT", params, L"INVALID"));

	if(in_format_desc.format == core::video_format::invalid)
		in_format_desc = dependencies.format_desc;

	auto channel_layout_spec	= get_param(L"CHANNEL_LAYOUT", params);
	auto channel_layout			= *core::audio_channel_layout_repository::get_default()->get_layout(L"stereo");

	if (!channel_layout_spec.empty())
	{
		auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout_spec);

		if (!found_layout)
			CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout not found."));

		channel_layout = *found_layout;
	}

	boost::ireplace_all(filter_str, L"DEINTERLACE_BOB",	L"YADIF=1:-1");
	boost::ireplace_all(filter_str, L"DEINTERLACE_LQ",	L"SEPARATEFIELDS");
	boost::ireplace_all(filter_str, L"DEINTERLACE",		L"YADIF=0:-1");

	//logo killer wxg20170105
	//----------------------------
	auto logo_killer = get_param(L"LOGO_KILLER", params, L"");
	logo_killer_params vid_params;
	std::string logo_killer_str = u8(logo_killer);
	if (logo_killer_str != "")
	{
		logo_killer_str = logo_killer_str.erase(0, 1);
		logo_killer_str = logo_killer_str.erase(logo_killer_str.length() - 1, 1);
		try
		{
			std::string::size_type find = logo_killer_str.find_first_of(",");
			std::string strEnable = logo_killer_str.substr(0, find);
			logo_killer_str = logo_killer_str.erase(0, find + 1);
			vid_params.logo_killer_enable = (bool)atoi(strEnable.c_str());
			if (vid_params.logo_killer_enable)
			{
				find = logo_killer_str.find_first_of(",");
				std::string strLeft = logo_killer_str.substr(0, find);
				logo_killer_str = logo_killer_str.erase(0, find + 1);
				vid_params.logo_killer_left = atoi(strLeft.c_str());

				find = logo_killer_str.find_first_of(",");
				std::string strTop = logo_killer_str.substr(0, find);
				logo_killer_str = logo_killer_str.erase(0, find + 1);
				vid_params.logo_killer_top = atoi(strTop.c_str());

				find = logo_killer_str.find_first_of(",");
				std::string strWidth = logo_killer_str.substr(0, find);
				logo_killer_str = logo_killer_str.erase(0, find + 1);
				vid_params.logo_killer_width = atoi(strWidth.c_str());

				find = logo_killer_str.find_first_of(",");
				std::string strHeight = logo_killer_str.substr(0, find);
				logo_killer_str = logo_killer_str.erase(0, find + 1);
				vid_params.logo_killer_height = atoi(strHeight.c_str());

				find = logo_killer_str.find_first_of(",");
				std::string strIsSmooth = logo_killer_str.substr(0, find);
				logo_killer_str = logo_killer_str.erase(0, find + 1);
				vid_params.logo_killer_is_smooth = (bool)atoi(strIsSmooth.c_str());

				std::string strSmoothValue = logo_killer_str;
				vid_params.logo_killer_smooth_value = atoi(strSmoothValue.c_str());
			}
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
			CASPAR_LOG(error) << L" logo killer params error.";
		}
	}
	auto producer = spl::make_shared<decklink_producer_proxy>(
			in_format_desc,
			dependencies.frame_factory,
			dependencies.format_desc,
			channel_layout,
			device_index,
			filter_str,
			length,
		vid_params);

	auto get_source_framerate	= [=] { return producer->get_out_framerate(); };
	auto target_framerate		= dependencies.format_desc.framerate;

	return core::create_destroy_proxy(core::create_framerate_producer(
			producer,
			get_source_framerate,
			target_framerate,
			dependencies.format_desc.field_mode,
			dependencies.format_desc.audio_cadence));
}
}}
