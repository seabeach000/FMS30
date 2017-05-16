//
// Created by zibj 2016/10/25.
//
#include "ndi_consumer.h"
#include <Processing.NDI.Lib.h>


#include <common/memcpy.h>
#include <common/future.h>
#include <common/param.h>

#include <common/os/general_protection_fault.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
#include <libavutil/channel_layout.h>
#include <core/frame/frame.h>
#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>
#include <core/help/help_sink.h>
#include <boost/algorithm/string.hpp>
#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>
#include <vector>
//#include <atlbase.h>
//#include <atlstr.h>
 

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable : 4244)
#endif
extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
}
#if defined(_MSC_VER)
#pragma warning (pop)
#endif
#define AUDIO32_t 0x7fffffff	
namespace caspar {
	namespace ndi {

		struct AudioSampleCalc
		{
			AudioSampleCalc()
			{
				Reset();
			}
			double m_dblDiff;
			int NextSamples(double _dblFrameRate, int _nAudioFreq)
			{
				double dblNeed = (double)_nAudioFreq / _dblFrameRate;
				int nSamples = (int)(dblNeed + m_dblDiff);
				m_dblDiff += (dblNeed - nSamples);
				return nSamples;
			}

			void Reset()
			{
				m_dblDiff = 0;
			}
		};

		struct configuration
		{
			std::wstring ratio = L"16:9";
			std::wstring name = L"My Video";
			//std::wstring groups = L"FMS";

			bool						vanc_output_ = false;//config vanc
			core::audio_channel_layout	out_channel_layout = core::audio_channel_layout::invalid();
			core::audio_channel_layout get_adjusted_layout(const core::audio_channel_layout& in_layout) const
			{
				auto adjusted = out_channel_layout == core::audio_channel_layout::invalid() ? in_layout : out_channel_layout;

				if (adjusted.num_channels == 1) // Duplicate mono-signal into both left and right.
				{
					adjusted.num_channels = 2;
					adjusted.channel_order.push_back(adjusted.channel_order.at(0)); // Usually FC -> FC FC
				}
				else if (adjusted.num_channels == 2)
				{
					adjusted.num_channels = 2;
				}
				else if (adjusted.num_channels <= 8)
				{
					adjusted.num_channels = 8;
				}
				else // Over 8 always pad to 16 or drop >16
				{
					adjusted.num_channels = 16;
				}

				return adjusted;
			}
		};

		//std::vector<HANDLE>		stream_exes_handles;
		//bool					run_time_check_thread = false;
		//tbb::mutex				stream_exe_mutex;

		struct ndi_consumer : boost::noncopyable
		{
			NDIlib_send_instance_t								pNDI_send;
			const configuration									config_;
			core::video_format_desc								format_desc_;

			tbb::atomic<bool>									is_running_;
			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
			boost::thread										thread_;
			AudioSampleCalc										m_audCalc;
			const core::audio_channel_layout					in_channel_layout_;
			const core::audio_channel_layout					out_channel_layout_ = config_.get_adjusted_layout(in_channel_layout_);
			std::shared_ptr<SwrContext>							swr_;
		public:

			std::future<bool> send(core::const_frame frame)
			{
				bool b = frame_buffer_.try_push(frame);
				return make_ready_future(is_running_.load());
			}
			std::wstring print() const
			{
				return config_.name;// +L" " + channel_and_format();
			}

			ndi_consumer(const configuration& config,
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& in_channel_layout
			) : config_(config)
				, format_desc_(format_desc)
				, in_channel_layout_(in_channel_layout)
			{
				//int intype = av_get_default_channel_layout(in_channel_layout.num_channels);//AV_CH_LAYOUT_MONO
				//int outtype = av_get_default_channel_layout(out_channel_layout_.num_channels);// ‰»Î…˘µ¿
				//swr_ = {
				//	swr_alloc_set_opts(
				//		nullptr,
				//		outtype,
				//		AV_SAMPLE_FMT_S32,
				//		format_desc_.audio_sample_rate,
				//		intype ,
				//		AV_SAMPLE_FMT_S32,
				//		format_desc_.audio_sample_rate,
				//		0,
				//		nullptr),
				//	[](SwrContext* p)
				//{
				//	swr_free(&p);
				//}
				//};
				//swr_init(swr_.get());

				frame_buffer_.set_capacity(1);
				is_running_ = false;

				/////ndi
				std::string s = u8(config_.name);
				const NDIlib_send_create_t NDI_send_create_desc = { s.c_str(), NULL, true, true };
				pNDI_send = NDIlib_send_create(&NDI_send_create_desc);

				if (!pNDI_send)
				{
					CASPAR_THROW_EXCEPTION(invalid_argument() << msg_info("NDILIB SEND CREATE ERROR"));
					return;
				}

				static const char* p_connection_string = "<ndi_product long_name=\"NDILib Send Example.\" "
					"             short_name=\"NDILib Send\" "
					"             manufacturer=\"CoolCo, inc.\" "
					"             version=\"1.000.000\" "
					"             session=\"default\" "
					"             model_name=\"S1\" "
					"             serial=\"ABCDEFG\"/>";
				const NDIlib_metadata_frame_t NDI_connection_type = {
					(int)::strlen(p_connection_string),
					NDIlib_send_timecode_synthesize,
					(char*)p_connection_string
				};
				NDIlib_send_add_connection_metadata(pNDI_send, &NDI_connection_type);
				is_running_ = true;
				thread_ = boost::thread([this] {run(); });
			}

			void run()
			{
				while (is_running_)
				{
					core::const_frame frame;
					if (!frame_buffer_.try_pop(frame))
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
						continue;
					}


					
					int Samples = m_audCalc.NextSamples(format_desc_.fps, format_desc_.audio_sample_rate);
					

					std::vector<std::wstring> token;
					float ads = 0.0;
					float asf = 0.0;
					boost::split(token, config_.ratio, boost::is_any_of(L":"));
					if (token.size() == 2)
					{
						ads = (float)atof(u8(token[0]).c_str());
						asf = (float)atof(u8(token[1]).c_str());
					}
					NDIlib_video_frame_t NDI_video_frame = {

						format_desc_.width, format_desc_.height,

						NDIlib_FourCC_type_BGRA,

						format_desc_.framerate.numerator() * 1000,format_desc_.framerate.denominator() * 1000,
						// The aspect ratio (16:9)
						ads / asf,
						// This is a progressive frame
						NDIlib_frame_format_type_progressive,
						// Timecode (synthesized for us !)
						NDIlib_send_timecode_synthesize,
						// The video memory used for this frame
						(uint8_t*)malloc(format_desc_.width * format_desc_.height * 4),
						// The line to line stride of this image
						format_desc_.width * 4
					};

					/*tbb::parallel_for(0, (int)format_desc_.height, 1, [&](int y)
					{
						fast_memcpy(
							reinterpret_cast<char*>(NDI_video_frame.p_data) + y * format_desc_.width * 4,
							(frame.image_data().begin()) + y * format_desc_.width * 4,
							format_desc_.width * 4
						);
					});*/
					fast_memcpy(
						reinterpret_cast<char*>(NDI_video_frame.p_data),
						(frame.image_data().begin()),
						format_desc_.height * format_desc_.width * 4
					);

					NDIlib_audio_frame_t NDI_audio_frame = {
						// 48kHz
						format_desc_.audio_sample_rate,
						// The number of audio channels
						out_channel_layout_.num_channels,
						// The number of audio samples per channel
						Samples,
						// The timecode of this frame in 10ns intervals
						0LL,
						// The audio data
						(float*)malloc(Samples * frame.audio_channel_layout().num_channels * sizeof(float)),
						// The audio channel stride
						Samples * sizeof(float)
					};
					int audio_frame_size = ((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);


					void * source = (char *)malloc(frame.audio_data().size() * 4);
					void *outbuf = (char *)malloc(frame.audio_data().size() * 4);
					/*caspar::array<const int32_t>::iterator it;

					it = frame.audio_data().begin();
					int* p_ch = (int *)source;
					for (int sample_no = 0; sample_no < frame.audio_data().size();sample_no++)
					{
						p_ch[sample_no] = (int)*it;
						if (*it != 0)
						{
							int s = *it;
						}
						it++;
					}*/
					/*const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&source);
					uint8_t *out[] = { reinterpret_cast<uint8_t*>((uint8_t*)outbuf) };*/

					/*const auto channel_samples = swr_convert(
						swr_.get(),
						out,
						audio_frame_size,
						in,
						Samples);*/
					/*int *pch = (int *)source;
					int i = 0;
					for (int ch = 0; ch < out_channel_layout_.num_channels; ch++)
					{
						i = 0;
						i += ch;
						float* p_ch = (float*)((uint8_t*)NDI_audio_frame.p_data + ch*NDI_audio_frame.channel_stride_in_bytes);
						for (int sample_no = 0; sample_no < Samples;sample_no++)
						{
							p_ch[sample_no] = (float)pch[i] / (float)AUDIO32_t;
							i += out_channel_layout_.num_channels;
						}
					}*/

					array<const int32_t>::iterator it;



					for (int ch = 0; ch < out_channel_layout_.num_channels; ch++)
					{
						it = frame.audio_data().begin();
						it += ch;
						float* p_ch = (float*)((uint8_t*)NDI_audio_frame.p_data + ch*NDI_audio_frame.channel_stride_in_bytes);
						for (int sample_no = 0; sample_no < Samples;sample_no++)
						{
							p_ch[sample_no] = (float)*it / (float)AUDIO32_t;
							it += frame.audio_channel_layout().num_channels;
						}
					}

					free(source);
					free(outbuf);
					NDIlib_send_send_audio(pNDI_send, &NDI_audio_frame);
					NDIlib_send_send_video(pNDI_send, &NDI_video_frame);
					free((void*)NDI_video_frame.p_data);
					free((void*)NDI_audio_frame.p_data);
				}
			}
			~ndi_consumer()
			{
				release();
			}

			void release()
			{

				NDIlib_send_destroy(pNDI_send);

				// Not required, but nice
				NDIlib_destroy();

				is_running_ = false;
				frame_buffer_.try_push(core::const_frame::empty());
				thread_.join();
				//m_Object->ObjectVirtualSourceCreate(0, (BSTR)config_.name.c_str(), L"");
				//m_Object.Release();
				//SetEvent(stream_event_handle);
				CASPAR_LOG(info) << L" NID virtual source successfully released.";
			}
		};

		struct ndi_consumer_proxy : public core::frame_consumer
		{
			core::monitor::subject			monitor_subject_;
			const configuration				config_;
			std::unique_ptr<ndi_consumer> consumer_;
			// 			//core::interaction_sink*			sink_;
		public:
			ndi_consumer_proxy(const configuration& config)
				:config_(config)
			{
			}

			~ndi_consumer_proxy()
			{
				if (consumer_)
				{
					auto str = print();
					consumer_.reset();
					CASPAR_LOG(info) << str << L" Successfully Uninitialized.";
				}
			}

			// Methods
			std::future<bool> send(core::const_frame frame) override
			{
				return consumer_->send(frame);
			}
			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& audio_channel_layout,
				int channel_index) override
			{
				consumer_.reset();
				consumer_.reset(new ndi_consumer(config_, format_desc, audio_channel_layout));

				//CASPAR_LOG(info) << print() << L" Successfully Initialized.";
			}

			// monitor::observable
			core::monitor::subject& monitor_output()
			{
				return monitor_subject_;
			}

			// Properties

			std::wstring print() const override
			{
				return consumer_ ? consumer_->print() : L"[ndi_consumer]";
			}

			std::wstring name() const override
			{
				return L"ndi";
			}

			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;
				info.add(L"type", L"ndi");
				return info;
			}

			bool has_synchronization_clock() const override
			{
				return false;
			}

			int buffer_depth() const override// -1 to not participate in frame presentation synchronization
			{
				return 2;
			}

			int index() const override
			{
				return 601;
			}

			int64_t presentation_frame_age_millis() const override
			{
				return 1;
			}
		};

		void describe_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"NDI Consumer.");
		}

		spl::shared_ptr<core::frame_consumer> create_consumer(const std::vector<std::wstring>& params, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || !boost::iequals(params.at(0), L"NDI"))
				return core::frame_consumer::empty();
			configuration config;
			if (contains_param(L"NAME", params))
				config.name = get_param(L"SOURCE", params);

			if (contains_param(L"channel-layout", params))
			{
				auto channel_layout = get_param(L"channel-layout", params);
				if (!channel_layout.empty())
				{
					CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

						auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(channel_layout);

					if (!found_layout)
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + channel_layout + L" not found."));

					config.out_channel_layout = *found_layout;
				}
			}
			return spl::make_shared<ndi_consumer_proxy>(config);
		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			configuration config;
			config.name = ptree.get(L"source", config.name);
			config.ratio = ptree.get(L"ratio", config.ratio);
			//config.groups = ptree.get(L"groups",config.groups);
			auto channel_layout = ptree.get_optional<std::wstring>(L"channel-layout");

			if (channel_layout)
			{
				CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

					auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(*channel_layout);

				if (!found_layout)
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + *channel_layout + L" not found."));

				config.out_channel_layout = *found_layout;
			}
			return spl::make_shared<ndi_consumer_proxy>(config);
		}
	}
}




