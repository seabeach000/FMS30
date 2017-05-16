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

#include "../../StdAfx.h"

#include "video_decoder.h"

#include "../util/util.h"

#include "../../ffmpeg_error.h"

#include <core/frame/frame_transform.h>
#include <core/frame/frame_factory.h>

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/filesystem.hpp>

#include <queue>

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

namespace caspar { namespace ffmpeg {

struct video_decoder::implementation : boost::noncopyable
{
	int										index_				= -1;
	const spl::shared_ptr<AVCodecContext>	codec_context_;

	std::queue<spl::shared_ptr<AVPacket>>	packets_;

	const uint32_t							nb_frames_;

	const int								width_				= codec_context_->width;
	const int								height_				= codec_context_->height;
	bool									is_progressive_;

	tbb::atomic<uint32_t>					file_frame_number_;

	//logo killer20161229
	//-------------------
	std::shared_ptr<SwsContext>				sws_;
	bool                logo_killer_enable;
	int                 logo_killer_left;
	int                 logo_killer_top;
	int                 logo_killer_width;
	int                 logo_killer_height;
	int                 logo_killer_is_smooth;
	int                 logo_killer_smooth_value;
	//-------------------
public:
	explicit implementation(const spl::shared_ptr<AVFormatContext>& context)
		: codec_context_(open_codec(*context, AVMEDIA_TYPE_VIDEO, index_, false))
		, nb_frames_(static_cast<uint32_t>(std::max(context->streams[index_]->nb_frames, try_get_duration(context))))
	{
		file_frame_number_ = 0;

		codec_context_->refcounted_frames = 1;
		//logo killer20161229
		logo_killer_enable = false;
		logo_killer_left = -1;
		logo_killer_top = -1;
		logo_killer_width = -1;
		logo_killer_height = -1;
		logo_killer_is_smooth = 1;
		logo_killer_smooth_value = 10;
		//logo killer
		//---------------
		if (!sws_)
		{
			sws_.reset(sws_getContext(codec_context_->width, codec_context_->height, codec_context_->pix_fmt, codec_context_->width, codec_context_->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, nullptr, nullptr, nullptr), sws_freeContext);
			if (sws_ == nullptr)
				BOOST_THROW_EXCEPTION(caspar_exception() << msg_info("Cannot initialize the conversion context"));
		}
		//---------------
	}

	void push(const std::shared_ptr<AVPacket>& packet)
	{
		if(!packet)
			return;

		if(packet->stream_index == index_ || packet->data == nullptr)
			packets_.push(spl::make_shared_ptr(packet));
	}

	std::shared_ptr<AVFrame> poll()
	{
		if(packets_.empty())
			return nullptr;

		auto packet = packets_.front();

		if(packet->data == nullptr)
		{
			if(codec_context_->codec->capabilities & CODEC_CAP_DELAY)
			{
				auto video = decode(packet);
				if(video)
					return video;
			}

			packets_.pop();

			if (packet->pos != -1)
			{
				file_frame_number_ = static_cast<uint32_t>(packet->pos);
				avcodec_flush_buffers(codec_context_.get());
				return flush_video();
			}
			else // Really EOF
				return nullptr;
		}

		packets_.pop();
		return decode(packet);
	}

	//logo killer20161229
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
	void LogoKiller_YUV(AVFrame* avFrame, int left, int top, int width, int height, bool smoothing, int smoothing_value)
	{
		if (avFrame->format != (int)AV_PIX_FMT_YUV420P && avFrame->format != (int)AV_PIX_FMT_YUV422P)
		{
			return;
		}
		try
		{
			long Pitch_Y = avFrame->linesize[0];
			long Pitch_U = avFrame->linesize[1];
			long Pitch_V = avFrame->linesize[2];
			long Span_CH = avFrame->linesize[0] / avFrame->linesize[1];
			long Span_CV = static_cast<long>(avFrame->height / ((avFrame->data[2] - avFrame->data[1]) / avFrame->linesize[1]));
			if (avFrame->format == (int)AV_PIX_FMT_YUV422P)
			{
				Span_CV = 1;
			}
			if (avFrame->format == (int)AV_PIX_FMT_YUV420P)
			{
				Span_CV = 2;
			}


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
			uint8_t* lpLogoStart_U = avFrame->data[1] + left / Span_CH + top / Span_CV * Pitch_U;
			uint8_t* lpLogoStart_V = avFrame->data[2] + left / Span_CH + top / Span_CV * Pitch_V;

			uint8_t *pFirstLine_Y = lpLogoStart_Y;
			uint8_t *pFirstLine_U = lpLogoStart_U;
			uint8_t *pFirstLine_V = lpLogoStart_V;
			uint8_t *pLastLine_Y = lpLogoStart_Y + height * Pitch_Y;
			uint8_t *pLastLine_U = lpLogoStart_U + height / Span_CV * Pitch_U;
			uint8_t *pLastLine_V = lpLogoStart_V + height / Span_CV * Pitch_V;

			for (int j = 1; j < height; j++)
			{
				uint8_t *pCurrentLine_Y = lpLogoStart_Y + j * Pitch_Y;
				uint8_t *pCurrentLine_U = lpLogoStart_U + j / Span_CV * Pitch_U;
				uint8_t *pCurrentLine_V = lpLogoStart_V + j / Span_CV * Pitch_V;

				for (int i = 1; i < width / 2; i++)
				{
					uint8_t h_lumi1 = static_cast<uint8_t>((pCurrentLine_Y[1] * (width - i * 2) + pCurrentLine_Y[width - 1] * (i * 2)) / (width));
					uint8_t h_lumi2 = static_cast<uint8_t>((pCurrentLine_Y[1] * (width - i * 2 - 1) + pCurrentLine_Y[width - 1] * (i * 2 + 1)) / (width));
					uint8_t h_chroma1 = static_cast<uint8_t>((pCurrentLine_U[0] * (width - i * 2) + pCurrentLine_U[width / Span_CH] * (i * 2)) / (width));
					uint8_t h_chroma2 = static_cast<uint8_t>((pCurrentLine_V[0] * (width - i * 2) + pCurrentLine_V[width / Span_CH] * (i * 2)) / (width));

					uint8_t v_lumi1 = static_cast<uint8_t>((pFirstLine_Y[i * 2] * (height - j) + pLastLine_Y[i * 2] * j) / (height));
					uint8_t v_lumi2 = static_cast<uint8_t>((pFirstLine_Y[i * 2 + 1] * (height - j) + pLastLine_Y[i * 2 + 1] * j) / (height));
					uint8_t v_chroma1 = static_cast<uint8_t>((pFirstLine_U[i * 2 / Span_CH] * (height - j) + pLastLine_U[i * 2 / Span_CH] * j) / (height));
					uint8_t v_chroma2 = static_cast<uint8_t>((pFirstLine_V[i * 2 / Span_CH] * (height - j) + pLastLine_V[i * 2 / Span_CH] * j) / (height));

					pCurrentLine_Y[i * 2] = (h_lumi1 + v_lumi1) / 2;
					pCurrentLine_Y[i * 2 + 1] = (h_lumi2 + v_lumi2) / 2;
					pCurrentLine_U[i * 2 / Span_CH] = (h_chroma1 + v_chroma1) / 2;
					pCurrentLine_V[i * 2 / Span_CH] = (h_chroma2 + v_chroma2) / 2;
				}
			}

			// Patch from Jochen Trener to add adjustable smoothing (Gaussian blur)
			// It is based ón the paper ' An efficient algorithm for Gaussian
			// blur using finite state machines' by F. Waltz and J. Miller
			if (smoothing)
			{
				int i, j, n;
				int Ltmp1, Ltmp2;
				int Utmp1, Utmp2;
				int Vtmp1, Vtmp2;
				int smoothing_runs = smoothing_value;

				left -= 2;
				top -= 1;

				for (n = 0; n < smoothing_runs; ++n)
				{
					memset(LSC0, 0, 768 * sizeof(int));
					memset(USC0, 0, 768 * sizeof(int));
					memset(USC1, 0, 768 * sizeof(int));
					memset(VSC0, 0, 768 * sizeof(int));
					memset(VSC1, 0, 768 * sizeof(int));

					for (j = 0; j < height + 2; j++)
					{
						uint8_t *pAboveLine_Y = avFrame->data[0] + left + (top + j - 1) * Pitch_Y;
						uint8_t *pCurrentLine_Y = avFrame->data[0] + left + (top + j) * Pitch_Y;
						uint8_t *pAboveLine_U = avFrame->data[1] + left / Span_CH + (top + j - 1) / Span_CV * Pitch_U;
						uint8_t *pCurrentLine_U = avFrame->data[1] + left / Span_CH + (top + j) / Span_CV * Pitch_U;
						uint8_t *pAboveLine_V = avFrame->data[2] + left / Span_CH + (top + j - 1) / Span_CV * Pitch_U;
						uint8_t *pCurrentLine_V = avFrame->data[2] + left / Span_CH + (top + j) / Span_CV * Pitch_U;

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
		catch (...)
		{
			//int k = 0;
		}
	}

	std::shared_ptr<AVFrame> decode(spl::shared_ptr<AVPacket> pkt)
	{
		auto decoded_frame = create_frame();
		int frame_finished = 0;
		try {
			THROW_ON_ERROR2(avcodec_decode_video2(codec_context_.get(), decoded_frame.get(), &frame_finished, pkt.get()), "[video_decoder]");
		}
		catch (...)
		{
			CASPAR_LOG(info) << L"avcodec_decode_video2 decode error !";
		}

		// If a decoder consumes less then the whole packet then something is wrong
		// that might be just harmless padding at the end, or a problem with the
		// AVParser or demuxer which puted more then one frame in a AVPacket.

		if(frame_finished == 0)
			return nullptr;

		//logo killer20161229
		//--------------------------------------
		
		av_pix_fmt_count_planes(codec_context_->pix_fmt);
		if (AV_PIX_FMT_YUV422P != codec_context_->pix_fmt && AV_PIX_FMT_YUV420P != codec_context_->pix_fmt)
		{
			spl::shared_ptr<AVFrame> dest_frame(av_frame_alloc(), [](AVFrame* p)
			{
				avpicture_free(reinterpret_cast<AVPicture*>(p));
				av_frame_free(&p);
			});
			av_frame_ref(dest_frame.get(), decoded_frame.get());
			dest_frame->format = AV_PIX_FMT_YUV420P;
			avpicture_fill(reinterpret_cast<AVPicture*>(dest_frame.get()), nullptr, AV_PIX_FMT_YUV420P, codec_context_->width, codec_context_->height);
			avpicture_alloc(reinterpret_cast<AVPicture*>(dest_frame.get()), AV_PIX_FMT_YUV420P, codec_context_->width, codec_context_->height);
			sws_scale(sws_.get(), decoded_frame->data, decoded_frame->linesize, 0, dest_frame->height, dest_frame->data, dest_frame->linesize);
			av_frame_unref(decoded_frame.get());
			decoded_frame = dest_frame;
		}
		if (logo_killer_enable)
		{
			LogoKiller_YUV(decoded_frame.get(), logo_killer_left, logo_killer_top, logo_killer_width, logo_killer_height, logo_killer_is_smooth, logo_killer_smooth_value);
		}

		is_progressive_ = !decoded_frame->interlaced_frame;

		if(decoded_frame->repeat_pict > 0)
			CASPAR_LOG(warning) << "[video_decoder] Field repeat_pict not implemented.";

		++file_frame_number_;

		// This ties the life of the decoded_frame to the packet that it came from. For the
		// current version of ffmpeg (0.8 or c17808c) the RAW_VIDEO codec returns frame data
		// owned by the packet.
		return std::shared_ptr<AVFrame>(decoded_frame.get(), [decoded_frame, pkt](AVFrame*){});
	}

	bool ready() const
	{
		return packets_.size() >= 8;
	}

	bool empty() const
	{
		return packets_.empty();
	}

	uint32_t nb_frames() const
	{
		return std::max(nb_frames_, static_cast<uint32_t>(file_frame_number_));
	}

	std::wstring print() const
	{
		return L"[video-decoder] " + u16(codec_context_->codec->long_name);
	}

	//logo killer20161229
	void set_logo_killer_params(bool enable, int left, int top, int width, int height, int is_smooth, int smooth_value)
	{
		logo_killer_enable = enable;
		logo_killer_left = left;
		logo_killer_top = top;
		logo_killer_width = width;
		logo_killer_height = height;
		logo_killer_is_smooth = is_smooth;
		logo_killer_smooth_value = smooth_value;
	}
};

video_decoder::video_decoder(const spl::shared_ptr<AVFormatContext>& context) : impl_(new implementation(context)){}
void video_decoder::push(const std::shared_ptr<AVPacket>& packet){impl_->push(packet);}
std::shared_ptr<AVFrame> video_decoder::poll(){return impl_->poll();}
bool video_decoder::ready() const{return impl_->ready();}
bool video_decoder::empty() const { return impl_->empty(); }
int video_decoder::width() const{return impl_->width_;}
int video_decoder::height() const{return impl_->height_;}
uint32_t video_decoder::nb_frames() const{return impl_->nb_frames();}
uint32_t video_decoder::file_frame_number() const{return static_cast<uint32_t>(impl_->file_frame_number_);}
bool	video_decoder::is_progressive() const{return impl_->is_progressive_;}
std::wstring video_decoder::print() const{return impl_->print();}

void video_decoder::set_logo_killer_params(bool benable, int left, int top, int width, int height, int is_smooth, int smooth_value)
{
	bool _bEanble = benable;
	if (left == -1 || top == -1 || width == -1 || height == -1)
	{
		_bEanble = false;
	}
	impl_->set_logo_killer_params(_bEanble, left, top, width, height, is_smooth, smooth_value);
}

}}
