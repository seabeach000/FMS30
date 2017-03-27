#pragma once
#include "mvsInputTopology.h"
#include "mvsCleanTopologies.h"
#include "matrox_interface.h"
#include <mvIODefinitions.h>
#include "SDIInConnectorStatusCallback.h"
#include <common/log.h>
#include <vector>

#include <tbb/concurrent_queue.h>

#include <boost/lexical_cast.hpp>


namespace caspar {
	namespace matrox {
		struct SCardInfo
		{
			TMvSmartPtr<IMvCardConfiguration> pJCardConfig;
			SMvGeneralHardwareInformation sHwInfo;
			std::vector<TMvSmartPtr<IMvSdiVideoInputConnector> > vecpJConnectors;
		};

		struct matrox_interface::impl
		{
			TMvSmartPtr<CmvsInputTopology>					pJInputTopology;
			unsigned int									in_channel_;
			unsigned int									hardwareindex_;//板卡索引
			unsigned int									connector_;//通道索引
			std::wstring									ratio_;
			core::video_format								format_;
			bool											is_running;
			TMvSmartPtr<IMvSystemConfiguration>				pJSystemConfiguration;
			TMvSmartPtr<CStatusCallbackSdiIn>				m_pJSDIInputConnectorCallback;
			TMvSmartPtr<IMvVideoConnectorNotification>		m_pJSDIInputConnectorNotification;
			impl(int hardwareindex,
				int in_channel,
				int conrector,
				std::wstring ratio_s,
				core::video_format format)
				: hardwareindex_(hardwareindex)
				, in_channel_(in_channel)
				, connector_(conrector)
				, ratio_(ratio_s)
				,format_(format)
			{
				CASPAR_LOG(info) << L" matrox producer creat.";
				is_running = false;

				pJInputTopology = init_matrox_producer();
				if (pJInputTopology)
				{
					is_running = true;
				}
			}
			~impl()
			{
				CmvsCleanTopologies *pJanitor = NULL;
				pJanitor = new CmvsCleanTopologies(pJSystemConfiguration);
				std::wstring strTopologyName = L"MatroxProducer" + boost::lexical_cast<std::wstring>(connector_);
				pJanitor->Clean(u8(strTopologyName).c_str());
				delete pJanitor;
				//CoUninitialize();
			}

			TMvSmartPtr<CmvsInputTopology> init_matrox_producer()
			{
				TMvSmartPtr<CmvsInputTopology> pcaptrue = NULL;
				CMvHResult oHr;
				//oHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
				std::vector<SCardInfo> vecsCardConfigs;

// 				if (oHr.DidSucceed())
// 				{
					oHr = CoCreateInstance(CLSID_MvSystemConfiguration,
						NULL,
						CLSCTX_INPROC_SERVER,
						IID_IMvSystemConfiguration,
						(void**)&pJSystemConfiguration);
				//}

				if (oHr.DidFail())
				{
					//CoUninitialize();
					pcaptrue = NULL;
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(L"matrox unable to create the system configuration interface.")
						<< boost::errinfo_api_function("init_matrox_producer"));
					
					return pcaptrue;
				}

				// Get the cards enumerator
				_EnumerateCards(pJSystemConfiguration, vecsCardConfigs);

				if (vecsCardConfigs.size() == 0)
				{
					printf("No hardware detected!\n\n");
					oHr = MV_E_NO_HARDWARE_PROFILE_FOUND;
				}
				
				unsigned long ulNbOfProfiles = (unsigned long)vecsCardConfigs.size();

				if (hardwareindex_ >= ulNbOfProfiles)
				{
					
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(L"hardware index  error")
						<< boost::errinfo_api_function("init_matrox_producer"));
				}

				
				CmvsCleanTopologies *pJanitor = NULL;
				pJanitor = new CmvsCleanTopologies(pJSystemConfiguration);
				std::wstring strTopologyName = L"MatroxProducer" + boost::lexical_cast<std::wstring>(connector_);
				pJanitor->Clean(u8(strTopologyName).c_str());
				delete pJanitor;

				/*CmvsBaseTopology *pBaseTopology = NULL;
				pBaseTopology = new CmvsBaseTopology(pJSystemConfiguration, vecsCardConfigs[hardwareindex_].pJCardConfig, NULL);
				pBaseTopology->LogTopologies();
				delete pBaseTopology;
				boost::this_thread::sleep_for(boost::chrono::milliseconds(800));*/
					
				//自适应分辨率回调设置
				m_pJSDIInputConnectorCallback = new CStatusCallbackSdiIn(vecsCardConfigs[hardwareindex_].vecpJConnectors[connector_], format_);
				if (m_pJSDIInputConnectorCallback)
				{
					oHr = vecsCardConfigs[hardwareindex_].vecpJConnectors[connector_]->GetVideoConnectorNotification(&m_pJSDIInputConnectorNotification);

					if (oHr.DidSucceed())
					{
						oHr = m_pJSDIInputConnectorNotification->RegisterCallbackForNotification(m_pJSDIInputConnectorCallback);
					}
				}
				
				SMvResolutionInfo sResolution;
				GetResolution(&sResolution);

				pcaptrue = new CmvsInputTopology(pJSystemConfiguration,
					vecsCardConfigs[hardwareindex_].pJCardConfig,
					&sResolution, connector_);
				oHr = pcaptrue->BuildTopology(u8(strTopologyName).c_str(), connector_, in_channel_);
				if (oHr.DidSucceed())
				{
					CASPAR_LOG(info) << L"matrox  BuildTopology success";
					boost::this_thread::sleep_for(boost::chrono::milliseconds(800));
				}
				else
				{
					pcaptrue->LogError(oHr, "matrox  BuildTopology failed");

					//CoUninitialize();
					pcaptrue = NULL;
					CASPAR_THROW_EXCEPTION(caspar_exception()
						<< msg_info(L"BuildTopology failed")
						<< boost::errinfo_api_function("init_matrox_producer"));
				}
				return pcaptrue;

			}
			void GetResolution(SMvResolutionInfo *out_pResInfo)
			{
				out_pResInfo->size = sizeof(*out_pResInfo);
				std::string szResolution;
				switch (format_)
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
				if (format_ != core::video_format::invalid)
				{
					if (format_ == core::video_format::ntsc)
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
					else if (format_ == core::video_format::pal)
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
							if (ratio_ == L"16:9")
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
								return;
							}
						}

						// Next card
						pJCardConfig = NULL;
						oHr.AssignNoAssert(pJSystemConfigurationCardEnumerator->Next(&pJCardConfig));
					}
				}
			}

			//-----------------------------------------------------------------------------
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
			bool get_frame(MatroxFrame& frame)
			{
				if (m_pJSDIInputConnectorCallback->change())
				{
					
					SMvVideoConnectorStatus io_rsVideoStatus;
					SMvAudioPairStatus out_asAudioStatus[16];
					m_pJSDIInputConnectorCallback->GetStatus(io_rsVideoStatus, out_asAudioStatus);
					uint32_t  ulWidth = io_rsVideoStatus.sDetectedResolution.ulWidth;
					uint32_t  ulHeight = io_rsVideoStatus.sDetectedResolution.ulHeight;
					switch (ulWidth)
					{
					case 720:
					{
						if (ulHeight==576)
						{
							if (io_rsVideoStatus.sDetectedResolution.eScanMode == keMvScanModeProgressive)
							{
								format_ = core::video_format::x576p2500;
							}
							else
							{
								format_ = core::video_format::pal;
							}
						}
						if (ulHeight == 480)
						{
							format_ = core::video_format::ntsc;
						}
					}
					break;
					case 1920:
					{
						if (io_rsVideoStatus.sDetectedResolution.eScanMode == keMvScanModeFirstFieldTop || io_rsVideoStatus.sDetectedResolution.eScanMode == keMvScanModeSecondFieldTop)
						{
							format_ = core::video_format::x1080i5000;
						}
						else
						{
							format_ = core::video_format::x1080p2500;
						}
					}
					break;
					case 3840:
					{
						format_ = core::video_format::x2160p2500;	
					}
					break;
					case 1280:
					{
						format_ = core::video_format::x720p2500;
					}
					break;
					default:
						format_ = core::video_format::invalid;
						break;
					}
					is_running = false;
					//这个位置一定不能用线程执行，会崩溃，原因是有来到这个函数
					restart();
					return false;
				}
				if (!is_running)
					return false;
				return pJInputTopology->get_frame(frame);
			}
			void restart()
			{
				CMvHResult oHr = m_pJSDIInputConnectorNotification->RegisterCallbackForNotification(m_pJSDIInputConnectorCallback);
				m_pJSDIInputConnectorNotification = NULL;
				m_pJSDIInputConnectorNotification = NULL;
				pJInputTopology = NULL;//
				//CoUninitialize();
				
				boost::this_thread::sleep_for(boost::chrono::milliseconds(800));
				pJInputTopology = init_matrox_producer();
				if (pJInputTopology)
				{
					is_running = true;
				}
			}
		};
			
		
		matrox_interface::matrox_interface(int hardwareindex,int audiochannel,int conrector,std::wstring ratio_s,core::video_format format)
			:impl_(new impl(hardwareindex, audiochannel, conrector, ratio_s, format))
		{
		}
		
		bool matrox_interface::get_frame(MatroxFrame & frame) {return impl_->get_frame(frame);}
	}
}