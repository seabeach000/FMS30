#include "SDIInConnectorStatusCallback.h"
#include <iostream>
#include <mvErrors.h>
#include <core/video_format.h>
#include <common/log.h>
namespace caspar {
	namespace matrox {
		// ---------------------------------------------------------------------------------------------------------------------
		CStatusCallbackSdiIn::CStatusCallbackSdiIn(IMvSdiVideoInputConnector * in_pIConnector, core::video_format format)
			: CMvUnknown(L"CStatusCallbackSdiIn", NULL)
			, m_pJConnector(in_pIConnector)
			, formatchange_(false)
		{
			switch (format)
			{
			case caspar::core::video_format::pal:
				m_sVideoStatus.sDetectedResolution.ulWidth = 720;
				m_sVideoStatus.sDetectedResolution.ulHeight= 576;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeFirstFieldTop;
				break;
			case caspar::core::video_format::ntsc:
				m_sVideoStatus.sDetectedResolution.ulWidth = 720;
				m_sVideoStatus.sDetectedResolution.ulHeight = 486;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeSecondFieldTop;
				break;
			case caspar::core::video_format::x1080i5000:
				m_sVideoStatus.sDetectedResolution.ulWidth = 1920;
				m_sVideoStatus.sDetectedResolution.ulHeight = 1080;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeFirstFieldTop;
				break;
			case caspar::core::video_format::x1080p2500:
				m_sVideoStatus.sDetectedResolution.ulWidth = 1920;
				m_sVideoStatus.sDetectedResolution.ulHeight = 1080;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeProgressive;
				break;
			case caspar::core::video_format::x2160p2500:
				m_sVideoStatus.sDetectedResolution.ulWidth = 1920;
				m_sVideoStatus.sDetectedResolution.ulHeight = 1080;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeProgressive;
				break;
			case caspar::core::video_format::x576p2500:
				m_sVideoStatus.sDetectedResolution.ulWidth = 720;
				m_sVideoStatus.sDetectedResolution.ulHeight = 576;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeProgressive;
				break;
			case caspar::core::video_format::x720p2500:
				m_sVideoStatus.sDetectedResolution.ulWidth = 1280;
				m_sVideoStatus.sDetectedResolution.ulHeight = 720;
				m_sVideoStatus.sDetectedResolution.eScanMode = keMvScanModeProgressive;
				break;
			default:
				break;
			}
		}

		// ---------------------------------------------------------------------------------------------------------------------
		CStatusCallbackSdiIn::CStatusCallbackSdiIn()
			: CMvUnknown(L"CStatusCallbackSdiIn", NULL)
		{
		}

		// ---------------------------------------------------------------------------------------------------------------------
		CStatusCallbackSdiIn::~CStatusCallbackSdiIn(void)
		{

		}

		// ---------------------------------------------------------------------------------------------------------------------
		HRESULT CStatusCallbackSdiIn::Notify(EMvVideoConnectorLabel    in_eVideoConnectorLabel,
			SMvVideoConnectorStatus & in_rsVideoConnectorStatus)
		{
			
			//回调会激发多次，值判断一次就好了，所以要判断一下，不能每次formatchange都设置成true
			m_eVideoConnectorLabel = in_eVideoConnectorLabel;
			std::wstring strSDIInputStatusNotify;

			if (in_eVideoConnectorLabel == m_pJConnector->GetVideoInputConnectorLabel())
			{
				// Get the SDI video and EA audio status
				CMvAutoLock oLock(&m_csStatusLock);

				/*for (uint32_t ui32Index = 0; ui32Index < _countof(m_asAudioStatus); ui32Index++)
				{
					m_asAudioStatus[ui32Index].ui32Size = sizeof(m_asAudioStatus[0]);
				}

				m_pJConnector->GetSdiEmbeddedAudioInputPairConnectorsStatuses(m_asAudioStatus, _countof(m_asAudioStatus));*/
				if (in_rsVideoConnectorStatus.sDetectedResolution.ulWidth>0&& in_rsVideoConnectorStatus.sDetectedResolution.ulHeight>0)
				{
				
					if (m_sVideoStatus.sDetectedResolution.ulWidth != in_rsVideoConnectorStatus.sDetectedResolution.ulWidth
						|| m_sVideoStatus.sDetectedResolution.ulHeight != in_rsVideoConnectorStatus.sDetectedResolution.ulHeight)
					{
						m_sVideoStatus = in_rsVideoConnectorStatus;
						formatchange_ = true;
					}
				}
			}
			else
			{
				
				CASPAR_LOG(error) <<L"CStatusCallbackSdiIn::Notify: Video: Invalid connector label.  Expecting " << m_pJConnector->GetVideoInputConnectorLabel() <<
					"and received"<< in_eVideoConnectorLabel;
			}

			return MV_NOERROR;
		}


		// ---------------------------------------------------------------------------------------------------------------------
		void CStatusCallbackSdiIn::GetStatus(SMvVideoConnectorStatus & io_rsVideoStatus, SMvAudioPairStatus out_asAudioStatus[])
		{
			CMvAutoLock oLock(&m_csStatusLock);

			io_rsVideoStatus = m_sVideoStatus;
			memcpy(out_asAudioStatus, m_asAudioStatus, sizeof(m_asAudioStatus));
		}
		bool  CStatusCallbackSdiIn::change()
		{
			return formatchange_;
		}
		void  CStatusCallbackSdiIn::reset()
		{
			formatchange_ =false;
		}
	}
}