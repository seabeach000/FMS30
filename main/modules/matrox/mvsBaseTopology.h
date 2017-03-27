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

#ifndef MVBASETOPOLOGY_H
#define	MVBASETOPOLOGY_H

#include "MatroxDSXsdk.h"
namespace caspar {
	namespace matrox {
		const uint64_t g_kui64W2RinFrames = 2;
		const uint32_t g_kui32NodeDepth = 6;


		class CmvsBaseTopology
		{
		public:
			CmvsBaseTopology(IMvSystemConfiguration *in_pISystemConfiguration,
				IMvCardConfiguration* in_pICardConfiguration,
				SMvResolutionInfo* in_psResolutionInfo);
			virtual ~CmvsBaseTopology();

			void SetTopologyName(const char* in_kszName);
			void SetupClock(IMvVideoInputConnector * in_pIConnector);
			uint64_t GetCurrentTime();

			HRESULT LogTopologies();
			void LogError(HRESULT in_oHr, const char * in_szErrorMsg, ...);

		protected:

			void    _RetrieveGenlockClock();
			HRESULT _RetrieveInputClock(IMvVideoInputConnector * in_pIConnector);
			HRESULT _CreateTopology(const char* in_kszName);

			void _InitNodeSettings(const char in_szName[32],
				EMvSurfaceFormat in_eSurfaceFormat,
				SMvNodeSettings *in_psNodeSettings,
				SMvNodeSettingsVideo* in_psVideoSettings = NULL,
				SMvNodeSettingsAudio* in_psAudioSettings = NULL,
				SMvNodeSettingsVanc* in_psVancSettings = NULL);
			void _InitInputStreamSettings(SMvInputStreamSettings &out_rsStreamSettings);
			void _InitOutputStreamSettings(SMvOutputStreamSettings &out_rsStreamSettings);
			void _InitTransformStreamSettings(SMvTransformStreamSettings &out_rsStreamSettings);
			void _InitMixerStreamSettings(SMvMixerStreamSettings &out_rsStreamSettings);
			void _InitMixerNodeSettings(SMvMixerStreamNodeSettings &out_rsNodeSettings);

			HRESULT _GetVideoInputConnector(IMvSdiVideoInputConnector **in_ppISdiVideoInputConnector, uint8_t in_ui8InputIndex);
			HRESULT _GetVideoOutputConnector(IMvSdiVideoOutputConnector **in_ppISdiVideoOutputConnector, uint8_t in_ui8OutputIndex);

			HRESULT _GetEmbeddedAudioInputConnectors(IMvSdiVideoInputConnector *in_pISdivideoInputConnector,
				IMvAudioInputConnector   **out_apIAudioInputConnectors,
				uint32_t &io_rui32Count);

			inline bool _IsFieldBased(SMvResolutionInfo &in_sResInfo)
			{
				return in_sResInfo.eScanMode == keMvScanModeFirstFieldTop || in_sResInfo.eScanMode == keMvScanModeSecondFieldTop;
			}

			SMvResolutionInfo                   m_sResolution;
			TMvSmartPtr<IMvSystemConfiguration> m_pJSystemConfiguration;
			TMvSmartPtr<IMvCardConfiguration>   m_pJCardCfg;
			TMvSmartPtr<IMvSystemTopology>      m_pJTopology;
			TMvSmartPtr<IMvSystemClock>         m_pJClock;
			TMvSmartPtr<IMvFlexEngine>          m_pJFlexEngine;
			uint64_t                            m_ui64W2RDelayInVideoUnits;
		};
	}
}
#endif	/* MVBASETOPOLOGY_H */

