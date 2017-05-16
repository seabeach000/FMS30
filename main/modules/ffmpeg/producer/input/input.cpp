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

#include "input.h"

#include "../util/util.h"
#include "../util/flv.h"
#include "../../ffmpeg_error.h"
#include "../../ffmpeg.h"

#include <core/video_format.h>

#include <common/diagnostics/graph.h>
#include <common/executor.h>
#include <common/except.h>
#include <common/os/general_protection_fault.h>
#include <common/param.h>
#include <common/scope_exit.h>

#include <tbb/concurrent_queue.h>
#include <tbb/atomic.h>
#include <tbb/recursive_mutex.h>

#include <boost/range/algorithm.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
	#define __STDC_CONSTANT_MACROS
	#define __STDC_LIMIT_MACROS
	#include <libavformat/avformat.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif

static const size_t MAX_BUFFER_COUNT    = 100;
static const size_t MAX_BUFFER_COUNT_RT = 3;
static const size_t MIN_BUFFER_COUNT    = 50;
static const size_t MAX_BUFFER_SIZE     = 64 * 1000000;

namespace caspar { namespace ffmpeg {
struct input::implementation : boost::noncopyable
{
	const spl::shared_ptr<diagnostics::graph>					graph_;

	const spl::shared_ptr<AVFormatContext>						format_context_; // Destroy this last
	const int													default_stream_index_	= av_find_default_stream_index(format_context_.get());

	const std::wstring											filename_;
	tbb::atomic<uint32_t>										start_;
	tbb::atomic<uint32_t>										length_;
	const bool													thumbnail_mode_;
	tbb::atomic<bool>											loop_;
	uint32_t													frame_number_			= 0;

	tbb::concurrent_bounded_queue<std::shared_ptr<AVPacket>>	buffer_;
	tbb::atomic<size_t>											buffer_size_;

	executor													executor_;
	bool                                                        need_seek_;
	uint32_t                                                    seek_start_;
	bool                                                        bStartSendData_;
	bool														hasFindFirstVideoKeyFrame_;	
	bool                                                        isLiveStream_;
	bool														isTickRunning_;
	int															source_track_origin_;
	boost::posix_time::ptime                                    last_checktime_;
	int															check_timeout_;
	int     													source_afd_code;	// Active format descriptor code from *.mxf
	int64_t                                                     m_offset;
	int64_t                                                     m_lastPTS;
	std::shared_ptr<AVPacket>                                   m_first_pkt = nullptr;
	int                                                         length_time;//length add
	double                                                      time_per_frame_;
	int                                                         length_diff;//length add

	explicit implementation(const spl::shared_ptr<diagnostics::graph> graph, const std::wstring& url_or_file, bool loop, uint32_t start, uint32_t length, bool thumbnail_mode, const ffmpeg_options& vid_params)
		: graph_(graph)
		, format_context_(open_input(url_or_file, vid_params))
		, filename_(url_or_file)
		, thumbnail_mode_(thumbnail_mode)
		, executor_(print())
		,need_seek_(false)
		,bStartSendData_(false)
		,hasFindFirstVideoKeyFrame_(false)
		,isLiveStream_(false)
		,isTickRunning_(false)
		,source_track_origin_(0)
		, source_afd_code(invalid_afd_code)
		,check_timeout_(5)
		,m_offset(0)
		,m_lastPTS(AV_NOPTS_VALUE)
	{
		if (thumbnail_mode_)
			executor_.invoke([]
			{
				enable_quiet_logging_for_thread();
			});

		start_			= start;
		length_			= length;
		if (length != std::numeric_limits<uint32_t>::max())
		{
			double fps = read_fps(*format_context_, 0.0);
			int64_t durationLen = static_cast<int64_t>(format_context_->duration*fps / 1000000 + 1);
			if ((durationLen - length) > 50)
			{
				length_ = length + 50;
			}
			else
			{
				length_ = static_cast<unsigned int>(durationLen);
			}
		}
		loop_			= loop;
		buffer_size_	= 0;
		//Omn seek
		//-----------------------------------------------------------
		int gop_size = 12;
		AVDictionaryEntry *m = nullptr;
		if (format_context_->nb_streams >= 1)
		{
			AVStream* vStream = format_context_->streams[default_stream_index_];
			if (vStream)
			{
				gop_size = vStream->codec->gop_size;
				m = av_dict_get(vStream->metadata, "source_track_origin", m, AV_DICT_IGNORE_SUFFIX);
				if (m)
				{
					if (strcmp(m->value, "") != 0)
					{
						source_track_origin_ = atoi(m->value);
						source_track_origin_ = 0;
					}
				}
				m = av_dict_get(vStream->metadata, "active_format_descriptor", m, AV_DICT_IGNORE_SUFFIX);
				if (m)
				{
					if (strcmp(m->value, "") != 0)
					{
						source_afd_code = 0;
//3.0
						source_afd_code = atoi(m->value);
//2.0 下面都是2.0逻辑这个逻辑 不太明白这个跟ffmpeg的版本有什么区别
						int length1 = static_cast<int>(strlen(m->value));
						for (int i = 0; i < length1; ++i)
						{
							source_afd_code += m->value[i] - '0';
							if (i != length1 - 1)
							{
								source_afd_code <<= 1;
							}
						}
						source_afd_code <<= 3;
						source_afd_code &= 0x4;
					}
				}
				/////////////////////////////////////////////////
			}
		}
		start_ += source_track_origin_;
		//-----------------------------------------------------------
		isLiveStream_ = filename_.find(L"udp", 0) == 0 ||
			filename_.find(L"rtmp", 0) == 0 ||
			filename_.find(L"http", 0) == 0;

		length_time = 0;//length add
		length_diff = 0;

		if (start_ > 0 && !isLiveStream_)
		{
			m_first_pkt = create_packet();
			setCurrentCheckTime(30);
			av_read_frame(format_context_.get(), m_first_pkt.get());
			need_seek_ = true;
			queued_seek(start_);
		}
		seek_start_ = start_;
		graph_->set_color("seek", diagnostics::color(1.0f, 0.5f, 0.0f));
		graph_->set_color("buffer-count", diagnostics::color(0.7f, 0.4f, 0.4f));
		graph_->set_color("buffer-size", diagnostics::color(1.0f, 1.0f, 0.0f));


		tick();
	}

	bool try_pop(std::shared_ptr<AVPacket>& packet)
	{
		auto result = buffer_.try_pop(packet);

		if(result)
		{
			if(packet)
				buffer_size_ -= packet->size;
		}

		if (!isTickRunning_)
			tick();

		graph_->set_value("buffer-size", (static_cast<double>(buffer_size_)+0.001)/MAX_BUFFER_SIZE);
		graph_->set_value("buffer-count", (static_cast<double>(buffer_.size()+0.001)/MAX_BUFFER_COUNT));

		return result;
	}

	std::ptrdiff_t get_max_buffer_count() const
	{
		return thumbnail_mode_ ? 1 : MAX_BUFFER_COUNT;
	}

	std::ptrdiff_t get_min_buffer_count() const
	{
		return thumbnail_mode_ ? 0 : MIN_BUFFER_COUNT;
	}

	std::future<bool> seek(uint32_t target)
	{
		if (!executor_.is_running())
			return make_ready_future(false);

		return executor_.begin_invoke([=]() -> bool
		{
			std::shared_ptr<AVPacket> packet;
			while(buffer_.try_pop(packet) && packet)
				buffer_size_ -= packet->size;

			queued_seek(target);

			tick();

			return true;
		}, task_priority::high_priority);
	}

	std::wstring print() const
	{
		return L"ffmpeg_input[" + filename_ + L")]";
	}

	bool full() const
	{
		return (buffer_size_ > MAX_BUFFER_SIZE || buffer_.size() > get_max_buffer_count()) && buffer_.size() > get_min_buffer_count();
	}
	
	void tick()
	{
		isTickRunning_ = true;
		if (!executor_.is_running())
		{
			isTickRunning_ = false;
			return;
		}

		executor_.begin_invoke([this]
		{
			if (full())
			{
				isTickRunning_ = false;
				return;
			}
			try
			{
				auto packet = create_packet();
				setCurrentCheckTime(30);
				auto ret = av_read_frame(format_context_.get(), packet.get()); // packet is only valid until next call of av_read_frame. Use av_dup_packet to extend its life.

				if(is_eof(ret))
				{
					frame_number_	= 0;

					if(loop_)
					{
						queued_seek(start_);
						graph_->set_tag(diagnostics::tag_severity::INFO, "seek");
						CASPAR_LOG(trace) << print() << " Looping.";
					}
					else
					{
						// Needed by some decoders to decode remaining frames based on last packet.
						auto flush_packet = create_packet();
						flush_packet->data = nullptr;
						flush_packet->size = 0;
						flush_packet->pos = -1;

						buffer_.push(flush_packet);

						executor_.stop();
					}
				}
				else
				{
					//file seek,入点大于0才需要seek
					if (need_seek_ )
					{
						if (packet->stream_index == default_stream_index_)
						{
							int32_t nextSart = 0;
							AVStream* pStream = format_context_.get()->streams[default_stream_index_];
							int gop_size = pStream->codec->gop_size > 0 ? pStream->codec->gop_size:12;
							bool bfindKey = find_key_packet(packet);
							if (!bfindKey)
							{
								nextSart = seek_start_ - gop_size;
								if (nextSart <= 0)
								{
									queued_seek(0);
									need_seek_ = false;
									graph_->set_tag(diagnostics::tag_severity::INFO, "seek");
									CASPAR_LOG(trace) << print() << "Seek Find.";
									//找到后接着把这个packet发送出去，只是实现了包层面的I Frame
									packet = create_packet();
									setCurrentCheckTime(30);
									av_read_frame(format_context_.get(), packet.get());
									bStartSendData_ = true;
									buffer_.clear();
									if (m_first_pkt != nullptr)//有些素材第一个GOP需要第一个包
									{
										THROW_ON_ERROR(ret, "av_read_frame", print());

										if (m_first_pkt->stream_index == default_stream_index_)
											++frame_number_;

										THROW_ON_ERROR2(av_dup_packet(m_first_pkt.get()), print());

										// Make sure that the packet is correctly deallocated even if size and data is modified during decoding.

										int64_t nowPts = 0;
										bool  validPTS = false;
										if (m_first_pkt->pts != AV_NOPTS_VALUE && 0 == m_first_pkt->stream_index)
										{
											validPTS = true;
											nowPts = packet->pts + m_offset;
											if (m_lastPTS != AV_NOPTS_VALUE && (m_lastPTS - nowPts) > 3 * (format_context_->streams[0]->time_base.den / format_context_->streams[0]->time_base.num))
												m_offset += m_lastPTS - nowPts;
										}
										m_first_pkt->pts += m_offset;
										m_first_pkt->dts += m_offset;

										buffer_.try_push(m_first_pkt);
										buffer_size_ += m_first_pkt->size;

										if (validPTS)
											m_lastPTS = m_first_pkt->pts;

										//测试mxf的时间戳
										//if (format_context_->streams[packet->stream_index]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
										//{
										//	CASPAR_LOG(info) << L"video timeStamp = " << packet->pts;
										//}
										//if (format_context_->streams[packet->stream_index]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
										//{
										//	CASPAR_LOG(info) << L"				audio timeStamp = " << packet->pts;
										//}
										graph_->set_value("buffer-size", (static_cast<double>(buffer_size_) + 0.001) / MAX_BUFFER_SIZE);
										graph_->set_value("buffer-count", (static_cast<double>(buffer_.size() + 0.001) / MAX_BUFFER_COUNT));
										m_first_pkt = nullptr;
									}
								}
								else
								{
									queued_seek(nextSart);
									seek_start_ = nextSart;
									bStartSendData_ = false;     //要跳出去,不发送这个packet
								}
							}
							else
							{
								AVStream* pStream1 = format_context_.get()->streams[default_stream_index_];
								double timeSecond = (packet->pts - pStream1->start_time) * av_q2d(pStream1->time_base);
								double frames_per_second = read_fps(*format_context_, 0.0);//av_q2d(pStream->r_frame_rate);
								int32_t nframe = static_cast<int32_t>(timeSecond * frames_per_second);// / length_time;
								length_diff = start_ - nframe;
								length_diff < 0 ? length_diff = 0 : length_diff;

								need_seek_ = false;
								graph_->set_tag(diagnostics::tag_severity::INFO, "seek");
								CASPAR_LOG(trace) << print() << "Seek Find.";
								//找到后接着把这个packet发送出去，只是实现了包层面的I Frame
								bStartSendData_ = true;
							}
						}
					}
					//适用于直播流的情况,但是文件没有入点的情况，音频先到达会有问题
					if (isLiveStream_)
					{
						if (!hasFindFirstVideoKeyFrame_)
						{
							if (format_context_->streams[packet->stream_index]->codec->codec_type == AVMEDIA_TYPE_VIDEO && ((packet->flags & AV_PKT_FLAG_KEY) == AV_PKT_FLAG_KEY))
							{
								if (packet->pts != AV_NOPTS_VALUE)
								{
									hasFindFirstVideoKeyFrame_ = true;
									format_context_->streams[packet->stream_index]->start_time = packet->pts;
									bStartSendData_ = true;
									CASPAR_LOG(info) << L"				Input Video startTime= " << format_context_->streams[packet->stream_index]->start_time;
								}
							}
							else if (format_context_->streams[packet->stream_index]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
							{
								if (packet->pts != AV_NOPTS_VALUE)
									format_context_->streams[packet->stream_index]->start_time = packet->pts;
							}
						}
					}
					else
					{
						hasFindFirstVideoKeyFrame_ = true;
						bStartSendData_ = true;    //文件走到这里必须能够发送
					}

					if (bStartSendData_&&(!need_seek_))
					{
						
						THROW_ON_ERROR(ret, "av_read_frame", print());

						if (packet->stream_index == default_stream_index_)
							++frame_number_;

						THROW_ON_ERROR2(av_dup_packet(packet.get()), print());

						// Make sure that the packet is correctly deallocated even if size and data is modified during decoding.
						auto size = packet->size;
						auto data = packet->data;

						packet = spl::shared_ptr<AVPacket>(packet.get(), [packet, size, data](AVPacket*)
						{
							packet->size = size;
							packet->data = data;
						});

						int64_t nowPts = 0;
						bool  validPTS = false;
						if (packet->pts != AV_NOPTS_VALUE && 0 == packet->stream_index)
						{
							validPTS = true;
							nowPts = packet->pts + m_offset;
							if (m_lastPTS != AV_NOPTS_VALUE && (m_lastPTS - nowPts) > 3 * (format_context_->streams[0]->time_base.den / format_context_->streams[0]->time_base.num))
								m_offset += m_lastPTS - nowPts;
						}
						packet->pts += m_offset;
						packet->dts += m_offset;

						buffer_.try_push(packet);
						buffer_size_ += packet->size;

						if (validPTS)
							m_lastPTS = packet->pts;

						//测试mxf的时间戳
						//if (format_context_->streams[packet->stream_index]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
						//{
						//	CASPAR_LOG(info) << L"video timeStamp = " << packet->pts;
						//}
						//if (format_context_->streams[packet->stream_index]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
						//{
						//	CASPAR_LOG(info) << L"				audio timeStamp = " << packet->pts;
						//}
						graph_->set_value("buffer-size", (static_cast<double>(buffer_size_) + 0.001) / MAX_BUFFER_SIZE);
						graph_->set_value("buffer-count", (static_cast<double>(buffer_.size() + 0.001) / MAX_BUFFER_COUNT));
					}
				}

				tick();
			}
			catch(...)
			{
				if (!thumbnail_mode_)
					CASPAR_LOG_CURRENT_EXCEPTION();
				executor_.stop();
			}
		});
	}

	spl::shared_ptr<AVFormatContext> open_input(const std::wstring& url_or_file, const ffmpeg_options& vid_params)
	{
		AVDictionary* format_options = nullptr;

		CASPAR_SCOPE_EXIT
		{
			if (format_options)
				av_dict_free(&format_options);
		};

		for (auto& option : vid_params)
			av_dict_set(&format_options, option.first.c_str(), option.second.c_str(), 0);

		auto resource_name			= std::wstring();
		auto parts					= caspar::protocol_split(url_or_file);
		auto protocol				= parts.at(0);
		auto path					= parts.at(1);
		AVInputFormat* input_format	= nullptr;

		static const std::set<std::wstring> PROTOCOLS_TREATED_AS_FORMATS = { L"dshow", L"v4l2" };

		if (protocol.empty())
			resource_name = path;
		else if (PROTOCOLS_TREATED_AS_FORMATS.find(protocol) != PROTOCOLS_TREATED_AS_FORMATS.end())
		{
			input_format = av_find_input_format(u8(protocol).c_str());
			resource_name = path;
		}
		else
			resource_name = protocol + L"://" + path;

		AVFormatContext* weak_context = nullptr;
		//wxg20161109
		weak_context = avformat_alloc_context();
		weak_context->probesize = weak_context->probesize * 4;
		weak_context->interrupt_callback.opaque = this;
		weak_context->interrupt_callback.callback = this->check_interrupt;
		setCurrentCheckTime(5);
		THROW_ON_ERROR2(avformat_open_input(&weak_context, u8(resource_name).c_str(), input_format, &format_options), resource_name);

		spl::shared_ptr<AVFormatContext> context(weak_context, [](AVFormatContext* ptr)
		{
			avformat_close_input(&ptr);
		});

		if (format_options)
		{
			std::string unsupported_tokens = "";
			AVDictionaryEntry *t = NULL;
			while ((t = av_dict_get(format_options, "", t, AV_DICT_IGNORE_SUFFIX)) != nullptr)
			{
				if (!unsupported_tokens.empty())
					unsupported_tokens += ", ";
				unsupported_tokens += t->key;
			}
			CASPAR_THROW_EXCEPTION(user_error() << msg_info(unsupported_tokens));
		}

		setCurrentCheckTime(5);
		THROW_ON_ERROR2(avformat_find_stream_info(context.get(), nullptr), resource_name);
		fix_meta_data(*context);
		return context;
	}

	void fix_meta_data(AVFormatContext& context)
	{
		auto video_index = av_find_best_stream(&context, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);

		if (video_index > -1)
		{
			auto video_stream = context.streams[video_index];
			auto video_context = context.streams[video_index]->codec;

			if (boost::filesystem::path(context.filename).extension().string() == ".flv")
			{
				try
				{
					auto meta = read_flv_meta_info(context.filename);
					double fps = boost::lexical_cast<double>(meta["framerate"]);
					video_stream->nb_frames = static_cast<int64_t>(boost::lexical_cast<double>(meta["duration"])*fps);
				}
				catch (...) {}
			}
			else
			{
				auto stream_time = video_stream->time_base;
				auto duration = video_stream->duration;
				auto codec_time = video_context->time_base;
				auto ticks = video_context->ticks_per_frame;

				if (video_stream->nb_frames == 0)
					video_stream->nb_frames = (duration*stream_time.num*codec_time.den) / (stream_time.den*codec_time.num*ticks);
			}
		}
	}

	void queued_seek(const uint32_t target)
	{
		if (!thumbnail_mode_)
			CASPAR_LOG(debug) << print() << " Seeking: " << target;

		int flags = AVSEEK_FLAG_FRAME;
		if(target == 0)
		{
			// Fix VP6 seeking
			int vid_stream_index = av_find_best_stream(format_context_.get(), AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
			if(vid_stream_index >= 0)
			{
				auto codec_id = format_context_->streams[vid_stream_index]->codec->codec_id;
//2.0				if(codec_id == CODEC_ID_VP6A || codec_id == CODEC_ID_VP6F || codec_id == CODEC_ID_VP6)
//3.0
				if (codec_id == AV_CODEC_ID_VP6A || codec_id == AV_CODEC_ID_VP6F || codec_id == AV_CODEC_ID_VP6)
					flags = AVSEEK_FLAG_BYTE;
			}
		}

		auto stream = format_context_->streams[default_stream_index_];


		auto fps = read_fps(*format_context_, 0.0);
		setCurrentCheckTime(5);
		THROW_ON_ERROR2(avformat_seek_file(
			format_context_.get(),
			default_stream_index_,
			std::numeric_limits<int64_t>::min(),
			static_cast<int64_t>((target / fps * stream->time_base.den) / stream->time_base.num) + stream->start_time,
			std::numeric_limits<int64_t>::max(),			
			0), print());

		auto flush_packet	= create_packet();
		flush_packet->data	= nullptr;
		flush_packet->size	= 0;
		flush_packet->pos	= target;

		buffer_.push(flush_packet);
	}
	//seek add 2.0
	//--------------------------------------------------
	bool find_key_packet(spl::shared_ptr<AVPacket> &packet1)
	{
		AVStream* pStream = format_context_.get()->streams[default_stream_index_];
		//seek add1
		//-------------------------------------------------------------
		double timeSecond = (packet1->pts - pStream->start_time) * av_q2d(pStream->time_base);
		double frames_per_second = read_fps(*format_context_, 0.0);//av_q2d(pStream->avg_frame_rate);
		double sencond_per_frame = 1 / frames_per_second;
		time_per_frame_ = sencond_per_frame * pStream->time_base.den;
		int multitime = static_cast<int>(time_per_frame_ / packet1->duration);
		length_time = multitime <= 0 ? 1 : multitime;
		int32_t nframe = static_cast<int32_t>(timeSecond * frames_per_second);// / multitime;
														//--------------------------------------------------------------

		bool iskey = (packet1->flags & AV_PKT_FLAG_KEY) == AV_PKT_FLAG_KEY;
		if (iskey)
		{
			return true;
		}
		else//ly
		{
			if (nframe == 0)
			{
				return true;
			}
		}
		int count = nframe + 1;
		int nCount = 0;
		while (count <= static_cast<int>(start_))
		{
			boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
			packet1 = create_packet();
			av_read_frame(format_context_.get(), packet1.get());
			if (packet1->stream_index != default_stream_index_)
			{	
				continue;
			}
			nCount++;
			if (multitime == 2)
			{
				if (nCount == 2)
				{
					count++;
					nCount = 0;
				}
			}
			else
			{
				count++;
			}
			
			iskey = (packet1->flags & AV_PKT_FLAG_KEY) == AV_PKT_FLAG_KEY;
			if (iskey)
			{
				return true;
			}
		}
		return false;
	}
	//--------------------------------------------------
	//bool find_key_packet(spl::shared_ptr<AVPacket> &packet)//这里传入参数必须是引用类型，否则会传不出正确的帧
	//{
	//	//目前认为只有文件是带有入点的，其余的入点都是0
	//	bool iskey = (packet->flags & AV_PKT_FLAG_KEY) == AV_PKT_FLAG_KEY;
	//	if (iskey)
	//	{
	//		CASPAR_LOG(info) << L"First Key Frame timestamp " << packet->pts;
	//		return true;
	//	}
	//		
	//	auto fps = read_fps(*format_context_, 0.0);
	//	AVStream* pStream = format_context_.get()->streams[default_stream_index_];
	//	int64_t startPTS = ((seek_start_ + 10) / fps * pStream->time_base.den) / pStream->time_base.num;
	//	if (packet->pts != AV_NOPTS_VALUE &&(packet->pts - pStream->start_time > startPTS))
	//	{
	//		return false;              //只要return false 就会向前继续找
	//	}
	//	
	//	//以下必须重新创建packet（不重新创建则会内存泄漏），并且create_packet函数中不能初始化packet否则会出现一些报错，同时也必须sleep否则运行太快占cpu
	//	int64_t comparePts = packet->pts;
	//	while (packet->pts == AV_NOPTS_VALUE ||
	//		(packet->pts != AV_NOPTS_VALUE && ((comparePts - pStream->start_time) <= startPTS)))
	//	{	
	//		boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
	//		packet = create_packet();
	//		auto ret = av_read_frame(format_context_.get(), packet.get());
	//		if (ret < 0)
	//		{
	//			CASPAR_LOG(info) << L"av_read_frame return error,stop continue find key frame !";
	//			return true;  
	//		}
	//		if (packet->stream_index != default_stream_index_)
	//			continue;
	//		else
	//			comparePts = packet->pts;
	//		iskey = (packet->flags & AV_PKT_FLAG_KEY) == AV_PKT_FLAG_KEY;
	//		if (iskey)
	//		{
	//			CASPAR_LOG(info) << L"pStream->start_time= " << pStream->start_time << L"First Key Frame timestamp " << packet->pts;
	//			return true;
	//		}
	//	}

	//	return false;
	//}
	bool is_eof(int ret)
	{
		if (isLiveStream_)
		{
			return false;
		}
		if(ret == AVERROR(EIO))
			CASPAR_LOG(trace) << print() << " Received EIO, assuming EOF. ";
		if(ret == AVERROR_EOF)
			CASPAR_LOG(trace) << print() << " Received EOF. ";

	//	return ret == AVERROR_EOF || ret == AVERROR(EIO) || frame_number_ >= length_; // av_read_frame doesn't always correctly return AVERROR_EOF;
		if (length_ == std::numeric_limits<uint32_t>::max())
		{
			return ret == AVERROR_EOF || ret == AVERROR(EIO) || frame_number_ >= length_;
		}
		else
		{
			return ret == AVERROR_EOF || ret == AVERROR(EIO) || frame_number_ >= ((length_ + length_diff) * (length_time == 0 ? 1 : length_time)); // av_read_frame doesn't always correctly return AVERROR_EOF;
		}
	}

	int num_audio_streams() const
	{
		return 0; // TODO
	}
	static int check_interrupt(void* ctx)
	{
#ifdef  _DEBUG
		return false;
#endif
		caspar::ffmpeg::input::implementation* input0 = (caspar::ffmpeg::input::implementation*)ctx;
		boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
		time_elapse = boost::posix_time::microsec_clock::universal_time() - input0->last_checktime_;
		if (time_elapse.total_seconds() > input0->check_timeout_)
		{
			return true;
		}
		return false;
	}
	void setCurrentCheckTime(int timeout)
	{
		last_checktime_ = boost::posix_time::microsec_clock::universal_time();
		check_timeout_ = timeout;
	}
};

input::input(const spl::shared_ptr<diagnostics::graph>& graph, const std::wstring& url_or_file, bool loop, uint32_t start, uint32_t length, bool thumbnail_mode, const ffmpeg_options& vid_params)
	: impl_(new implementation(graph, url_or_file, loop, start, length, thumbnail_mode, vid_params))
{
	source_afd_code = impl_->source_afd_code;
}
bool input::eof() const {return !impl_->executor_.is_running();}
bool input::try_pop(std::shared_ptr<AVPacket>& packet){return impl_->try_pop(packet);}
spl::shared_ptr<AVFormatContext> input::context(){return impl_->format_context_;}
void input::start(uint32_t value){impl_->start_ = value;}
uint32_t input::start() const{return impl_->start_;}
void input::length(uint32_t value){impl_->length_ = value;}
uint32_t input::length() const{return impl_->length_;}
void input::loop(bool value){impl_->loop_ = value;}
bool input::loop() const{return impl_->loop_;}
int input::num_audio_streams() const { return impl_->num_audio_streams(); }
std::future<bool> input::seek(uint32_t target){return impl_->seek(target);}
double input::length_time() { return impl_->length_time; }//seek add1
uint32_t input::start_position() { return impl_->start_; }//Omn Seek

bool input::hasUpdateAVstarttime()
{
	return impl_->hasFindFirstVideoKeyFrame_;
}

uint32_t input::source_track_orign()
{
	return impl_->source_track_origin_;
}

}}
