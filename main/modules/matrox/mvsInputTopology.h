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


#pragma once

#include "mvThread.h"
#include "mvsBaseTopology.h"
#include <MvFlexAPI.h>
#include <queue>
#include <tbb/concurrent_queue.h>
#include "matrox_interface.h"
namespace caspar {
	namespace matrox {

		class CmvsInputTopology : public CmvsBaseTopology,
			public CMvUnknown,
			public IMvNodeNotificationCallback
		{
		public:
			MVDECLARE_IUNKNOWN;
			CmvsInputTopology(IMvSystemConfiguration *in_pISystemConfiguration,
				IMvCardConfiguration* in_pICardConfiguration,
				SMvResolutionInfo *in_pResolutionInfo,
				uint8_t connector);
			virtual ~CmvsInputTopology();

			HRESULT BuildTopology(const char *in_kszName, uint8_t in_ui8InputIndex,uint8_t channel_number);
			//bool get_frame_buffer(void * pvideo, unsigned int &videolen, void * paudio, unsigned int &audiolen);
			bool get_frame(MatroxFrame & frame);
			
		protected:
			virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters);

			void _ProcessVanc(SMvVancPacket* in_paVancPackets, uint32_t in_ui32PacketCount);
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters>	BuffersQueue;
			tbb::concurrent_bounded_queue<SMvNodeNotificationCallbackParameters> m_oOutputBuffersQueue;
			
		private:
			tbb::cache_aligned_allocator<uint8_t>  cc_memory_pool;
			TMvSmartPtr<IMvInputStream>           m_pJInputStream;
			TMvSmartPtr<IMvNode>                  m_pJCardNode;
			TMvSmartPtr<IMvHostNode>              m_pJHostNode;
			TMvSmartPtr<IMvTransferStream>        m_pJTransferStream;
			TMvSmartPtr<IMvVancDataPackets>       m_pJVancDataPackets;
			CMvCriticalSection m_oCriticalSection;

			CMvEvent			m_oCompletionEvent;

			unsigned long		m_ulAudioSampleSize;
			uint32_t			m_ui32RemainingUnitsToCapture;
			bool				ratio_4_3;
			int					nCmd_;
			bool				is_running_;//是否开始,避免队列满
			bool				noStartpush;//入队判断 顶场先入队


		private:

		};
	}
}