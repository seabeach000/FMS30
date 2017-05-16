//
// Created by zibj 2016/10/25.
//

#include "dshow_consumer.h"

#include <common/diagnostics/graph.h>
// #include <common/gl/gl_check.h>
// #include <common/log.h>
// #include <common/memory.h>
// #include <common/array.h>
// #include <common/memshfl.h>
#include <common/memcpy.h>
// #include <common/utf.h>
// #include <common/prec_timer.h>
#include <common/future.h>
// #include <common/timer.h>
#include <common/param.h>
#include <common/os/general_protection_fault.h>
// #include <common/scope_exit.h>
// 
// //#include <windows.h>
// 
// #include <ffmpeg/producer/filter/filter.h>
// #include <ffmpeg/producer/util/util.h>
// 
#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>
// #include <core/interaction/interaction_sink.h>
#include <core/help/help_sink.h>
// #include <core/help/help_repository.h>
// 
// #include <boost/circular_buffer.hpp>
// #include <boost/lexical_cast.hpp>
// #include <boost/property_tree/ptree.hpp>
// #include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
// 
#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>
// 
// #include <asmlib.h>
// 
// #include <algorithm>
#include <vector>

//medialooks
#include <MDefines.h>
#include <MPlatform.h>
// 
#include <atlbase.h>
#include <atlstr.h>
 
// #include <string.h>
// #include "stdlib.h"
// #include "math.h"

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

namespace caspar {
	namespace dshow {

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
			std::wstring name = L"DShow Consumer";
		};

		std::vector<HANDLE>		stream_exes_handles;
		bool					run_time_check_thread = false;
		tbb::mutex				stream_exe_mutex;

		struct dshow_consumer : boost::noncopyable
 		{
			const spl::shared_ptr<diagnostics::graph>			graph_;
			caspar::timer										tick_timer_;

	 		const configuration									config_;
			core::video_format_desc								format_desc_;
			int													channel_index_;

  			tbb::atomic<bool>									is_running_;
  			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
 		
			bool												IsPushStreamProcessStarted;
			
			//medialooks
			CComPtr<IMFrames>	 								m_Frames;
			CComPtr<IMReceiver>									m_Proxy;
			CComPtr<IMObject>   								m_Object;
			M_VID_PROPS 										props;
			//
			
			LONGLONG   											frame_time;
			LONGLONG   											frame_time_interval;

			boost::thread										thread_;
			boost::thread										checkthread_;
			AudioSampleCalc										m_audCalc;
			HANDLE 												stream_event_handle;

		public:

			std::future<bool> send(core::const_frame frame)
			{
				graph_->set_value("tick-time", tick_timer_.elapsed()*format_desc_.fps*0.5);
				if(!frame_buffer_.try_push(frame))
					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
				tick_timer_.restart();
				return make_ready_future(is_running_.load());
			}
			std::wstring print() const
			{
				return L"dshow_consumer[" + config_.name + L"|" + boost::lexical_cast<std::wstring>(channel_index_) + L"|" + format_desc_.name + L"]";
			}

  			dshow_consumer(const configuration& config,
				const core::video_format_desc& format_desc,
				int channel_index
 				):config_(config)
				,format_desc_(format_desc)
				,channel_index_(channel_index)
  			{
				frame_buffer_.set_capacity(1);
				IsPushStreamProcessStarted = false;

				graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				graph_->set_text(print());
				diagnostics::register_graph(graph_);

				HRESULT hr;
				is_running_ = true;

				hr = m_Frames.CoCreateInstance(__uuidof(MFrames));
				if (FAILED(hr))
				{
					CASPAR_LOG(info) << L"Failed to create m_Frames.";
				}
				hr = m_Proxy.CoCreateInstance(__uuidof(MProxy));
				if (FAILED(hr))
				{
					CASPAR_LOG(info) << L"Failed to create m_Props.";
				}
				m_Object = CComQIPtr<IMObject>(m_Proxy);
				m_Object->ObjectNameSet((BSTR)config_.name.c_str());
				m_Object->ObjectStart(nullptr);

				hr = m_Object->ObjectVirtualSourceCreate(1, (BSTR)config_.name.c_str(), L"");
				VideoFormatTransfer(format_desc_, props);

				frame_time = 0;
				frame_time_interval = 10000000 / format_desc_.fps;

 				thread_ = boost::thread([this] {run(); });
				if (run_time_check_thread == false)
				{
					checkthread_ = boost::thread([this] {PushStreamBackGround_runtime_check(); });
					run_time_check_thread = true;
				}
 			}

			void PushStreamBackGround_runtime_check()
			{
				while (true)
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
					tbb::mutex::scoped_lock lock(stream_exe_mutex);
					if (stream_exes_handles.empty())
					{
						continue;
					}
					for (std::vector<HANDLE>::iterator it = stream_exes_handles.begin();
						it != stream_exes_handles.end();
						)
					{
						DWORD ret = WaitForSingleObject(*it, 1000);
						if (ret == WAIT_OBJECT_0)
						{
							it = stream_exes_handles.erase(it);
							CASPAR_LOG(info) << L"Unexpected exception happened, the PushStreamBackGround.exe has been quit!";

							continue;
						}

						++it;
					}
				}
 			}
  
			void run()
 			{
				ensure_gpf_handler_installed_for_thread(
					"dshow-consumer-thread");
				char* pNewData_Y_Reverse = nullptr;
				init();
				caspar::timer pushframe_timer;
				while (is_running_)
				{
					core::const_frame frame;
					if (!frame_buffer_.try_pop(frame))
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
						continue;
					}
					pushframe_timer.restart();
					CComQIPtr<IMFrame> pMFrame;
					if (!pNewData_Y_Reverse)
					{
						pNewData_Y_Reverse = (char*)malloc(frame.size());
					}

					if (pNewData_Y_Reverse)
					{
						/*tbb::parallel_for(0, (int)format_desc_.height, 1, [&](int y)
						{
							fast_memcpy(
								reinterpret_cast<char*>(pNewData_Y_Reverse) + y * format_desc_.width * 4,
								(frame.image_data().begin()) + (format_desc_.height - y - 1) * format_desc_.width * 4,
								format_desc_.width * 4
							);
						});*/
						for (int i = 0; i < (int)format_desc_.height; i++)
						{
							fast_memcpy(
								reinterpret_cast<char*>(pNewData_Y_Reverse) + i * format_desc_.width * 4,
								(frame.image_data().begin()) + (format_desc_.height - i - 1) * format_desc_.width * 4,
								format_desc_.width * 4
							);
						}
						WCHAR _bsProps[50] = { 0 };

						int Samples = m_audCalc.NextSamples(props.dblRate, format_desc_.audio_sample_rate);
						swprintf(_bsProps, L"audio_samples=%d", Samples * frame.audio_channel_layout().num_channels);

						int audio_frame_size = ((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);
						m_Frames->FramesCreateFromMem(&props,
							(LONGLONG)(pNewData_Y_Reverse),
							&pMFrame,
							_bsProps
						);
						M_AV_PROPS avProps;
						pMFrame->FrameAVPropsGet(&avProps);
						int BitsPerSample = audio_frame_size / Samples / frame.audio_channel_layout().num_channels * 8;
						avProps.audProps.nBitsPerSample = BitsPerSample;

						pMFrame->FrameAVPropsSet(&avProps);

						LONG audio_size;
						LONGLONG audio_data;
						pMFrame->FrameAudioGetBytes(&audio_size, &audio_data);
						fast_memcpy((void*)audio_data, frame.audio_data().begin(), audio_frame_size);
						M_TIME t;
						pMFrame->FrameTimeGet(&t);
						t.rtStartTime = frame_time;
						t.rtEndTime = frame_time + frame_time_interval;
						frame_time += frame_time_interval;
						pMFrame->FrameTimeSet(&t);
					}

					M_AV_PROPS avProps;
					if (pMFrame != nullptr)
					{
						pMFrame->FrameAVPropsGet(&avProps);
						//avProps.vidProps.fccType = eMFCC_HDYC;
						//avProps.vidProps.nRowBytes = avProps.vidProps.nWidth * 2;
						//CComQIPtr<IMFrame> pFrame;
						//pMFrame->FrameConvert(&avProps.vidProps, &pFrame, nullptr);
						//m_Proxy->ReceiverPutFrame(L"ds_stream", pFrame);
						m_Proxy->ReceiverPutFrame(L"ds_stream", pMFrame);
					}
					graph_->set_value("pushframe-time", pushframe_timer.elapsed() * format_desc_.fps * 0.5);

					if (!IsPushStreamProcessStarted)
					{
						IsPushStreamProcessStarted = true;
						if (!wcscmp(L"", config_.name.c_str()))
						{
							CASPAR_LOG(info) << L"Invalid ip stream name.";
						}
						else
						{
							wchar_t cmd_line[50] = { L"cmd_line " };
							swprintf(cmd_line, L"cmd_line %s", config_.name.c_str());
							STARTUPINFO si = { sizeof(si) };
							PROCESS_INFORMATION pi;
							stream_event_handle = CreateEvent(nullptr, true, false, config_.name.c_str());

							bool h = CreateProcess(
								L"PushStreamBackGround/PushStreamBackGround.exe",
								cmd_line,
								NULL,
								NULL,
								false,
								NULL,
								NULL,
								NULL,
								&si,
								&pi
							);
							if (!h)
							{
								CASPAR_LOG(info) << L"Failed to create PushStreamBackGround.exe, please check the path.";
							}
							else
							{
								tbb::mutex::scoped_lock lock(stream_exe_mutex);
								stream_exes_handles.push_back(pi.hProcess);
							}
						}
					}
				}
				if (pNewData_Y_Reverse)
				{
					free(pNewData_Y_Reverse);
					pNewData_Y_Reverse = nullptr;
				}
 			}

  			void VideoFormatTransfer(core::video_format_desc Src, M_VID_PROPS& Des)
  			{
 				switch (Src.format)
 				{
 				case core::video_format::pal:
 					Des.eVideoFormat = eMVF_PAL;
 					break;
 
 				case core::video_format::ntsc:
 					Des.eVideoFormat = eMVF_NTSC;
 					break;
 
 				case core::video_format::x1080i5000:
 					Des.eVideoFormat = eMVF_HD1080_50i;
 					break;
 
 				case core::video_format::x2160p2500:
 					Des.eVideoFormat = eMVF_4K_UHD_25p;
 					break;
 				case core::video_format::x576p2500:
 					Des.eVideoFormat = eMVF_PAL/* Default */;
 					break;
 
 				case core::video_format::x720p2500:
 					Des.eVideoFormat = eMVF_HD720_50p/* Default */;
 					break;
 
 				case core::video_format::x720p5000:
 					Des.eVideoFormat = eMVF_HD720_50p/* Default */;
 					break;
 
 				case core::video_format::x720p2398:
 					Des.eVideoFormat = eMVF_HD720_50p/* Default */;
 					break;
 
 				case core::video_format::x720p2400:
 					Des.eVideoFormat = eMVF_HD720_50p/* Default */;
 					break;
 
 				case core::video_format::x720p2997:
 					Des.eVideoFormat = eMVF_HD720_50p/* Default */;
 					break;
 
 				case core::video_format::x720p5994:
 					Des.eVideoFormat = eMVF_HD720_5994p;
 					break;
 
 				case core::video_format::x720p3000:
 					Des.eVideoFormat = eMVF_HD720_50p/* Default */;
 					break;
 
 				case core::video_format::x720p6000:
 					Des.eVideoFormat = eMVF_HD720_60p;
 					break;
 
 				case core::video_format::x1080p2398:
 					Des.eVideoFormat = eMVF_HD1080_2398p;
 					break;
 
 				case core::video_format::x1080p2400:
 					Des.eVideoFormat = eMVF_HD1080_24p;
 					break;
 
 				case core::video_format::x1080i5994:
 					Des.eVideoFormat = eMVF_HD1080_5994i;
 					break;
 
 				case core::video_format::x1080i6000:
 					Des.eVideoFormat = eMVF_HD1080_60i;
 					break;
 
 				case core::video_format::x1080p2500:
 					Des.eVideoFormat = eMVF_HD1080_25p;
 					break;
 
 				case core::video_format::x1080p2997:
 					Des.eVideoFormat = eMVF_HD1080_2997p;
 					break;
 
 				case core::video_format::x1080p3000:
 					Des.eVideoFormat = eMVF_HD1080_30p;
 					break;
 
 				case core::video_format::x1080p5000:
 					Des.eVideoFormat = eMVF_HD1080_50p;
 					break;
 
 				case core::video_format::x1080p5994:
 					Des.eVideoFormat = eMVF_HD1080_5994p;
 					break;
 
 				case core::video_format::x1080p6000:
 					Des.eVideoFormat = eMVF_HD1080_60p;
 					break;
 
 				case core::video_format::x1556p2398:
 					Des.eVideoFormat = eMVF_2K_2398p/* Default */;
 					break;
 
 				case core::video_format::x1556p2400:
 					Des.eVideoFormat = eMVF_2K_24p/* Default */;
 					break;
 
 				case core::video_format::x1556p2500:
 					Des.eVideoFormat = eMVF_2K_25p/* Default */;
 					break;
 
 				case core::video_format::dci1080p2398:
 					Des.eVideoFormat = eMVF_HD1080_2398p/* Default */;
 					break;
 
 				case core::video_format::dci1080p2400:
 					Des.eVideoFormat = eMVF_HD1080_24p/* Default */;
 					break;
 
 				case core::video_format::dci1080p2500:
 					Des.eVideoFormat = eMVF_HD1080_25p/* Default */;
 					break;
 
 				case core::video_format::x2160p2398:
 					Des.eVideoFormat = eMVF_4K_UHD_2398p;
 					break;
 
 				case core::video_format::x2160p2400:
 					Des.eVideoFormat = eMVF_4K_UHD_24p;
 					break;
 
 				case core::video_format::x2160p2997:
 					Des.eVideoFormat = eMVF_4K_UHD_2997p;
 					break;
 
 				case core::video_format::x2160p3000:
 					Des.eVideoFormat = eMVF_4K_UHD_30p;
 					break;
 
 				case core::video_format::dci2160p2398:
 					Des.eVideoFormat = eMVF_4K_DCI_2398p;
 					break;
 
 				case core::video_format::dci2160p2400:
 					Des.eVideoFormat = eMVF_4K_DCI_24p;
 					break;
 
 				case core::video_format::dci2160p2500:
 					Des.eVideoFormat = eMVF_4K_DCI_25p;
 					break;
 
 				case core::video_format::invalid:
 					Des.eVideoFormat = eMVF_PAL/* Default */;
 					break;
 
 				case core::video_format::count:
 					Des.eVideoFormat = eMVF_PAL/* Default */;
 					break;
 
 				default:
 					break;
 				}
 
 				Des.dblRate = Src.fps;
 				Des.fccType = eMFCC_ARGB32;
 				Des.nWidth = Src.width;
 				Des.nHeight = Src.height;
 				Des.nAspectX = Src.square_width;
 				Des.nAspectY = Src.square_height;
 				Des.nRowBytes = Des.nWidth * 4;
 				Des.eScaleType = eMST_NoScale;
 				Des.e3DFormat = eM3D_None;
 				Des.eInterlace = (eMInterlace)Src.field_mode;//eMI_Field1First;
 			}
 
 			~dshow_consumer()
 			{
 				release();
 			}

 			void release()
 			{
				is_running_ = false;
 				frame_buffer_.try_push(core::const_frame::empty());
 				thread_.join();
				m_Object->ObjectVirtualSourceCreate(0, (BSTR)config_.name.c_str(), L"");
				m_Object.Release();
				SetEvent(stream_event_handle);
				CASPAR_LOG(info) << L" DirectShow virtual source successfully released.";
 			}

 			void init()
 			{
 			}

		};

		struct dshow_consumer_proxy : public core::frame_consumer
		{
 			core::monitor::subject			monitor_subject_;
 			const configuration				config_;
 			std::unique_ptr<dshow_consumer> consumer_;
// 			//core::interaction_sink*			sink_;
 		public:
			dshow_consumer_proxy(const configuration& config)
				:config_(config)
			{
			}

			~dshow_consumer_proxy()
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
				consumer_.reset(new dshow_consumer(config_, format_desc, channel_index));

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
				return consumer_ ? consumer_->print() : L"[dshow_consumer]";
			}

			std::wstring name() const override
			{
				return L"dshow";
			}

			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;
				info.add(L"type", L"dshow");
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
				return 5000;
			}

			int64_t presentation_frame_age_millis() const override
			{
				return 1;
			}
		};

		void describe_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"DShow Consumer.");
		}

		spl::shared_ptr<core::frame_consumer> create_consumer(const std::vector<std::wstring>& params, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || !boost::iequals(params.at(0), L"DIRECTSHOW"))
				return core::frame_consumer::empty();
			configuration config;
			if (contains_param(L"DS-SOURCENAME", params))
				config.name = get_param(L"DS-SOURCENAME", params);
			return spl::make_shared<dshow_consumer_proxy>(config);
		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			configuration config;
			config.name = ptree.get(L"ds-sourcename", config.name);

			return spl::make_shared<dshow_consumer_proxy>(config);
		}
}}




