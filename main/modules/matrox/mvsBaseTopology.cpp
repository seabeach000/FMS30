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

#include "mvsBaseTopology.h"
#include <common/utf.h>
#include <common/log.h>
#ifdef LINUX_PLATFORM
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#endif
namespace caspar {
	namespace matrox {
		// ----------------------------------------------------------------------------
		CmvsBaseTopology::CmvsBaseTopology(IMvSystemConfiguration *in_pISystemConfiguration,
			IMvCardConfiguration* in_pICardConfiguration,
			SMvResolutionInfo* in_psResolutionInfo)
			: m_pJSystemConfiguration(in_pISystemConfiguration)
			, m_pJCardCfg(in_pICardConfiguration)
		{
			if (in_psResolutionInfo)
			{
				memcpy(&m_sResolution, in_psResolutionInfo, sizeof(m_sResolution));
			}
			else
			{
				memset(&m_sResolution, 0, sizeof(m_sResolution));
			}

			if (in_psResolutionInfo)
			{
				m_ui64W2RDelayInVideoUnits = _IsFieldBased(*in_psResolutionInfo) ? g_kui64W2RinFrames * 2 : g_kui64W2RinFrames;
			}
			else
			{
				// Assume default is ntsc.
				m_ui64W2RDelayInVideoUnits = g_kui64W2RinFrames * 2;
			}
		}

		// ----------------------------------------------------------------------------
		CmvsBaseTopology::~CmvsBaseTopology()
		{
			//m_pJTopology->DestroyTopology();
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsBaseTopology::LogTopologies()
		{
			CMvHResult oHr;

			// Create topology enumerator.
			TMvSmartPtr<IMvSystemTopologyEnumerator> pJTopologyEnum;
			oHr = m_pJSystemConfiguration->CreateSystemTopologyEnumerator(&pJTopologyEnum);

			if (oHr.DidFail())
			{
				return oHr;
			}

			CASPAR_LOG(info)<<L"\n*********************************************************************";

			TMvSmartPtr<IMvSystemTopology> pJTopology;
			pJTopologyEnum->Next(&pJTopology);

			if (!pJTopology)
			{
				CASPAR_LOG(info)<<L"No topologies on board.";
			}

			pJTopologyEnum->Reset();
			pJTopology = NULL;

			//Make sure any error has been reset
			oHr = MV_NOERROR;

			// Loop through topologies.
			while (pJTopologyEnum->Next(&pJTopology) == MV_NOERROR)
			{
				char szTopologyName[32];
				pJTopology->GetName(szTopologyName, 32);
				CASPAR_LOG(info)<<L"Topology : "<<u16(szTopologyName);

				// Create node enumerator.
				TMvSmartPtr<IMvNodesEnumerator> pJNodeEnum;
				oHr = pJTopology->CreateNodesEnumerator(&pJNodeEnum);
				if (oHr.DidFail()) return oHr;

				// Create stream enumerator.
				TMvSmartPtr<IMvStreamsEnumerator> pJStreamEnum;
				oHr = pJTopology->CreateStreamsEnumerator(&pJStreamEnum);
				if (oHr.DidFail()) return oHr;

				// Loop through streams.
				//TMvSmartPtr<IMvStream> pJStream;
				//while (pJStreamEnum->Next(&pJStream) == MV_NOERROR)
				//{
				//	char szStreamName[32];
				//	pJStream->GetName(szStreamName, 32);
				//	CASPAR_LOG(info)<<L"   STREAM NAME: "<<u16(szStreamName);

				//	EMvStreamType eStreamType = pJStream->GetStreamType();
				//	switch (eStreamType)
				//	{
				//	case keMvStreamTypeInputStream:
				//	{
				//		CASPAR_LOG(info) << L"  [TYPE: Input stream]";
				//		TMvSmartQPtr<IMvInputStream, &IID_IMvInputStream> pJInputStream(pJStream, &oHr);
				//		if (oHr.DidFail()) return oHr;

				//		SMvResolutionInfo sResolution = { sizeof(sResolution) };
				//		pJInputStream->GetResolution(sResolution);

				//		std::string strScanMode = "p";
				//		if (sResolution.eScanMode == keMvScanModeFirstFieldTop ||
				//			sResolution.eScanMode == keMvScanModeSecondFieldTop)
				//		{
				//			strScanMode = "i";
				//		}
				//		CASPAR_LOG(info) << L"  [RES:"<< sResolution.ulWidth<<L"x"<< sResolution.ulHeight<<strScanMode.c_str()<<
				//			u16(MV_FRAME_RATE_ENUM_TO_STRING(sResolution.eFrameRate))<<L"]";


				//		TMvSmartPtr<IMvVideoInputConnector> pJVideoInputConnector;
				//		pJInputStream->GetVideoInputConnector(&pJVideoInputConnector);
				//		if (pJVideoInputConnector)
				//		{
				//			EMvVideoConnectorLabel eLabel = pJVideoInputConnector->GetVideoInputConnectorLabel();
				//			CASPAR_LOG(info)<<L"  [Input Connector: %s,"<<u16(MV_VIDEO_CONNECTOR_LABEL_ENUM_TO_STRING(eLabel))<<L"]";
				//		}

				//		TMvSmartPtr<IMvNode> pJOutputNode;
				//		uint64_t ui64Timestamp;
				//		oHr = pJInputStream->GetOutputNode(ui64Timestamp, &pJOutputNode);
				//		if (oHr.DidFail()) return oHr;

				//		if (pJOutputNode)
				//		{
				//			pJOutputNode->GetName(szStreamName, 32);
				//			CASPAR_LOG(info) << L"  [OUTPUT NODE: "<<szStreamName<<L"]";
				//		}

				//		break;
				//	}
				//	case keMvStreamTypeOutputStream:
				//	{
				//		/*CASPAR_LOG(info) << L"  [TYPE: Output stream]";
				//		TMvSmartQPtr<IMvOutputStream, &IID_IMvOutputStream> pJOutputStream(pJStream, &oHr);
				//		if (oHr.DidFail()) return oHr;

				//		SMvResolutionInfo sResolution = { sizeof(sResolution) };
				//		pJOutputStream->GetResolution(sResolution);

				//		std::string strScanMode = "p";
				//		if (sResolution.eScanMode == keMvScanModeFirstFieldTop ||
				//			sResolution.eScanMode == keMvScanModeSecondFieldTop)
				//		{
				//			strScanMode = "i";
				//		}
				//		CASPAR_LOG(info) << L"  [RES:" << sResolution.ulWidth << L"x" << sResolution.ulHeight << strScanMode.c_str() <<
				//			u16(MV_FRAME_RATE_ENUM_TO_STRING(sResolution.eFrameRate)) << L"]";
				//		uint32_t ui32NbOutputConnectors = 8;
				//		IMvSdiVideoOutputConnector *apIVideoOutputConnector[8];
				//		pJOutputStream->GetVideoOutputConnectors(apIVideoOutputConnector, ui32NbOutputConnectors);
				//		for (uint32_t i = 0; i < ui32NbOutputConnectors; i++)
				//		{
				//			EMvVideoConnectorLabel eLabel = apIVideoOutputConnector[i]->GetVideoOutputConnectorLabel();
				//			CASPAR_LOG(info) << L"  [Output Connector: "<<u16(MV_VIDEO_CONNECTOR_LABEL_ENUM_TO_STRING(eLabel));
				//			apIVideoOutputConnector[i]->Release();
				//		}

				//		TMvSmartPtr<IMvNode> pJInputNode;
				//		uint64_t ui64Timestamp;
				//		oHr = pJOutputStream->GetInputNode(ui64Timestamp, &pJInputNode);
				//		if (oHr.DidFail()) return oHr;

				//		if (pJInputNode)
				//		{
				//			pJInputNode->GetName(szStreamName, 32);
				//			CASPAR_LOG(info) << L"  [INPUT NODE: " << szStreamName << L"]";
				//		}*/

				//		break;
				//	}
				//	case keMvStreamTypeTransformStream:
				//	{
				//		CASPAR_LOG(info)<<L"  [TYPE: Transform stream]";
				//		TMvSmartQPtr<IMvTransformStream, &IID_IMvTransformStream> pJTransformStream(pJStream, &oHr);
				//		if (oHr.DidFail()) return oHr;

				//		TMvSmartPtr<IMvNode> pJInputNode;
				//		uint64_t ui64Timestamp;
				//		oHr = pJTransformStream->GetInputNode(ui64Timestamp, &pJInputNode);
				//		if (oHr.DidFail()) return oHr;

				//		if (pJInputNode)
				//		{
				//			pJInputNode->GetName(szStreamName, 32);
				//			CASPAR_LOG(info) << L"  [INPUT NODE: " << u16(szStreamName) << L"]";
				//		}

				//		TMvSmartPtr<IMvNode> pJOutputNode;
				//		oHr = pJTransformStream->GetOutputNode(ui64Timestamp, &pJOutputNode);
				//		if (oHr.DidFail()) return oHr;

				//		if (pJOutputNode)
				//		{
				//			pJOutputNode->GetName(szStreamName, 32);
				//			CASPAR_LOG(info) << L"  [OUTPUT NODE: "<<  u16(szStreamName)<<	L"]";
				//		}

				//		break;
				//	}
				//	case keMvStreamTypeMixerStream:
				//	{
				//		CASPAR_LOG(info) << L"  [TYPE: Transform stream]";
				//		TMvSmartQPtr<IMvMixerStream, &IID_IMvMixerStream> pJMixerStream(pJStream, &oHr);
				//		if (oHr.DidFail()) return oHr;

				//		uint32_t ui32InputCount = 16;
				//		IMvNode* apIInputNodes[16];

				//		uint64_t ui64Timestamp;
				//		oHr = pJMixerStream->GetInputNodes(ui64Timestamp, apIInputNodes, ui32InputCount);
				//		if (oHr.DidFail()) return oHr;

				//		for (uint32_t i = 0; i < ui32InputCount; i++)
				//		{
				//			apIInputNodes[i]->GetName(szStreamName, 32);
				//			CASPAR_LOG(info) << L"  [INPUT NODE: "<< u16(szStreamName) <<L"]";
				//			apIInputNodes[i]->Release();
				//		}

				//		TMvSmartPtr<IMvNode> pJOutputNode;
				//		oHr = pJMixerStream->GetOutputNode(ui64Timestamp, &pJOutputNode);
				//		if (oHr.DidFail()) return oHr;

				//		if (pJOutputNode)
				//		{
				//			pJOutputNode->GetName(szStreamName, 32);
				//			CASPAR_LOG(info) << L"  [OUTPUT NODE: " << u16(szStreamName) << L"]";
				//		}

				//		break;
				//	}
				//	default:
				//	{
				//		break;
				//	}
				//	}
				//	pJStream = NULL;
				//}

				// Loop through nodes.
			/*	TMvSmartPtr<IMvNode> pJNode;
				while (pJNodeEnum->Next(&pJNode) == MV_NOERROR)
				{
					char szNodeName[32];
					pJNode->GetName(szNodeName, 32);
					CASPAR_LOG(info) << L"   Node  : [NAME: "<< u16(szNodeName) << L"]";

					EMvNodeContent eNodeContent = pJNode->GetNodeContentType();

					CASPAR_LOG(info) << L"  [TYPE: %S]"<<(wchar_t*)MV_NODE_CONTENT_ENUM_TO_STRING(eNodeContent);

					pJNode = NULL;
				}*/
				pJTopology->AcquireControl();
				pJTopology = NULL;
			}
		
			return oHr;
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::SetupClock(IMvVideoInputConnector * in_pIConnector)
		{
			_RetrieveGenlockClock();
			// Search for an input clock. If nothing is found, we settle for a genlock clock.
			//if (!in_pIConnector)
			//{
			//	// Settle for a genlock clock.
			//	_RetrieveGenlockClock();
			//}
			//else if (_RetrieveInputClock(in_pIConnector) != MV_NOERROR)
			//{
			//	// Settle for a genlock clock.
			//	_RetrieveGenlockClock();
			//}
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_RetrieveGenlockClock()
		{
			CMvHResult oHr;

			// Get the clock enumerator interface.
			TMvSmartPtr<IMvSystemClockEnumerator> pJClockEnum;
			TMvSmartPtr<IMvSystemClock> pJClock;

			oHr = m_pJCardCfg->CreateSystemClockEnumerator(&pJClockEnum);

			// Enumarate all clocks in the system.
			while (pJClockEnum->Next(&pJClock) == MV_NOERROR)
			{
				// Search for a genlock clock
				if (pJClock->GetClockType() == keMvSystemClockTypeGenlock)
				{
					// This is the genlock clock corresponding to the used card.
					m_pJClock = pJClock;
					break;
				}

				// Next clock
				pJClock = NULL;
			}
		}


		// ----------------------------------------------------------------------------
		HRESULT CmvsBaseTopology::_RetrieveInputClock(IMvVideoInputConnector * in_pIConnector)
		{
			CMvHResult oHr;

			// Get the clock enumerator interface.
			TMvSmartPtr<IMvSystemClockEnumerator> pJClockEnum;
			TMvSmartPtr<IMvSystemClock> pJClock;

			oHr = m_pJCardCfg->CreateSystemClockEnumerator(&pJClockEnum);

			// Enumarate all clocks in the system.
			while (pJClockEnum->Next(&pJClock) == MV_NOERROR)
			{
				// Search for an input clock
				if (pJClock->GetClockType() == keMvSystemClockTypeInput)
				{
					TMvSmartQPtr<IMvSystemClockInput, &IID_IMvSystemClockInput> pQInputClk(pJClock, &oHr);
					oHr.AssertIfError();

					TMvSmartPtr<IMvSdiVideoInputConnector> pJTempConnector;

					oHr = pQInputClk->GetConnector(&pJTempConnector);

					if (in_pIConnector->GetVideoInputConnectorLabel() == pJTempConnector->GetVideoInputConnectorLabel())
					{
						// This is the input clock we want.
						m_pJClock = pJClock;
						break;
					}
				}

				// Next clock
				pJClock = NULL;
			}

			return m_pJClock == NULL ? MV_E_NOT_FOUND : MV_NOERROR;
		}

		uint64_t CmvsBaseTopology::GetCurrentTime()
		{
			if (m_pJClock)
			{
				return m_pJClock->GetTime();
			}

			return 0;
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsBaseTopology::_CreateTopology(const char *in_kszName)
		{
			CMvHResult oHr;

			// Set genlock resolution.         
			TMvSmartPtr<IMvGenlockConfiguration> pJGenlockConfig;
			oHr = m_pJCardCfg->GetGenlockConfiguration(&pJGenlockConfig);

			SMvGeneralHardwareInformation sCardInfo = { sizeof(sCardInfo) };
			sCardInfo.sConnectorsDescription.size = sizeof(sCardInfo.sConnectorsDescription);
			oHr = m_pJCardCfg->GetCardInformation(&sCardInfo, 0);

			// Update the resolution of the genlock settings.
			SMvGenlockSettings sGenlockSettings = { sizeof(sGenlockSettings) };
			oHr = pJGenlockConfig->GetGenlockSettings(sGenlockSettings);

			sGenlockSettings.sResolution = m_sResolution;
			sGenlockSettings.eGenlockSource = keGenlockSourceSDIVideo;
			sGenlockSettings.ui32SourceIndex = 0;
			oHr = pJGenlockConfig->SetGenlockSettings(sGenlockSettings);

			if (oHr.DidFail())
			{
				LogError(oHr, "Error: Unable to set genlock settings");
			}

			// Wait 2 seconds to be sure the hardware is stable enough to start processing.
			boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));

			// Create the topology
			oHr = m_pJSystemConfiguration->CreateSystemTopology(in_kszName, m_pJClock, &m_pJTopology);

			if (oHr.DidFail())
			{
				LogError(oHr, "Error: Unable to create the system topology");
			}

			TMvSmartQPtr<IMvFlexEngine, &IID_IMvFlexEngine> pJFlexEngine(m_pJTopology, &oHr);
			m_pJFlexEngine = pJFlexEngine;

			if (oHr.DidFail())
			{
				LogError(oHr, "Error: Unable to get Flex Engine interface");
			}

			return oHr;
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsBaseTopology::_GetVideoInputConnector(IMvSdiVideoInputConnector **in_ppISdiVideoInputConnector,
			uint8_t in_ui8InputIndex)
		{
			IMvSdiVideoInputConnectorsEnumerator * pISdiVideoInputConnectorsEnumerator = NULL;
			IMvSdiVideoInputConnector * pISdiVideoInputConnector = NULL;
			HRESULT oHr = MV_E_NOT_FOUND;

			if (m_pJCardCfg)
			{
				m_pJCardCfg->CreateSdiVideoInputConnectorsEnumerator(&pISdiVideoInputConnectorsEnumerator);
				if (pISdiVideoInputConnectorsEnumerator)
				{
					pISdiVideoInputConnectorsEnumerator->Reset();
					pISdiVideoInputConnectorsEnumerator->Skip(in_ui8InputIndex);
					pISdiVideoInputConnectorsEnumerator->Next(&pISdiVideoInputConnector);
					if (pISdiVideoInputConnector)
					{
						*in_ppISdiVideoInputConnector = pISdiVideoInputConnector;

						oHr = MV_NOERROR;
					}
					else
					{
						*in_ppISdiVideoInputConnector = NULL;
					}
					pISdiVideoInputConnectorsEnumerator->Release();
				}
			}
			return oHr;
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsBaseTopology::_GetEmbeddedAudioInputConnectors(IMvSdiVideoInputConnector *in_pISdivideoInputConnector,
			IMvAudioInputConnector **out_apIAudioInputConnectors,
			uint32_t &io_rui32Count)
		{
			CMvHResult oHr;
			uint32_t ui32AudioConnectorCount = 0;
			IMvSdiEmbeddedAudioInputPairConnector *pISdiEmbeddedAudioInputConnector;

			TMvSmartPtr<IMvSdiEmbeddedAudioInputPairConnectorsEnumerator> pJEnumerator;
			oHr = in_pISdivideoInputConnector->CreateSdiEmbeddedAudioInputPairConnectorsEnumerator(&pJEnumerator);
			while (pJEnumerator->Next(&pISdiEmbeddedAudioInputConnector) == MV_NOERROR && ui32AudioConnectorCount < io_rui32Count)
			{
				out_apIAudioInputConnectors[ui32AudioConnectorCount] = pISdiEmbeddedAudioInputConnector;
				ui32AudioConnectorCount++;
			}

			io_rui32Count = ui32AudioConnectorCount;

			return oHr;
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsBaseTopology::_GetVideoOutputConnector(IMvSdiVideoOutputConnector **in_ppISdiVideoOutputConnector,
			uint8_t in_ui8OutputIndex)
		{
			IMvSdiVideoOutputConnectorsEnumerator * pISdiVideoOutputConnectorsEnumerator = NULL;
			IMvSdiVideoOutputConnector * pISdiVideoOutputConnector = NULL;
			HRESULT oHr = MV_E_NOT_FOUND;

			if (m_pJCardCfg)
			{
				m_pJCardCfg->CreateSdiVideoOutputConnectorsEnumerator(&pISdiVideoOutputConnectorsEnumerator);
				if (pISdiVideoOutputConnectorsEnumerator)
				{
					pISdiVideoOutputConnectorsEnumerator->Reset();
					pISdiVideoOutputConnectorsEnumerator->Skip(in_ui8OutputIndex);
					pISdiVideoOutputConnectorsEnumerator->Next(&pISdiVideoOutputConnector);
					if (pISdiVideoOutputConnector)
					{
						*in_ppISdiVideoOutputConnector = pISdiVideoOutputConnector;
						oHr = MV_NOERROR;
					}
					else
					{
						*in_ppISdiVideoOutputConnector = NULL;
					}
					pISdiVideoOutputConnectorsEnumerator->Release();
				}
			}
			return oHr;
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_InitNodeSettings(const char in_szName[32],
			EMvSurfaceFormat in_eSurfaceFormat,
			SMvNodeSettings *in_psNodeSettings,
			SMvNodeSettingsVideo* in_psVideoSettings,
			SMvNodeSettingsAudio* in_psAudioSettings,
			SMvNodeSettingsVanc* in_psVancSettings)
		{
			if (in_psNodeSettings)
			{
				in_psNodeSettings->ui32Size = sizeof(*in_psNodeSettings);
				strncpy_s(in_psNodeSettings->szName, _countof(in_psNodeSettings->szName), in_szName, _countof(in_psNodeSettings->szName) - 1);

				in_psNodeSettings->ui64WriteToReadDelayInNanoTime = MvGetNanoTimeForSample(m_ui64W2RDelayInVideoUnits, m_sResolution);

				in_psNodeSettings->ui32Depth = g_kui32NodeDepth;

				in_psNodeSettings->eNodeContent = keMvNodeContentInvalid;
				if (in_psVideoSettings && !in_psAudioSettings && !in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentVideo;
				}

				if (!in_psVideoSettings && in_psAudioSettings && !in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentAudio;
				}

				if (!in_psVideoSettings && !in_psAudioSettings && in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentVanc;
				}

				if (in_psVideoSettings && in_psAudioSettings && !in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentVideoAudio;
				}

				if (in_psVideoSettings && !in_psAudioSettings && in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentVideoVanc;
				}

				if (!in_psVideoSettings && in_psAudioSettings && in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentAudioVanc;
				}

				if (in_psVideoSettings && in_psAudioSettings && in_psVancSettings)
				{
					in_psNodeSettings->eNodeContent = keMvNodeContentVideoAudioVanc;
				}
			}

			if (in_psVideoSettings)
			{
				in_psVideoSettings->ui32Size = sizeof(*in_psVideoSettings);
				in_psVideoSettings->eSurfaceFormat = in_eSurfaceFormat;
				memcpy(&in_psVideoSettings->sResInfo, &m_sResolution, sizeof(m_sResolution));

				if (m_sResolution.ulWidth <= 720)
				{
					in_psVideoSettings->eColorimetry = keMvColorimetryITUR_BT_601;
				}
				else
				{
					in_psVideoSettings->eColorimetry = keMvColorimetryITUR_BT_709;
				}
			}

			if (in_psAudioSettings)
			{
				in_psAudioSettings->ui32Size = sizeof(*in_psAudioSettings);
				in_psAudioSettings->eChannelType = keChannelType16Tracks;
				in_psAudioSettings->eDataType = keAudioDataTypePCM;
				in_psAudioSettings->ui32BitsPerSample = 32;
				in_psAudioSettings->ui32ValidBitsPerSample = 24;
			}

			if (in_psVancSettings)
			{
				in_psVancSettings->ui32Size = sizeof(*in_psVancSettings);
				in_psVancSettings->eVancFormat = keMvSurfaceFormatMatroxAncillaryData;
				in_psVancSettings->ui32ComponentBitCount = 16;
				//in_psVancSettings->eVancFormat = keMvSurfaceFormatYUYV422;
				//in_psVancSettings->ui32ComponentBitCount = 10;
			}
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_InitInputStreamSettings(SMvInputStreamSettings &out_rsStreamSettings)
		{
			out_rsStreamSettings.ui32Size = sizeof(out_rsStreamSettings);

			SMvGeneralHardwareInformation sCardInfo = { sizeof(sCardInfo) };
			sCardInfo.sConnectorsDescription.size = sizeof(sCardInfo.sConnectorsDescription);
			m_pJCardCfg->GetCardInformation(&sCardInfo, 0);

			out_rsStreamSettings.eInputStreamMode = keMvInputStreamModeAudioVideoTBC;
			out_rsStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
			out_rsStreamSettings.sVideoInputStreamSettings.dBrightness = 0.0f;
			out_rsStreamSettings.sVideoInputStreamSettings.dLumaGain = 1.0f;
			out_rsStreamSettings.sVideoInputStreamSettings.dHue = 0.0f;
			out_rsStreamSettings.sVideoInputStreamSettings.dSaturation = 1.0f;
			out_rsStreamSettings.sVideoInputStreamSettings.bAllowSuperBlack = false;
			out_rsStreamSettings.sVideoInputStreamSettings.bAllowSuperWhite = false;
			out_rsStreamSettings.sVideoInputStreamSettings.bEnableChromaClipping = false;
			out_rsStreamSettings.sVideoInputStreamSettings.bUpscaleKeyLuma = false;
			out_rsStreamSettings.sVideoInputStreamSettings.bInvertKeyLuma = false;
			out_rsStreamSettings.sVideoInputStreamSettings.bApplyKeyLumaOffset = false;

			for (uint32_t i = 0; i < 8; i++)
			{
				out_rsStreamSettings.sAudioInputStreamSettings.abCapturePairMute[i] = false;
			}
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_InitOutputStreamSettings(SMvOutputStreamSettings &out_rsStreamSettings)
		{
			out_rsStreamSettings.ui32Size = sizeof(out_rsStreamSettings);
			out_rsStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
			out_rsStreamSettings.sVideoOutputStreamSettings.bAllowSuperBlack = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bAllowSuperWhite = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bDownscaleKeyLuma = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableChromaClipping = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableEdgeSharpeningFilter = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableVideoMixer = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bInvertKeyLuma = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bApplyKeyLumaOffset = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.bIsVideoShaped = false;
			out_rsStreamSettings.sVideoOutputStreamSettings.eVideoMixerVancSource = keVideoMixerVancSourceNode;
			out_rsStreamSettings.sVideoOutputStreamSettings.eVideoMixerAudioAndHancSource = keVideoMixerAudioAndHancSourceMixerOrNode;
			out_rsStreamSettings.sVideoOutputStreamSettings.ui64AdvancedDelayInNanoTime = 0;
			out_rsStreamSettings.sVideoOutputStreamSettings.bEnableMechanicalBypass = false;
			out_rsStreamSettings.sAudioOutputStreamSettings.bEnableAudioMixer = false;
			out_rsStreamSettings.sAudioOutputStreamSettings.bAuxPhaseInvert = false;
			out_rsStreamSettings.sAudioOutputStreamSettings.dAuxMasterVolume = 1.0;
			out_rsStreamSettings.sAudioOutputStreamSettings.dLineMasterVolume = 1.0;
			out_rsStreamSettings.sAudioOutputStreamSettings.eAuxSourceSelection = keMvAudioMixerSourceNode;
			for (uint32_t i = 0; i < 16; i++)
			{
				out_rsStreamSettings.sAudioOutputStreamSettings.adAuxVolume[i] = 1.0;
				out_rsStreamSettings.sAudioOutputStreamSettings.adLineVolume[i] = 1.0;
			}
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_InitTransformStreamSettings(SMvTransformStreamSettings &out_rsStreamSettings)
		{
			out_rsStreamSettings.ui32Size = sizeof(out_rsStreamSettings);
			out_rsStreamSettings.sVideoTransformSettings.eVideoTransformType = keMvVideoTransformTypeInvalid;
			out_rsStreamSettings.sVideoTransformSettings.sInputRect.lLeft = 0;
			out_rsStreamSettings.sVideoTransformSettings.sInputRect.lRight = m_sResolution.ulWidth;
			out_rsStreamSettings.sVideoTransformSettings.sInputRect.lTop = 0;
			out_rsStreamSettings.sVideoTransformSettings.sInputRect.lBottom = m_sResolution.ulHeight;
			out_rsStreamSettings.sVideoTransformSettings.sOutputRect.lLeft = 0;
			out_rsStreamSettings.sVideoTransformSettings.sOutputRect.lRight = m_sResolution.ulWidth;
			out_rsStreamSettings.sVideoTransformSettings.sOutputRect.lTop = 0;
			out_rsStreamSettings.sVideoTransformSettings.sOutputRect.lBottom = m_sResolution.ulHeight;
			out_rsStreamSettings.sVideoTransformSettings.ui64InputNodeAdvancedDelayInNanoTime = 0;
			out_rsStreamSettings.sVideoTransformSettings.eProcessFields = keMvTransformProcessingAll;
			out_rsStreamSettings.sVideoTransformSettings.bVerticalFilterManualControl = false;
			out_rsStreamSettings.sVideoTransformSettings.ui32VerticalFilterManualValue = 0;
			out_rsStreamSettings.sVideoTransformSettings.eTransformFilterCoefficients = keMvTransformFilterCoeffStandard;

			out_rsStreamSettings.sVancConvertingTransformSettings.bClipAllVancPackets = false;
			out_rsStreamSettings.sVancConvertingTransformSettings.bConvertDigitalCEA608ToAnalog = false;
			out_rsStreamSettings.sVancConvertingTransformSettings.bConvertAnalogCEA608ToDigital = false;
			out_rsStreamSettings.sVancConvertingTransformSettings.bInsertBarDataUsingDestRect = false;
			out_rsStreamSettings.sVancConvertingTransformSettings.bInsertAFDCode = false;
			out_rsStreamSettings.sVancConvertingTransformSettings.eAFDCodeAndAspectRatio = keMvAFDCode_16_9_Undefined;
			out_rsStreamSettings.bProcessAudio = true;
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_InitMixerStreamSettings(SMvMixerStreamSettings &out_rsStreamSettings)
		{
			out_rsStreamSettings.ui32Size = sizeof(out_rsStreamSettings);
			out_rsStreamSettings.bProcessAudio = true;
			out_rsStreamSettings.ui32AudioSelect = 1;
			out_rsStreamSettings.bProcessVanc = false;
			out_rsStreamSettings.ui32VancSelect = 1;
			out_rsStreamSettings.eCompositingMode = keMvCompositingModeDownStream;
			out_rsStreamSettings.eBackgroundColor = keMvColorBlue;
			out_rsStreamSettings.eBackgroundHandling = keMvBackgroundHandlingColor;
			out_rsStreamSettings.bIsOutputVideoShaped = false;
			out_rsStreamSettings.bBackgroundChromaFilterARGB = false;
			out_rsStreamSettings.ui64BackgroundNodeAdvancedDelayInNanoTime = 0;
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::_InitMixerNodeSettings(SMvMixerStreamNodeSettings &out_rsNodeSettings)
		{
			out_rsNodeSettings.ui32Size = sizeof(out_rsNodeSettings);
			out_rsNodeSettings.dNodeTransparency = 1.0;
			out_rsNodeSettings.ptNodePosition.fX = 0.0;
			out_rsNodeSettings.ptNodePosition.fY = 0.0;
			out_rsNodeSettings.bUseAlpha = false;
			out_rsNodeSettings.bIsVideoShaped = false;
			out_rsNodeSettings.ui64AdvancedDelayInNanoTime = 0;
			out_rsNodeSettings.bChromaFilterARGB = false;
		}

		// ----------------------------------------------------------------------------
		void CmvsBaseTopology::LogError(HRESULT in_oHr, const char * in_szErrorMsg, ...)
		{
			size_t const SIZE_BUFFER = 128;
			char szErrorMsg[SIZE_BUFFER];

			std::wstring strOHrToString((mvErrorToString(in_oHr)));


			// Build the message from the parameter list and print
			va_list vaList;

			va_start(vaList, in_szErrorMsg);
			vsprintf_s(szErrorMsg, SIZE_BUFFER, in_szErrorMsg, vaList);
			va_end(vaList);


			size_t sizeErrorCode = strOHrToString.find_first_of(L':');
			strOHrToString = strOHrToString.substr(0, sizeErrorCode);
			char buff[1025];
			sprintf(buff,"%s: Error=%#x: %ls\n", szErrorMsg, in_oHr, strOHrToString.c_str());
			CASPAR_LOG(error) << L"mxtrox:" << u16(buff);
		}


	}
}