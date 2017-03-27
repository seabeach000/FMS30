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

#include "mvsBaseTopology.h"
#include <core/frame/frame.h>
#include <tbb/concurrent_queue.h>
#include <queue>
extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}
namespace caspar {
	namespace matrox {
		struct transferconfig
		{
			void * pVideoBuffer;
			void * pAudioBuffer;	
			SMvVancPacket in_paVancPackets;
			uint32_t in_ui32PacketCount;
			bool secondfiel;
			unsigned int RowPitchInbytes;

		};
		class CmvsOutputTopology : public CmvsBaseTopology,
			public CMvUnknown,
			public IMvNodeNotificationCallback
		{
		public:
			MVDECLARE_IUNKNOWN;
			CmvsOutputTopology(IMvSystemConfiguration *in_pISystemConfiguration,
				IMvCardConfiguration* in_pICardConfiguration,
				SMvResolutionInfo *in_pResolutionInfo,int outindex,
				int video_rate,
				int in_channel,
				int out_channel,
				int audio_rate,
				bool vanc_output);
			virtual ~CmvsOutputTopology();

			HRESULT BuildTopology(const char *in_kszName, uint8_t in_ui8InputIndex = 0, bool keyout = false);
			HRESULT _SetupGenlockResolution(int sourceindex);
			HRESULT RegisterCallbackForWrite();
			HRESULT UnregisterCallback();

			HRESULT QueueFieldOrFrame(void *pvideo,void *paudio, void *pvideo1, void *paudio1,
				SMvVancPacket* in_paVancPackets, uint32_t in_ui32PacketCount);
			void _ProcessVanc(core::const_frame &frame);
			void _ProcessVanc1(core::const_frame &frame);
			void _ProcessVanc2();
			void get_top_frame(core::const_frame &frame, void **pvideo, void **pvideo1, void **paudio , void **paudio1);
			void get_second_frame(core::const_frame &frame, void **pvideo, void **pvideo1, void **paudio, void **paudio1);
			void get_frame(core::const_frame &frame, void **pvdeo, void **paudio);

		protected:
			virtual HRESULT __stdcall NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters);

		private:
			TMvSmartPtr<IMvOutputStream>    m_pJOutputStream;
			TMvSmartPtr<IMvNode>            m_pJCardNode;
			TMvSmartPtr<IMvHostNode>        m_pJHostNode;
			TMvSmartPtr<IMvTransferStream>  m_pJTransferStream;

			TMvSmartPtr<IMvVancDataPackets> m_pJVancDataPackets;
			
			tbb::concurrent_bounded_queue<transferconfig>	BuffersQueue;
			tbb::concurrent_bounded_queue<transferconfig>	FirstQueue;
			tbb::concurrent_bounded_queue<transferconfig>	SecondQueue;

			CMvCriticalSection m_oCriticalSection;
			std::shared_ptr<SwrContext>				swr_;
			std::shared_ptr<SwsContext>				sws_video;
			unsigned long m_ulSampleSize;
			uint32_t      m_ui32SurfacesToReceive;
			uint32_t      m_ui32AudioSamplesToReceive;
			int outindex;
			int sample_;
			int audio_rate_;
			int in_channel_;
			int out_channel_;
			bool vanc_output_;
			core::const_frame frame;
			int cout_;
		};
	}
}