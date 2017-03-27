
#pragma once

#include <mvUnknown.h>
#include <MvFlexAPI.h>
#include <mvSmartPtr.h>
#include <core/video_format.h>
namespace caspar {
	namespace matrox {
#define		MAX_SDI_EA_CONNECTOR	16

		class CStatusCallbackSdiIn : public CMvUnknown,
			public IMvVideoConnectorNotificationCallback
		{
		public:
			CStatusCallbackSdiIn(IMvSdiVideoInputConnector * in_pIConnector, core::video_format format);
			CStatusCallbackSdiIn();

			virtual ~CStatusCallbackSdiIn(void);

			// Interface IMvVideoConnectorNotificationCallback
			virtual HRESULT __stdcall Notify(EMvVideoConnectorLabel    in_eVideoConnectorLabel,
				SMvVideoConnectorStatus & in_rsVideoConnectorStatus);

			// CMvUnknow implementation
			MVDECLARE_IUNKNOWN;

			// Public methods
			void GetStatus(SMvVideoConnectorStatus & io_rsVideoStatus, SMvAudioPairStatus out_asAudioStatus[]);
			EMvVideoConnectorLabel GetSDIConnectorID() { return m_eVideoConnectorLabel; }
			bool change();
			void reset();

		protected:
			TMvSmartPtr <IMvSdiVideoInputConnector> m_pJConnector;
			CMvCriticalSection      m_csStatusLock;
			SMvVideoConnectorStatus m_sVideoStatus;
			SMvAudioPairStatus      m_asAudioStatus[MAX_SDI_EA_CONNECTOR];
			EMvVideoConnectorLabel  m_eVideoConnectorLabel;
			bool formatchange_;
		};
	}
}
