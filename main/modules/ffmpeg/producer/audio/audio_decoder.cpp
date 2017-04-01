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

#include "audio_decoder.h"

#include "../util/util.h"
#include "../../ffmpeg_error.h"

#include <core/video_format.h>
#include <core/mixer/audio/audio_util.h>

#include <common/cache_aligned_vector.h>

#include <queue>

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libswresample/swresample.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

namespace caspar { namespace ffmpeg {

struct audio_decoder::implementation : boost::noncopyable
{
	int										index_;
	const spl::shared_ptr<AVCodecContext>	codec_context_;
	const int								out_samplerate_;

	cache_aligned_vector<int32_t>			buffer_;

	std::queue<spl::shared_ptr<AVPacket>>	packets_;

	std::shared_ptr<SwrContext>				swr_				{
																	swr_alloc_set_opts(
																			nullptr,
																			codec_context_->channel_layout
																					? codec_context_->channel_layout
																					: av_get_default_channel_layout(codec_context_->channels),
																			AV_SAMPLE_FMT_S32,
																			out_samplerate_,
																			codec_context_->channel_layout
																					? codec_context_->channel_layout
																					: av_get_default_channel_layout(codec_context_->channels),
																			codec_context_->sample_fmt,
																			codec_context_->sample_rate,
																			0,
																			nullptr),
																	[](SwrContext* p)
																	{
																		swr_free(&p);
																	}
																};
	int64_t                                                         video_FristTimestamp;
	bool															hasAudioSyncVideo_;
	AVRational									                    stream_Timebase_;
	int64_t                                                         lastAudioPts_;
public:
	explicit implementation(int stream_index, const spl::shared_ptr<AVFormatContext>& context, int out_samplerate)
		: index_(stream_index)
		, codec_context_(open_codec(*context, AVMEDIA_TYPE_AUDIO, index_, false))
		, out_samplerate_(out_samplerate)
		, buffer_(10 * out_samplerate_ * codec_context_->channels) // 10 seconds of audio
		,hasAudioSyncVideo_(false)
		,stream_Timebase_(context->streams[index_]->time_base)
		,lastAudioPts_(0)
	{
		if(!swr_)
			CASPAR_THROW_EXCEPTION(bad_alloc());

		THROW_ON_ERROR2(swr_init(swr_.get()), "[audio_decoder]");

		codec_context_->refcounted_frames = 1;
	}

	void push(const std::shared_ptr<AVPacket>& packet)
	{
		if(!packet)
			return;

		if(packet->stream_index == index_ || packet->data == nullptr)
			packets_.push(spl::make_shared_ptr(packet));
	}

	std::shared_ptr<core::mutable_audio_buffer> poll()
	{
		if(packets_.empty())
			return nullptr;

		auto packet = packets_.front();

		if(packet->data == nullptr)
		{
			packets_.pop();
			avcodec_flush_buffers(codec_context_.get());
			return flush_audio();
		}

		auto audio = decode(*packet);

		if(packet->size == 0)
			packets_.pop();

		return audio;
	}

	std::shared_ptr<core::mutable_audio_buffer> decode(AVPacket& pkt)
	{
		auto decoded_frame = create_frame();

		int got_frame = 0;
		int len = 0;
		try {
			len = THROW_ON_ERROR2(avcodec_decode_audio4(codec_context_.get(), decoded_frame.get(), &got_frame, &pkt), "[audio_decoder]");
		}
		catch (...) {
			CASPAR_LOG(info) << L"avcodec_decode_audio4 decode error !";
		}		

		if (len == 0)
		{
			pkt.size = 0;
			return nullptr;
		}

		pkt.data += len;
		pkt.size -= len;

		if (!got_frame)
			return nullptr;

		if (!hasAudioSyncVideo_)
		{
			if (decoded_frame->pkt_pts < video_FristTimestamp)
				return nullptr;
		}
		memset(buffer_.data(), 0, buffer_.size() * sizeof(int32_t));

		const uint8_t **in = const_cast<const uint8_t**>(decoded_frame->extended_data);
		uint8_t* out[] = { reinterpret_cast<uint8_t*>(buffer_.data()) };

		const auto channel_samples = swr_convert(
				swr_.get(),
				out,
				static_cast<int>(buffer_.size()) / codec_context_->channels,
				in,
				decoded_frame->nb_samples);

		//ֱ�����п�����Ƶʱ���������Ƶ����Ҫ���侲��
		int64_t needAddSample = 0; 
		int64_t uints = stream_Timebase_.den / stream_Timebase_.num;
		uints = uints / 1000;
		int64_t videoAduioGap = 0;//ms
		if (hasAudioSyncVideo_)  //ֻ���ڿ�ͷ��ͬ���Ѿ�������֮��Ŵ����м��ͬ��
		{
			int64_t sampleDur = (decoded_frame->nb_samples * 1000) / decoded_frame->sample_rate;
			int audioGap = (decoded_frame->pkt_pts - lastAudioPts_) / uints - sampleDur;
			if (audioGap > 1 && audioGap < 5000)
			{
				needAddSample = (out_samplerate_ * codec_context_->channels)*audioGap / 1000;
				CASPAR_LOG(warning) << L"Fill the mute data audioGap :(ms)  " << audioGap;
			}
			lastAudioPts_ = decoded_frame->pkt_pts;
		}
		if (!hasAudioSyncVideo_)
		{
			lastAudioPts_ = decoded_frame->pkt_pts;
			hasAudioSyncVideo_ = true;
			int64_t audioSyncVideo = decoded_frame->pkt_pts - video_FristTimestamp;
			if (audioSyncVideo > 30*uints && audioSyncVideo < 5000*uints)
			{
				videoAduioGap = audioSyncVideo / uints;
				needAddSample = (out_samplerate_ * codec_context_->channels)*videoAduioGap / 1000;				
			}
			CASPAR_LOG(info) << L"   First audio data : decoded_frame->pkt_pts : " << decoded_frame->pkt_pts << L"video_FristTimestamp : " << video_FristTimestamp << L"videoAduioGap :(ms) " << videoAduioGap;
		}

		return std::make_shared<core::mutable_audio_buffer>(
				buffer_.begin(),
				buffer_.begin() + channel_samples * decoded_frame->channels + needAddSample);
	}

	bool ready() const
	{
		return packets_.size() > 10;
	}

	std::wstring print() const
	{
		return L"[audio-decoder] " + u16(codec_context_->codec->long_name);
	}

	uint64_t ffmpeg_channel_layout() const
	{
		if (codec_context_->channel_layout == 0)
			return av_get_default_channel_layout(codec_context_->channels);
		else
			return codec_context_->channel_layout;
	}
};

audio_decoder::audio_decoder(int stream_index, const spl::shared_ptr<AVFormatContext>& context, int out_samplerate) : impl_(new implementation(stream_index, context, out_samplerate)){}
void audio_decoder::push(const std::shared_ptr<AVPacket>& packet){impl_->push(packet);}
bool audio_decoder::ready() const{return impl_->ready();}
std::shared_ptr<core::mutable_audio_buffer> audio_decoder::poll() { return impl_->poll(); }
int	audio_decoder::num_channels() const { return impl_->codec_context_->channels; }
uint64_t audio_decoder::ffmpeg_channel_layout() const { return impl_->ffmpeg_channel_layout(); }
std::wstring audio_decoder::print() const{return impl_->print();}
void audio_decoder::set_FirstVideoTimecode(int64_t firstVideoPts) { impl_->video_FristTimestamp = firstVideoPts; }

}}