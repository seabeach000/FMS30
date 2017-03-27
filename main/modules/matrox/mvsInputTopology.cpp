/*

(c) Copyright Matrox Electronic Systems Ltd., 2013. All rights reserved. 

This code and information is provided "as is" without warranty of any kind,
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/

#include "mvsInputTopology.h"


#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <common/memcpy.h>
#include <common/utf.h>
#include <common/cache_aligned_vector.h>
#include <common/memshfl.h>
// 
#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>
#include <boost/lexical_cast.hpp>
#include <libswscale/swscale.h>
#include <libavutil/channel_layout.h>
#ifdef LINUX_PLATFORM
#include <inttypes.h>
#endif

#include "MatroxDSXsdkGuids.h"
#include "mvHelperFunctions.h"

#define __STDC_FORMAT_MACROS
#define  _Max_QUE 1
namespace caspar {
	namespace matrox {
		// ----------------------------------------------------------------------------
		CmvsInputTopology::CmvsInputTopology(IMvSystemConfiguration *in_pISystemConfiguration,
			IMvCardConfiguration* in_pICardConfiguration,
			SMvResolutionInfo *in_pResolutionInfo,
			uint8_t connector)
			: CmvsBaseTopology(in_pISystemConfiguration, in_pICardConfiguration, in_pResolutionInfo)
			, CMvUnknown((L"CmvsInputTopology" + boost::lexical_cast<std::wstring>(connector)).c_str(), NULL)
			, m_ulAudioSampleSize(0)
		{
			noStartpush = true;
			is_running_ = false;
			BuffersQueue.set_capacity(_Max_QUE);
			m_oOutputBuffersQueue.set_capacity(1000);
		}


		// ----------------------------------------------------------------------------
		CmvsInputTopology::~CmvsInputTopology()
		{
			try
			{
				m_pJHostNode->UnregisterReadCallback(this);
				if (BuffersQueue.size())
				{
					SMvNodeNotificationCallbackParameters lpT;
					BuffersQueue.pop(lpT);
					
					if (lpT.pVideoBuffer)
						free(lpT.pVideoBuffer);
					if (lpT.pAudioBuffer)
						free(lpT.pAudioBuffer);
				}
				while (m_oOutputBuffersQueue.size())
				{
					SMvNodeNotificationCallbackParameters lpT;
					BuffersQueue.pop(lpT);
					if (lpT.pVideoBuffer)
						free(lpT.pVideoBuffer);
					if (lpT.pAudioBuffer)
						free(lpT.pAudioBuffer);
				}
				m_pJTopology->DestroyAllComponents();
				m_pJTopology->DestroyTopology();
			}
			catch (...)
			{
			}
			
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsInputTopology::BuildTopology(const char *in_kszName, uint8_t in_ui8InputIndex,uint8_t channel_number)
		{
			CMvHResult oHr;

			TMvSmartPtr<IMvSdiVideoInputConnector> pJSdiVideoInputConnector[4] = { NULL, NULL, NULL, NULL };
			uint32_t ui32VideoConnectorCount = 0;

			// 4K resolution?
			if (m_sResolution.ulWidth >= 3840)
			{
				ui32VideoConnectorCount = 4;
				for (uint8_t i = 0; i < 4; i++)
				{
					oHr = _GetVideoInputConnector(&pJSdiVideoInputConnector[i], in_ui8InputIndex + i);
					if (oHr.DidFail())
					{
						return oHr;
					}
				}
			}
			else
			{
				// SD and HD
				ui32VideoConnectorCount = 1;
				oHr = _GetVideoInputConnector(&pJSdiVideoInputConnector[0], in_ui8InputIndex);
				if (oHr.DidFail())
				{
					return oHr;
				}
			}

			// Setup a genlock clock to match the clock used at the output. If the same clock is not used between the input 
			// and output, the timestamp computation for the output must be compensated because of the drift between 
			// the input and output clock. For this sample, just use the same clock.
			SetupClock(NULL);

			oHr = _CreateTopology(in_kszName);
			if (oHr.DidFail())
			{
				return oHr;
			}
			SMvNodeSettings sNodeSettings;
			SMvNodeSettingsVideo sVideoSettings;
			SMvNodeSettingsAudio sAudioSettings;
			SMvNodeSettingsVanc  sVancSettings;


			std::wstring sname= L"InputCardNode" + boost::lexical_cast<std::wstring>((in_ui8InputIndex));
			_InitNodeSettings(u8(sname).c_str(), keMvSurfaceFormatYUYV422, &sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings);
			switch (channel_number)
			{
			case 1:
				sAudioSettings.eChannelType = keChannelTypeMono;
				break;
			case 2:
				sAudioSettings.eChannelType = keChannelTypeStereo;
				break;
			case 8:
				sAudioSettings.eChannelType = keChannelType8Tracks;
				break;
			case 16:
				sAudioSettings.eChannelType = keChannelType16Tracks;
				break;
			default:
				break;
			}
			oHr = m_pJTopology->CreateCardNode(sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings, NULL, &m_pJCardNode);
			if (oHr.DidFail())
			{
				return oHr;
			}
			
			// Get the embedded SDI audio pairs.
			uint32_t ui32AudioConnectorCount = 16;
			IMvAudioInputConnector * apIAudioInputConnectors[16];
			if (oHr.DidSucceed())
			{
				oHr = _GetEmbeddedAudioInputConnectors(pJSdiVideoInputConnector[0], apIAudioInputConnectors, ui32AudioConnectorCount);
			}

			// Create the input stream.
			IMvVideoInputConnector* apIVideoConnector[4] = { pJSdiVideoInputConnector[0],
															 pJSdiVideoInputConnector[1],
															 pJSdiVideoInputConnector[2],
															 pJSdiVideoInputConnector[3] };
			SMvInputStreamSettings sInStreamSettings;
			_InitInputStreamSettings(sInStreamSettings);
			sname = L"InputStream" + boost::lexical_cast<std::wstring>((int)in_ui8InputIndex);
			oHr = m_pJTopology->CreateInputStream(u8(sname).c_str(),
				apIVideoConnector, ui32VideoConnectorCount,
				apIAudioInputConnectors, ui32AudioConnectorCount,
				m_pJCardNode,
				m_sResolution,
				sInStreamSettings,
				&m_pJInputStream);

			if (oHr.DidFail())
			{
				return oHr;
			}

			// For simplicity in the sample code, introduce a small delay to let genlock and input signals
			// stabilize before starting capture (instead of observing genlock and input status through RegisterCallbackForNotification(...)).  
			boost::this_thread::sleep_for(boost::chrono::milliseconds(200));

			// Verify input status.
			SMvVideoConnectorStatus sConnectorStatus = { sizeof(sConnectorStatus) };
			sConnectorStatus.sDetectedResolution.size = sizeof(sConnectorStatus.sDetectedResolution);

			oHr = pJSdiVideoInputConnector[0]->GetVideoConnectorStatus(sConnectorStatus);
			if (!sConnectorStatus.bIsVideoPresent)
			{
				CASPAR_LOG(error)<<L"No video input detected!";
				return MV_E_VIDEO_INPUT_ABSENT;
			}

			// Verify input resolution.
			// Verify input resolution.
			SMvResolutionInfo sInputResolution = m_sResolution;
			if (ui32VideoConnectorCount == 4)
			{
				sInputResolution.ulWidth /= 2;
				sInputResolution.ulHeight /= 2;
			}

			sConnectorStatus.sDetectedResolution.size = sizeof(sConnectorStatus.sDetectedResolution);
			sConnectorStatus.sDetectedResolution.ulComponentBitCount = m_sResolution.ulComponentBitCount; // Don't care about BPC

			// Create the host node.

			sname = L"InputHostNode" + boost::lexical_cast<std::wstring>((in_ui8InputIndex));
			oHr = m_pJTopology->CreateHostNode(sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings, &m_pJHostNode);
			if (oHr.DidFail())
			{
				return oHr;
			}

			// Create the transfer stream.
			SMvTransferStreamSettings sTransferSettings = { sizeof(SMvTransferStreamSettings), 0 };
			sname = L"TransferStreaminput" + boost::lexical_cast<std::wstring>((in_ui8InputIndex));
			oHr = m_pJTopology->CreateTransferStream(u8(sname).c_str(), m_pJCardNode, m_pJHostNode, keMvTransferDirectionCardToHost, sTransferSettings, &m_pJTransferStream);
			if (oHr.DidFail())
			{
				return oHr;
			}
			oHr = m_pJHostNode->QueryInterface(IID_IMvVancDataPackets, (void**)&m_pJVancDataPackets);
			if (!oHr.DidSucceed())
			{
				LogError(oHr, "m_pJHostNode QueryInterface failed");
				return oHr;
			}
			oHr = m_pJVancDataPackets->EnableVancDataPackets();
			if (!oHr.DidSucceed())
			{
				LogError(oHr, "m_pJHostNode QueryInterface failed");
				return oHr;
			}
			
			oHr = m_pJHostNode->RegisterCallbackForRead(this);

			// Release audio input connectors.
			//这段代码什么意思？
			while (ui32AudioConnectorCount)
			{
				apIAudioInputConnectors[ui32AudioConnectorCount - 1]->Release();
				ui32AudioConnectorCount--;
			}
			return oHr;
		}
		HRESULT CmvsInputTopology::NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
		{
			CMvHResult oHr = MV_NOERROR;
			SMvNodeNotificationCallbackParameters topdata;
			if (_IsFieldBased(m_sResolution))
			{
				
				if (MvGetSampleForNanoTime(in_krsNotificationParameters.ui64Timestamp, m_sResolution) % 2 == 1)//偶场
				{
					//m_oCriticalSection.Wait();
					 
					if (BuffersQueue.size()==0)
					{
						return oHr;
					}
					BuffersQueue.pop(topdata);
					m_oOutputBuffersQueue.push(topdata);

					SMvNodeNotificationCallbackParameters lpt= in_krsNotificationParameters;
				
 					lpt.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
 					lpt.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);
					fast_memcpy(lpt.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					fast_memcpy(lpt.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
					m_oOutputBuffersQueue.push(lpt);
					//m_oCriticalSection.Release();
					
				}
				else
				{
					topdata=in_krsNotificationParameters;
					
					topdata.pVideoBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					topdata.pAudioBuffer = (uint8_t*)malloc(in_krsNotificationParameters.ui32AudioSize);
					
					fast_memcpy(topdata.pVideoBuffer, in_krsNotificationParameters.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					fast_memcpy(topdata.pAudioBuffer, in_krsNotificationParameters.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
					BuffersQueue.push(topdata);
				}
			}

			// Get the vanc packets from the host node.
			/*uint32_t ui32VancPacketCount = 8;
			SMvVancPacket asVancPacket[8];
			
			//vanc
			if (_IsFieldBased(m_sResolution))
			{
			oHr = m_pJVancDataPackets->GetVancPacketsField(in_krsNotificationParameters.ui64Timestamp, asVancPacket, ui32VancPacketCount);
			}
			else
			{
			oHr = m_pJVancDataPackets->GetVancPacketsFrame(in_krsNotificationParameters.ui64Timestamp, asVancPacket, ui32VancPacketCount);
			}

			//_ProcessVanc(asVancPacket, ui32VancPacketCount);*/
		
			return oHr;
		}
		bool CmvsInputTopology::get_frame(MatroxFrame & frame)
		{
			SMvNodeNotificationCallbackParameters lpT;
			SMvNodeNotificationCallbackParameters lpB;
			if (_IsFieldBased(m_sResolution))
			{
				//m_oCriticalSection.Wait();
				if (m_oOutputBuffersQueue.size() < 2)
				{
					//m_oCriticalSection.Release();
					return false;
				}
				//m_oCriticalSection.Release();
				//m_oCriticalSection.Wait();
				//lpT = m_oOutputBuffersQueue.front();
				m_oOutputBuffersQueue.pop(lpT);
			//	m_oCriticalSection.Release();

				//m_oCriticalSection.Wait();
				//lpB = m_oOutputBuffersQueue.front();
				m_oOutputBuffersQueue.pop(lpB);
				//m_oCriticalSection.Release();
			}
			else
			{
				//m_oCriticalSection.Wait();
				if (m_oOutputBuffersQueue.size() < 1)
				{
					//m_oCriticalSection.Release();
					return false;
				}
			//	m_oCriticalSection.Release();

				//m_oCriticalSection.Wait();
				//lpT = m_oOutputBuffersQueue.front();
				m_oOutputBuffersQueue.pop(lpT);
				//m_oCriticalSection.Release();
				//BuffersQueue.pop(lpT);
			}

			if (_IsFieldBased(m_sResolution))
			{
				
				uint8_t * p1 = (uint8_t *)lpT.pVideoBuffer;//寄场指针
				uint8_t *p2 = (uint8_t *)lpB.pVideoBuffer;//偶场指针
				if (m_sResolution.ulWidth == 720 && (m_sResolution.ulHeight == 288 * 2 || m_sResolution.ulHeight == 243 * 2))
				{
					uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(720*2*576);
					frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, 720*2*576); });

					tbb::parallel_for<size_t>(0, m_sResolution.ulHeight, [&](size_t y)
					{
						if (y % 2)
						{

							fast_memcpy(frame.pvideo.get() + y * 720 * 2, p2 + (y / 2)*lpB.ui32VideoRowPitchInBytes, 720 * 2);
						}
						else
						{

							fast_memcpy(frame.pvideo.get() + y * 720 * 2, p1 + (y / 2)*lpT.ui32VideoRowPitchInBytes, 720 * 2);
						}
					});
				}
				else
				{
					uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight * 2);
					frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight * 2); });

					tbb::parallel_for<size_t>(0, lpT.ui32VideoHeight*2, [&](size_t y)
					{
						if (y % 2)
						{
							fast_memcpy(frame.pvideo.get() + y * lpB.ui32VideoRowPitchInBytes, p2 + (y / 2)*lpB.ui32VideoRowPitchInBytes, lpB.ui32VideoRowPitchInBytes);
						}
						else
						{
							fast_memcpy(frame.pvideo.get() + y *  lpT.ui32VideoRowPitchInBytes, p1 + (y / 2)*lpT.ui32VideoRowPitchInBytes, lpT.ui32VideoRowPitchInBytes);
						}
					});
					
				}
				uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32AudioSize*2);
				frame.paudio = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32AudioSize * 2); });
				fast_memcpy(frame.paudio.get(), lpT.pAudioBuffer, lpT.ui32AudioSize);
				fast_memcpy(frame.paudio.get() + lpT.ui32AudioSize, lpB.pAudioBuffer, lpB.ui32AudioSize);
				frame.videolen = lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight*2;
				frame.audiolen = lpT.ui32AudioSize*2;
				frame.width = lpT.ui32Width==768 ? 720: lpT.ui32Width;
				frame.height = lpT.ui32VideoHeight*2;
				frame.interlaced_frame = 1;
				frame.top_field_first = 1;
				frame.afd_aspect_ratio_ = -1;
				frame.afd_command_ = -1;
				
				switch (m_sResolution.eFrameRate)
				{
				case keMvFrameRate25:
					frame.usample = (48000 /25);
				case keMvFrameRate30:
					frame.usample = (48000 / 30);
				case keMvFrameRate50:
					frame.usample = (48000 / 50);
				case keMvFrameRate60:
					frame.usample = (48000 / 60);
				default:
					frame.usample = (48000 / 25);
					break;
				}
			}
			else
			{
				uint8_t* pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight);
				frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight); });

				pdest = (uint8_t*)cc_memory_pool.allocate(lpT.ui32AudioSize);
				frame.pvideo = std::shared_ptr<uint8_t>(pdest, [&](uint8_t* p) {cc_memory_pool.deallocate(p, lpT.ui32AudioSize); });

				fast_memcpy(frame.pvideo.get(), lpT.pVideoBuffer, lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight);
				fast_memcpy(frame.paudio.get(), lpT.pAudioBuffer, lpT.ui32AudioSize);
				frame.videolen = lpT.ui32VideoRowPitchInBytes*lpT.ui32VideoHeight;
				frame.audiolen = lpT.ui32AudioSize;
				frame.width = lpT.ui32Width;
				frame.height = lpT.ui32VideoHeight;
				frame.interlaced_frame = 0;
				frame.top_field_first = 0;
				frame.afd_aspect_ratio_ = -1;
				frame.afd_command_ = -1;
				switch (m_sResolution.eFrameRate)
				{
				case keMvFrameRate25:
					frame.usample = (48000 / 25);
				case keMvFrameRate30:
					frame.usample = (48000 / 30);
				case keMvFrameRate50:
					frame.usample = (48000 / 50);
				case keMvFrameRate60:
					frame.usample = (48000 / 60);
				default:
					frame.usample = (48000 / 25);
					break;
				}
			}
			if (lpT.pVideoBuffer)
				free(lpT.pVideoBuffer);
			if (lpT.pAudioBuffer)
				free(lpT.pAudioBuffer);
			if (lpB.pVideoBuffer)
				free(lpB.pVideoBuffer);
			if (lpB.pAudioBuffer)
				free(lpB.pAudioBuffer);
			return true;
		}
		void CmvsInputTopology::_ProcessVanc(SMvVancPacket* in_paVancPackets, uint32_t in_ui32PacketCount)
		{
			CMvHResult oHr;
			if (in_ui32PacketCount)
			{
				for (uint32_t i = 0; i < in_ui32PacketCount; i++)
				{

					EMvVANCPacketType eVancPacketType;
					oHr = m_pJVancDataPackets->GetVancPacketType(&in_paVancPackets[i], eVancPacketType);

					if (oHr.DidFail())
					{
						LogError(oHr, "GetVancPacketType() failed.\n");
					}

					switch (eVancPacketType)
					{
					case keMvVANCPacketTypeAFDAndBarData:
					{
						/*if (m_bVerbose)
						{
							printf("          PacketType: AFD and Bar Data\n");
						}*/
						printf("          PacketType: AFD and Bar Data\n");
						// Transform packet into AFD and Bar Data packet structure.
						SMvAFDAndBarDataVancPacket sAFDAndBarPacket;
						m_pJVancDataPackets->TransformVancPacketToAFDAndBarDataPacket(&in_paVancPackets[i], &sAFDAndBarPacket);
						/*if (m_bVerbose)
						{
							printf("          AFD code: 0x%x    16x9: %s\n", sAFDAndBarPacket.sAFD.ui8AFDCode, sAFDAndBarPacket.sAFD.bIs16by9AspectRatio ? "true" : "false");
							printf("          Bar Data Presence: %s%s%s%s\n", sAFDAndBarPacket.sBarData.bTopPresenceFlag ? "Top " : "",
								sAFDAndBarPacket.sBarData.bBottomPresenceFlag ? "Bottom " : "",
								sAFDAndBarPacket.sBarData.bLeftPresenceFlag ? "Left " : "",
								sAFDAndBarPacket.sBarData.bRightPresenceFlag ? "Right" : "");
							printf("          Top: %d Bottom: %d Left: %d Right: %d\n", sAFDAndBarPacket.sBarData.uTopOrLeftBar.ui16LineNumberEndOfTopBar,
								sAFDAndBarPacket.sBarData.uBottomOrRightBar.ui16LineNumberStartOfBottomBar,
								sAFDAndBarPacket.sBarData.uTopOrLeftBar.ui16PixelNumberEndOfLeftBar,
								sAFDAndBarPacket.sBarData.uBottomOrRightBar.ui16PixelNumberStartOfRightBar);
						}*/

						// Transform back to vanc packet (for testing only).
						SMvVancPacket sVancPacket;
						m_pJVancDataPackets->TransformAFDAndBarDataPacketToVancPacket(&sAFDAndBarPacket, in_paVancPackets[i].ui32LineNumber, &sVancPacket);
						break;
					}
					case keMvVANCPacketTypeCaptionDistribution:
					{
						/*if (m_bVerbose)
						{
							printf("          PacketType: Caption Distribution\n");
						}*/

						// Transform packet into Caption Distribution packet.
						SMvCaptionDistributionPacket sCaptionDistributionPacket;
						m_pJVancDataPackets->TransformVancPacketToCaptionDistributionPacket(&in_paVancPackets[i], &sCaptionDistributionPacket);

						/*if (m_bVerbose)
						{
							const wchar_t *pwszFrameRate = NMvHelper::FrameRateToString(sCaptionDistributionPacket.eFrameRate);
							const wchar_t *pwszScanMode = NMvHelper::ScanModeToString(sCaptionDistributionPacket.eScanMode);
							printf("          Counter: %d  Frame rate: %ls  Scan mode: %ls\n", sCaptionDistributionPacket.ui16CPDSequenceCounter, pwszFrameRate, pwszScanMode);
							printf("          Time code %s: %" PRIu64 "%" PRIu64 ":%" PRIu64 "%" PRIu64 ":%" PRIu64 "%" PRIu64 "%s%" PRIu64 "%" PRIu64 "\n", sCaptionDistributionPacket.bIsTimeCodeValid ? "(valid)" : "(not valid)",
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucTensOfHours,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucUnitOfHours,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucTensOfMinutes,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucUnitOfMinutes,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucTensOfSeconds,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucUnitOfSeconds,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucDropFrame ? ";" : ":",
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucTensOfFrames,
								sCaptionDistributionPacket.uSMPTE12_VITC_TimeCode.TimeCode.ucUnitOfFrames);
							printf("          CC count: %u  CCSVC count: %u\n", sCaptionDistributionPacket.ui32CC_Count, sCaptionDistributionPacket.ui32SVC_Count);
						}*/

						// Transform back to vanc packet (for testing only).
						SMvVancPacket sVancPacket;
						m_pJVancDataPackets->TransformCaptionDistributionPacketToVancPacket(&sCaptionDistributionPacket, in_paVancPackets[i].ui32LineNumber, &sVancPacket);

						break;
					}
					case keMvVANCPacketTypeUnknown:
					{
						SMvAFDAndBarDataVancPacket sAFDAndBarPacket;
						
						m_pJVancDataPackets->TransformVancPacketToAFDAndBarDataPacket(&in_paVancPackets[i], &sAFDAndBarPacket);
						ratio_4_3 = sAFDAndBarPacket.sAFD.bIs16by9AspectRatio ? 0 : 1;
						nCmd_ = sAFDAndBarPacket.sAFD.ui8AFDCode;
						break;
					}
					default:
					{
						break;
					}
					}
				}
			}
		}
	}
}