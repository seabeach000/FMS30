//
// Created by zibj 2016/10/25.
//
#include "matrox_consumer.h"
#include "../mvsOutputTopology.h"
#include "../mvsCleanTopologies.h"
#include <assert.h>
#include <time.h>

#include <common/memcpy.h>

#include <common/future.h>
#include <common/except.h>
#include <common/param.h>
#include <common/os/general_protection_fault.h>

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

#include <MDefines.h>
#include <MPlatform.h>

#include <atlbase.h>
#include <atlstr.h>
 


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
	namespace matrox {

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
		struct SCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation sHwInfo;
			std::vector<TMvSmartPtr<IMvSdiVideoInputConnector> > vecpJConnectors;
		};
		struct configuration
		{
			std::wstring cardindex = L"0";
			std::wstring index = L"1";
			std::wstring ratio = L"16:9";
			bool						vanc_output_ = false;//config vanc
			bool						key_out = false;
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
		
		std::vector<HANDLE>		stream_exes_handles;
		bool					run_time_check_thread = false;
		tbb::mutex				stream_exe_mutex;

		struct matrox_consumer :boost::noncopyable
 		{
	 		const configuration									config_;
			const int											channel_index_;
			core::video_format_desc								format_desc_;
			TMvSmartPtr<CmvsOutputTopology>						pJOutputTopology;
  			tbb::atomic<bool>									is_running_;
  			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;
			boost::thread										thread_;
			AudioSampleCalc										m_audCalc;
			bool												vanc_output_;//config vanc
			bool												key_out_;
			const core::audio_channel_layout					in_channel_layout_;
			const core::audio_channel_layout					out_channel_layout_ = config_.get_adjusted_layout(in_channel_layout_);


		public:

			std::future<bool> send(core::const_frame frame)
			{
				frame_buffer_.try_push(frame);
				return make_ready_future(is_running_.load());
			}
			std::wstring print() const
			{
				return config_.index;
			}

			matrox_consumer(
				const configuration& config,
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& in_channel_layout,
				int channel_index)
				: channel_index_(channel_index)
				, config_(config)
				, format_desc_(format_desc)
				, in_channel_layout_(in_channel_layout)
				, vanc_output_(config.vanc_output_)//config vanc
				,key_out_(config.key_out)
			{
				pJOutputTopology = NULL;
				pJOutputTopology=init_matrox_consumer();
				if (pJOutputTopology)
				{
					pJOutputTopology->RegisterCallbackForWrite();
				}
				
				is_running_ = false;
				frame_buffer_.set_capacity(1);//
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
						boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						continue;
					}
					if (pJOutputTopology != NULL)
					{
						
						pJOutputTopology->_ProcessVanc(frame);
					}
				}
				CASPAR_LOG(error) << L" matrox consumer release";
 			}
 			~matrox_consumer()
 			{
 				release();
 			}

			TMvSmartPtr<CmvsOutputTopology> init_matrox_consumer()
			{
				TMvSmartPtr<CmvsOutputTopology> pJPlayback = NULL;
				CMvHResult oHr;

				/*oHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);*/

				TMvSmartPtr<IMvSystemConfiguration> pJSystemConfiguration;

				std::vector<SCardInfo> vecsCardConfigs;

				if (oHr.DidSucceed())
				{
					oHr = CoCreateInstance(CLSID_MvSystemConfiguration,
						NULL,
						CLSCTX_INPROC_SERVER,
						IID_IMvSystemConfiguration,
						(void**)&pJSystemConfiguration);
				}

				if (oHr.DidFail())
				{
					//CoUninitialize();
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(print() + L" nable to create the system configuration interface.")
						<< boost::errinfo_api_function("init_matrox_producer"));
					return pJPlayback;
				}

				// Get the cards enumerator
				_EnumerateCards(pJSystemConfiguration, vecsCardConfigs);

				if (vecsCardConfigs.size() == 0)
				{
					CASPAR_LOG(error) << L"matrox: No hardware detected!";
					oHr = MV_E_NO_HARDWARE_PROFILE_FOUND;
				}

				unsigned long ulNbOfProfiles = (unsigned long)vecsCardConfigs.size();
			
				uint32_t ui8HwIndex = boost::lexical_cast<int>(config_.cardindex);

				if (ui8HwIndex >= ulNbOfProfiles)
				{
					CASPAR_LOG(error) << L"Invalid hardware index! check matrox config";
					return pJPlayback;
				}
				// Clean up previous topology if clean switch is specified.
				
				//清除占用
				CmvsCleanTopologies *pJanitor = NULL;
				pJanitor = new CmvsCleanTopologies(pJSystemConfiguration);
				std::wstring strTopologyName = L"MatroxConsumer" + config_.index;
				pJanitor->Clean(u8(strTopologyName).c_str());

				// Note that topologies are permanent unless you explicitly delete them
				delete pJanitor;

				// Print current topologies.
				
				CmvsBaseTopology *pBaseTopology = NULL;
				pBaseTopology = new CmvsBaseTopology(pJSystemConfiguration, vecsCardConfigs[ui8HwIndex].pJCardConfig, NULL);
				pBaseTopology->LogTopologies();
				delete pBaseTopology;
				
				SMvResolutionInfo sResolution;
				GetResolution(&sResolution);
				pJPlayback = new CmvsOutputTopology(pJSystemConfiguration,
					vecsCardConfigs[ui8HwIndex].pJCardConfig,
					&sResolution, (int)boost::lexical_cast<int>(config_.index),
					format_desc_.framerate.numerator() / format_desc_.framerate.denominator(),
					in_channel_layout_.num_channels,
					out_channel_layout_.num_channels,
					format_desc_.audio_sample_rate,
					config_.vanc_output_
				);
				oHr = pJPlayback->BuildTopology(u8(strTopologyName).c_str(), boost::lexical_cast<int>(config_.index),key_out_);
				
				if (oHr.DidSucceed())
				{
					boost::this_thread::sleep_for(boost::chrono::milliseconds(800));
				}
				else
				{
					pJPlayback->LogError(oHr, "BuildTopology() failed");
					pJPlayback = NULL;
				}
				return pJPlayback;

			}
			void GetResolution(SMvResolutionInfo *out_pResInfo)
			{
				out_pResInfo->size = sizeof(*out_pResInfo);
				std::string szResolution;
				switch (format_desc_.format)
				{
				case caspar::core::video_format::pal:
					szResolution = "PAL";
					break;
				case caspar::core::video_format::ntsc:
					szResolution = "NTSC";
					break;
				case caspar::core::video_format::x1080i5000:
					szResolution = "1920x1080i@25";
					break;
				case caspar::core::video_format::x1080p2500:
					szResolution = "1920x1080p@25";
					break;
				case caspar::core::video_format::x2160p2500:
					szResolution = "3840x2160p@25";//单路不支持
					break;
				case caspar::core::video_format::x576p2500:
					szResolution = "720x576p@25";//不支持
					break;
				case caspar::core::video_format::x720p2500:
					szResolution = "1280x720p@25";
					break;
				default:
					break;
				}
				if (format_desc_.format != core::video_format::invalid)
				{
					if (format_desc_.format == core::video_format::ntsc)
					{
						out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
						out_pResInfo->eFrameRate = keMvFrameRate30M;
						//out_pResInfo->eFrameRate = keMvFrameRate25;
						out_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
						out_pResInfo->ulComponentBitCount = 8;
						out_pResInfo->ulWidth = 720;
						out_pResInfo->ulHeight = 486;
						return;
					}
					else if (format_desc_.format == core::video_format::pal)
					{
						out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
						out_pResInfo->eFrameRate = keMvFrameRate25;
						out_pResInfo->eScanMode = keMvScanModeFirstFieldTop;
						out_pResInfo->ulComponentBitCount = 8;
						out_pResInfo->ulWidth = 720;
						out_pResInfo->ulHeight = 576;
						return;
					}
					else
					{
						size_t posX = szResolution.find("x");
						size_t posAt = szResolution.find("@");
						if (posX == std::string::npos)
						{
							posX = szResolution.find("X");
						}

						if (posX != std::string::npos && posAt != std::string::npos)
						{
							bool bSucceeded = true;
							std::string szSubStr = szResolution.substr(0, posX + 1); // Width
							out_pResInfo->ulWidth = atoi(szSubStr.c_str());
							szSubStr = szResolution.substr(posX + 1, (posAt - 1) - (posX + 1)); // Height
							out_pResInfo->ulHeight = atoi(szSubStr.c_str());

							szSubStr = szResolution.substr(posAt - 1, 1); // i or p
							if (szSubStr == "i" || szSubStr == "I")
							{
								if (out_pResInfo->ulHeight == 486)
								{
									out_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
								}
								else
								{
									out_pResInfo->eScanMode = keMvScanModeFirstFieldTop;
								}
							}
							else if (szSubStr == "p" || szSubStr == "P")
							{
								out_pResInfo->eScanMode = keMvScanModeProgressive;
							}
							else
							{

								bSucceeded = false;
							}

							szSubStr = szResolution.substr(posAt + 1, std::string::npos);
							if (szSubStr == "24")
							{
								out_pResInfo->eFrameRate = keMvFrameRate24;
							}
							else if (szSubStr == "24M" || szSubStr == "23.98" || szSubStr == "24m")
							{
								out_pResInfo->eFrameRate = keMvFrameRate24M;
							}
							else if (szSubStr == "25")
							{
								out_pResInfo->eFrameRate = keMvFrameRate25;
							}
							else if (szSubStr == "30")
							{
								out_pResInfo->eFrameRate = keMvFrameRate30;
							}
							else if (szSubStr == "30M" || szSubStr == "29.97" || szSubStr == "30m")
							{
								out_pResInfo->eFrameRate = keMvFrameRate30M;
							}
							else if (szSubStr == "50")
							{
								out_pResInfo->eFrameRate = keMvFrameRate50;
							}
							else if (szSubStr == "60")
							{
								out_pResInfo->eFrameRate = keMvFrameRate60;
							}
							else if (szSubStr == "60M" || szSubStr == "59.94" || szSubStr == "60m")
							{
								out_pResInfo->eFrameRate = keMvFrameRate60M;
							}
							else
							{
								bSucceeded = false;

							}

							out_pResInfo->ulComponentBitCount = 8;
							out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
							if (config_.ratio == L"16:9")
							{
								out_pResInfo->eAspectRatio = keMvAspectRatio_16_9;
							}
							if (bSucceeded)
							{
								return;
							}
						}
					}
				}

				out_pResInfo->eAspectRatio = keMvAspectRatio_4_3;
				out_pResInfo->eFrameRate = keMvFrameRate30M;
				out_pResInfo->eScanMode = keMvScanModeSecondFieldTop;
				out_pResInfo->ulComponentBitCount = 8;
				out_pResInfo->ulWidth = 720;
				out_pResInfo->ulHeight = 486;
				CASPAR_LOG(error) << L"Unspecified or invalid resolution format.  Defaulting to NTSC. Use -r to set resolution (Ex: -r=NTSC or -r=1920x1080i@29.97)\n";
			}
			// ----------------------------------------------------------------------------
			HRESULT _ValidateAndDisplayCardTemperature(SCardInfo & in_krsCardInfo)
			{
				CMvHResult oHr;

				// We only get the temperature sensor info once but it is a good practice
				// to register an IMvTemperatureNotificationCallback through the IMvTemperatureNotification
				// to be notified when there is an overheat or a fan malfunction.

				// X.mio2+ has three temperature sensors.
				SMvTemperatureInformation  asInfo[3] =
				{
					{ keTemperatureSensorIDInvalid, 0.0, 0.0, 0.0, keMvFanStatusNotAvailable },
					{ keTemperatureSensorIDInvalid, 0.0, 0.0, 0.0, keMvFanStatusNotAvailable },
					{ keTemperatureSensorIDInvalid, 0.0, 0.0, 0.0, keMvFanStatusNotAvailable }
				};

				in_krsCardInfo.pJCardConfig->GetTemperatureSensorInfo(asInfo, 3);

				for (int i = 0; i < 3; ++i)
				{
					if (asInfo[i].eTemperatureID != keTemperatureSensorIDInvalid)
					{
						if (asInfo[i].dTemperature >= asInfo[i].dTemperatureErrorThreshold)
						{
							CASPAR_LOG(warning) << L"matrox:WARNING: OVERHEAT!";
							oHr = MV_E_FAIL;
						}

						if (asInfo[i].eFanStatus == keMvFanStatusTooSlowOrStopped)
						{
							CASPAR_LOG(warning) << L"Fan: ERROR: Too slow or stopped!";
							oHr = MV_E_FAIL;
						}
						else if (asInfo[i].eFanStatus == keMvFanStatusOk)
						{
							//printf("Fan: Ok.\n");
						}
						// else { there is no fan so no fan message to output. }
					}
				}
				return oHr;
			}


			// ----------------------------------------------------------------------------
			void _EnumerateCards(IMvSystemConfiguration * in_pISysConfig,
				std::vector<SCardInfo> & out_rvecsCardConfigs)
			{
				CMvHResult oHr;
				TMvSmartPtr<IMvSystemConfigurationCardEnumerator> pJSystemConfigurationCardEnumerator;

				oHr = in_pISysConfig->CreateCardEnumerator(&pJSystemConfigurationCardEnumerator);

				// Enumerate all cards
				if (oHr.DidSucceed())
				{
					TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
					oHr.AssignNoAssert(pJSystemConfigurationCardEnumerator->Next(&pJCardConfig));

					while (oHr.DidSucceed())
					{
						// Get card information
						SCardInfo sCardInfo;
						sCardInfo.sHwInfo.size = sizeof(sCardInfo.sHwInfo);
						sCardInfo.pJCardConfig = pJCardConfig;
						sCardInfo.sHwInfo.sConnectorsDescription.size = sizeof(sCardInfo.sHwInfo.sConnectorsDescription);
						oHr = sCardInfo.pJCardConfig->GetCardInformation(&sCardInfo.sHwInfo, 0);

						if (oHr.DidSucceed())
						{
							//Fill the connectors info for this card
							TMvSmartPtr<IMvSdiVideoInputConnectorsEnumerator> pJSdiVideoInputConnectorsEnumerator;

							oHr = sCardInfo.pJCardConfig->CreateSdiVideoInputConnectorsEnumerator(&pJSdiVideoInputConnectorsEnumerator);

							// Enumerate all connectors
							if (oHr.DidSucceed())
							{
								TMvSmartPtr<IMvSdiVideoInputConnector> pJConnector;

								// Get first connector
								oHr.AssignNoAssert(pJSdiVideoInputConnectorsEnumerator->Next(&pJConnector));

								while (oHr.DidSucceed())
								{
									sCardInfo.vecpJConnectors.push_back(pJConnector);

									// Next card
									pJConnector = NULL;
									oHr.AssignNoAssert(pJSdiVideoInputConnectorsEnumerator->Next(&pJConnector));
								}

								// Ignore the error from the NEXT of the enumerator.
								oHr = MV_NOERROR;
							}
						}

						if (oHr.DidSucceed())
						{
							out_rvecsCardConfigs.push_back(sCardInfo);
							oHr = _ValidateAndDisplayCardTemperature(sCardInfo);
							if (oHr.DidFail())
							{
								//CoUninitialize();
								CASPAR_LOG(info) << L"_EnumerateCards error";
								return;
							}
						}

						// Next card
						pJCardConfig = NULL;
						oHr.AssignNoAssert(pJSystemConfigurationCardEnumerator->Next(&pJCardConfig));
					}
				}
			}

			// ----------------------------------------------------------------------------
			bool _IsCardUHDWithBuffers(IMvCardConfiguration * in_pICardConfiguration)
			{
				// Check if this is an X.mio2plus or a DSX LE3 card
				bool bOldCard = false;
				SMvGeneralHardwareInformation sCardInfo = { sizeof(sCardInfo) };
				sCardInfo.sConnectorsDescription.size = sizeof(sCardInfo.sConnectorsDescription);

				CMvHResult oHr = in_pICardConfiguration->GetCardInformation(&sCardInfo, 0);
				if (oHr.DidFail())
				{
					CASPAR_LOG(error) << L"Error: Unable to get the matrox card information";
				}

				switch (sCardInfo.eHardwareSerieDetected)
				{
				case kEMvHardwareSerieDSXmio2plus5000:
				case kEMvHardwareSerieDSXmio2plus6000:
				case kEMvHardwareSerieDSXmio2plus8000:
				case kEMvHardwareSerieDSXmio2plus8500:
				case kEMvHardwareSerieDSXLE3_100:
				case kEMvHardwareSerieDSXLE3_110:
				case kEMvHardwareSerieDSXLE3_200:
				case kEMvHardwareSerieDSXLE3_500:
				case kEMvHardwareSerieDSXLE3_550:
					bOldCard = true;
					break;

				default:
					break;
				}

				return bOldCard;
			}

			// ----------------------------------------------------------------------------
 			void release()
 			{
				//CoUninitialize();
				
				if (pJOutputTopology)
				{
					pJOutputTopology->UnregisterCallback();
					pJOutputTopology = NULL;
				}
				is_running_ = false;
 				frame_buffer_.try_push(core::const_frame::empty());
 				thread_.join();
				CASPAR_LOG(info) << L" NID virtual source successfully released.";
 			}

		};

		struct matrox_consumer_proxy : public core::frame_consumer
		{
 			core::monitor::subject			monitor_subject_;
 			const configuration				config_;
 			std::unique_ptr<matrox_consumer> consumer_;
 		public:
			matrox_consumer_proxy(const configuration& config)
				:config_(config)
			{
			}

			~matrox_consumer_proxy()
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
			void initialize(const core::video_format_desc& format_desc, const core::audio_channel_layout& channel_layout, int channel_index) override
			{
				consumer_.reset();
				consumer_.reset(new matrox_consumer(config_, format_desc, channel_layout, channel_index));

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
				return 7500+ boost::lexical_cast<int>(config_.index)+ boost::lexical_cast<int>(config_.cardindex)*10;
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
			if (params.size() < 1 || !boost::iequals(params.at(0), L"matrox"))
				return core::frame_consumer::empty();
			configuration config;
			if (contains_param(L"device", params))
				config.cardindex = get_param(L"device", params);
			if (contains_param(L"index", params))
				config.index = get_param(L"index", params);
			if (contains_param(L"ratio", params))
				config.ratio = get_param(L"ratio", params);
			if (contains_param(L"vanc-output", params))
				config.vanc_output_ = boost::lexical_cast<int>(get_param(L"vanc-output", params))==1?true:false;
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
			return spl::make_shared<matrox_consumer_proxy>(config);
		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
 			configuration config;
			config.cardindex = ptree.get(L"device", config.cardindex);
			config.ratio = ptree.get(L"ratio", config.ratio);
			config.index = ptree.get(L"index", config.index);
			config.vanc_output_ = ptree.get(L"vanc-output", config.vanc_output_);//config vanc
			config.key_out = ptree.get(L"key", config.key_out);
			auto channel_layout = ptree.get_optional<std::wstring>(L"channel-layout");


			if (channel_layout)
			{
				CASPAR_SCOPED_CONTEXT_MSG("/channel-layout")

					auto found_layout = core::audio_channel_layout_repository::get_default()->get_layout(*channel_layout);

				if (!found_layout)
					CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"Channel layout " + *channel_layout + L" not found."));

				config.out_channel_layout = *found_layout;
			}
			return spl::make_shared<matrox_consumer_proxy>(config);
		}
}}




