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

#include "mvsOutputTopology.h"
#include "MatroxDSXsdkGuids.h"
#include "mvTime.h"
#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>
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

#define __STDC_FORMAT_MACROS
#define  FIRSTTOP 4;
namespace caspar {
	namespace matrox {
		// ----------------------------------------------------------------------------
		CmvsOutputTopology::CmvsOutputTopology(IMvSystemConfiguration *in_pISystemConfiguration,
			IMvCardConfiguration* in_pICardConfiguration,
			SMvResolutionInfo *in_pResolutionInfo,int outindex,
			int video_rate,
			int in_channel,
			int out_channel,
			int audio_rate,
			bool vanc_output)
			: CmvsBaseTopology(in_pISystemConfiguration, in_pICardConfiguration, in_pResolutionInfo)
			, CMvUnknown((L"CmvsOutputTopology"+boost::lexical_cast<std::wstring>(outindex)).c_str(), NULL)
			, m_ulSampleSize(0)
			, sample_(audio_rate / video_rate)
			, audio_rate_(audio_rate)
			, in_channel_(in_channel)
			, out_channel_(out_channel)
			,vanc_output_(vanc_output)
		{
			int intype = av_get_default_channel_layout(in_channel_);//AV_CH_LAYOUT_MONO
			int outtype = av_get_default_channel_layout(out_channel);//输入声道
			swr_ = {
				swr_alloc_set_opts( 
					nullptr,
					outtype,
					AV_SAMPLE_FMT_S32,
					audio_rate,
					intype ,
					AV_SAMPLE_FMT_S32,
					audio_rate,
					0,
					nullptr),
				[](SwrContext* p)
			{
				swr_free(&p);
			}
			};
			swr_init(swr_.get());
			BuffersQueue.set_capacity(8);//
			FirstQueue.set_capacity(4);
			SecondQueue.set_capacity(4);
			cout_ = FIRSTTOP;
		}

		// ----------------------------------------------------------------------------
		CmvsOutputTopology::~CmvsOutputTopology()
		{
		}

		HRESULT CmvsOutputTopology::RegisterCallbackForWrite()
		{
			return m_pJHostNode->RegisterCallbackForWrite(this);
		}

		HRESULT CmvsOutputTopology::UnregisterCallback()
		{
			CMvHResult oHr;
			oHr = m_pJHostNode->UnregisterWriteCallback(this);
			return oHr;
		}
		void CmvsOutputTopology::get_top_frame(core::const_frame &frame, void **pvideo,void **pvideo1, void **paudio,void **paudio1)
		{
			int width = frame.width();
			int height = frame.height();

			if (!sws_video)
			{
				sws_video.reset(
					sws_getContext(
						width,
						height,
						AV_PIX_FMT_BGRA,
						width,
						height,
						AV_PIX_FMT_YUYV422,
						SWS_BICUBIC,
						nullptr,
						nullptr,
						nullptr
					),
					sws_freeContext);
				if (sws_video == nullptr)
					BOOST_THROW_EXCEPTION(caspar::caspar_exception() << caspar::msg_info(L"Cannot initialize the conversion context"));
			}
			unsigned long ulSizeToRead = width * 2 *height;

			uint8_t *rgbbuf[1];
			uint8_t *outbuf[3];
			int inlinesize[1] = { width * 4 };//ROW BYTE
			int outlinesize[1] = { width * 2 };//ROW BYTE

			rgbbuf[0] = (uint8_t *)malloc(width*4*height);
			outbuf[0] = (uint8_t *)malloc(ulSizeToRead);
			
			tbb::parallel_for(0, height , 1, [&](int y)
			{
				caspar::fast_memcpy(
					reinterpret_cast<char*>(rgbbuf[0]) + y *width * 4,
					(frame.image_data().begin()) + y * width * 4,
					width * 4
				);
			});
			
			sws_scale(sws_video.get(), rgbbuf, inlinesize,
				0, height, outbuf, outlinesize);
			
			////场消隐
			//char pall_buf[96] = { 0 };
			//memset(pall_buf, 0, 96);
			void * pBuffer = (uint8_t*)malloc((width * 2 + 100)*height / 2);
			void * pBuffer1 = (uint8_t*)malloc((width * 2 + 100)*height / 2);
			uint8_t*p = (uint8_t*)pBuffer;
			uint8_t*p1 = (uint8_t*)pBuffer1;
			for (int i = 0;i < height;i++)
			{
				////场消隐
				//if (width == 720 && (height == 288 *2|| height == 243*2))
				//{
				//	if (i % 2)
				//	{
				//		memcpy(p1, outbuf[0] + i*width * 2, width * 2);
				//		p1 += width * 2;
				//		memcpy(p1, pall_buf, 96);
				//		p1 += 96;
				//	}
				//	else
				//	{
				//		memcpy(p, outbuf[0] + i*width * 2, width * 2);
				//		p += (width * 2);
				//		memcpy(p, pall_buf, 96);
				//		p += 96;
				//	}
				//}
				//else
				{
					if (i % 2)//second
					{
						memcpy(p1, outbuf[0] + i*width * 2, width * 2);
						p1+= width * 2;
					}
					else
					{
						memcpy(p, outbuf[0] + i*width * 2, width * 2);
						p += width * 2;
					}
				}
			}

			//audio
			int audio_frame_size = ((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);
			void * source = (char *)malloc(frame.audio_data().size() * 4);
			void * pAudioBuffer = (char *)malloc(out_channel_ * sample_ * 4);
			void * pAudioBuffer1= (char *)malloc(out_channel_ * sample_ * 2);
			int outsize = out_channel_ * sample_ * 4;
			caspar::array<const int32_t>::iterator it;

			it = frame.audio_data().begin();
			int* p_ch = (int *)source;
			for (int sample_no = 0; sample_no < frame.audio_data().size();sample_no++)
			{
				p_ch[sample_no] = (int)*it;
				if (*it != 0)
				{
					int s = *it;
				}
				it++;
			}
			const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&source);
			uint8_t *out[] = { reinterpret_cast<uint8_t*>((uint8_t*)pAudioBuffer) };

			const auto channel_samples = swr_convert(
				swr_.get(),
				out,
				outsize,
				in,
				sample_);

			memcpy(pAudioBuffer1, (uint8_t*)pAudioBuffer + out_channel_ * sample_ * 2, out_channel_ * sample_ * 2);
			*paudio = (uint8_t*)pAudioBuffer;
			*paudio1 = (uint8_t*)pAudioBuffer1;
			*pvideo1 = pBuffer1;
			*pvideo = pBuffer;
			free(source);
			free(rgbbuf[0]);
			free(outbuf[0]);
		}
		void CmvsOutputTopology::get_second_frame(core::const_frame &frame, void **pvideo, void **pvideo1, void **paudio, void **paudio1MO)
		{
			int width = frame.width();
			int height = frame.height();

			if (!sws_video)
			{
				sws_video.reset(
					sws_getContext(
						width,
						height,
						AV_PIX_FMT_BGRA,
						width,
						height,
						AV_PIX_FMT_YUYV422,
						SWS_BICUBIC,
						nullptr,
						nullptr,
						nullptr
					),
					sws_freeContext);
				if (sws_video == nullptr)
					BOOST_THROW_EXCEPTION(caspar::caspar_exception() << caspar::msg_info(L"Cannot initialize the conversion context"));
			}
			unsigned long ulSizeToRead = width * height / 2 * 4;//一半的高度
			uint8_t *rgbbuf[1];
			uint8_t *outbuf[3];
			int inlinesize[1] = { width * 4 };
			int outlinesize[1] = { width * 2 };

			rgbbuf[0] = (uint8_t *)malloc(width*height * 4);
			outbuf[0] = (uint8_t *)malloc(width*height * 2);

			tbb::parallel_for(0, height, 1, [&](int y)
			{
				caspar::fast_memcpy(
					reinterpret_cast<char*>(rgbbuf[0]) + y *width * 4,
					(frame.image_data().begin()) + y * width * 4,
					width * 4
				);
			});


			sws_scale(sws_video.get(), rgbbuf, inlinesize,
				0, height, outbuf, outlinesize);
			int j = 0;
			//场消隐
			//char pall_buf[96] = { 0 };
			//memset(pall_buf, 0, 96);
			void * pBuffer = (uint8_t*)malloc(width*height / 2 * 2);
			void * pBuffer1 = (uint8_t*)malloc(width*height / 2 * 2);
			//uint8_t*p = (uint8_t*)pBuffer;
			//uint8_t*p1 = (uint8_t*)pBuffer1;
			for (int i = 0;i < height;i++)
			{
				////场消隐
				//if (width == 720 && (height == 288 * 2 || height == 243 * 2))
				//{
				//	if (i % 2)
				//	{
				//		memcpy(p1, outbuf[0] + i*width * 2, width * 2);
				//		p1 += width * 2;
				//		memcpy(p1, pall_buf, 96);
				//		p1 += 96;
				//	}
				//	else
				//	{
				//		memcpy(p, outbuf[0] + i*width * 2, width * 2);
				//		p += (width * 2);
				//		memcpy(p, pall_buf, 96);
				//		p += 96;
				//	}
				//}
				//else
				{
					if (i % 2)//second
					{
						memcpy((uint8_t*)pBuffer1 + j*width * 2, outbuf[0] + i*width * 2, width * 2);
						j++;
					}
					else
						memcpy((uint8_t*)pBuffer + j*width * 2, outbuf[0] + i* width * 2, width * 2);
				}
			}

			//audio


			free(rgbbuf[0]);
			free(outbuf[0]);
		}
		void CmvsOutputTopology::get_frame(core::const_frame &frame, void **pvideo,void **paudio)
		{
			int width = frame.width();
			int height = frame.height();
			if (!sws_video)
			{
				sws_video.reset(
					sws_getContext(
						width,
						height,
						AV_PIX_FMT_BGRA,
						width,
						height,
						AV_PIX_FMT_YUYV422,
						SWS_BICUBIC,
						nullptr,
						nullptr,
						nullptr
					),
					sws_freeContext);
				if (sws_video == nullptr)
					BOOST_THROW_EXCEPTION(caspar::caspar_exception() << caspar::msg_info(L"Cannot initialize the conversion context"));
			}
			uint8_t *inbuf[1];
			uint8_t *outbuf[1];
			int inlinesize[1] = { width * 4 };
			int outlinesize[1] = { width * 2 };


			inbuf[0] = (uint8_t *)malloc(width*height * 4);
			outbuf[0] = (uint8_t *)malloc(width*height * 4);//全场逐行


			tbb::parallel_for(0, height, 1, [&](int y)
			{
				caspar::fast_memcpy(
					reinterpret_cast<char*>(inbuf[0]) + y *width * 4,
					(frame.image_data().begin()) + y * width * 4,
					width * 4
				);
			});

			sws_scale(sws_video.get(), inbuf, inlinesize,
				0, height, outbuf, outlinesize);
			*pvideo = outbuf[0];

			//audio
			int audio_frame_size = ((boost::iterator_range<const int32_t*>)frame.audio_data()).size() * sizeof(int32_t);
			void * source = (char *)malloc(frame.audio_data().size() * 4);
			void * pAudioBuffer = (char *)malloc(out_channel_ * sample_*4);
			int outsize = out_channel_ * sample_ * 4;
			caspar::array<const int32_t>::iterator it;

			it = frame.audio_data().begin();
			int* p_ch = (int *)source;
			for (int sample_no = 0; sample_no < frame.audio_data().size();sample_no++)
			{
				p_ch[sample_no] = (int)*it;
				if (*it != 0)
				{
					int s = *it;
				}
				it++;
			}
			const uint8_t **in = const_cast<const uint8_t**>((uint8_t**)&source);
			uint8_t *out[] = { reinterpret_cast<uint8_t*>((uint8_t*)pAudioBuffer) };

			const auto channel_samples = swr_convert(
				swr_.get(),
				out,
				outsize,
				in,
				sample_);
			*paudio = (uint8_t*)pAudioBuffer;


			free(source);
			free(inbuf[0]);
		}
		void CmvsOutputTopology::_ProcessVanc(core::const_frame &frame)//40ms
		{

			CMvHResult oHr;
			// Get the vanc packets from the host node.
			void * pvideo = NULL;
			void * pvideo1 = NULL;
			void * paudio = NULL;
			void * paudio1 = NULL;
			
			//逐行调用一次，隔行两次
			if (_IsFieldBased(m_sResolution))
			{

				get_top_frame(frame, &pvideo,&pvideo1,&paudio,&paudio1);
			}
			else
			{
				get_frame(frame, &pvideo,&paudio);
			}
			uint32_t in_ui32PacketCount = 1;
			SMvVancPacket in_paVancPackets;
			int nAR = 0;
			int nCmd = 0;
			if (frame.afd_command())
			{
				nAR=frame.afd_command()->afd_aspect_ratio_;
				nCmd=frame.afd_command()->afd_command_;
			}
			else
			{
				in_ui32PacketCount = 0;//如果不存在AFD的话需要设置成0。
			}
			
			if (in_ui32PacketCount>0)
			{
				/*in_paVancPackets.ui8DID = 65;
				in_paVancPackets.ui8DC = 8;
				in_paVancPackets.ui8SDIDorDBN = 5;
				in_paVancPackets.ui32LineNumber = 13;
				in_paVancPackets.aui16UDW[0] = 632;
				in_paVancPackets.aui16UDW[1] = 512;
				in_paVancPackets.aui16UDW[2] = 512;
				in_paVancPackets.aui16UDW[3] = 512;
				in_paVancPackets.aui16UDW[4] = 512;
				in_paVancPackets.aui16UDW[5] = 512;
				in_paVancPackets.aui16UDW[6] = 512;
				in_paVancPackets.aui16UDW[7] = 512;*/
			
				SMvAFDAndBarDataVancPacket sAFDAndBarPacket;
				oHr = m_pJVancDataPackets->TransformVancPacketToAFDAndBarDataPacket(&in_paVancPackets, &sAFDAndBarPacket);
				sAFDAndBarPacket.sAFD.bIs16by9AspectRatio = nAR ? false : true;
				sAFDAndBarPacket.sAFD.ui8AFDCode = nCmd;
				sAFDAndBarPacket.sBarData.bTopPresenceFlag = false;
				sAFDAndBarPacket.sBarData.bBottomPresenceFlag = false;
				sAFDAndBarPacket.sBarData.bLeftPresenceFlag = false;
				sAFDAndBarPacket.sBarData.bRightPresenceFlag = false;
				sAFDAndBarPacket.sBarData.uTopOrLeftBar.ui16LineNumberEndOfTopBar = 0;
				sAFDAndBarPacket.sBarData.uTopOrLeftBar.ui16PixelNumberEndOfLeftBar = 0;
				sAFDAndBarPacket.sBarData.uBottomOrRightBar.ui16LineNumberStartOfBottomBar = 0;
				sAFDAndBarPacket.sBarData.uBottomOrRightBar.ui16PixelNumberStartOfRightBar = 0;
				oHr = m_pJVancDataPackets->TransformAFDAndBarDataPacketToVancPacket(&sAFDAndBarPacket, 571, &in_paVancPackets);
				
				
			}
			QueueFieldOrFrame(pvideo, paudio, pvideo1, paudio1, &in_paVancPackets, in_ui32PacketCount);
		}
		HRESULT CmvsOutputTopology::_SetupGenlockResolution(int sourceindex)
		{
			HRESULT hr;

			// Get genlock interface.         
			TMvSmartPtr<IMvGenlockConfiguration>	pJGenlockConfig;

			hr = m_pJCardCfg->GetGenlockConfiguration(&pJGenlockConfig);

			// Get current genlock settings
			if SUCCEEDED(hr)
			{
				SMvGenlockSettings sCurrentGenlockSettings = { sizeof(sCurrentGenlockSettings) };
				hr = pJGenlockConfig->GetGenlockSettings(sCurrentGenlockSettings);

				// Set genlock source to external BB
				if SUCCEEDED(hr)
				{
					SMvGenlockSettings sNewGenlockSettings;
					sNewGenlockSettings = sCurrentGenlockSettings;

					sNewGenlockSettings.eGenlockSource = keGenlockSourceInternal;//需要配置
					sNewGenlockSettings.sResolution.eAspectRatio = m_sResolution.eAspectRatio;
					sNewGenlockSettings.sResolution.ulComponentBitCount = 8;
					sNewGenlockSettings.sResolution.eFrameRate = m_sResolution.eFrameRate;
					sNewGenlockSettings.bEnableTermination = true;

					
					sNewGenlockSettings.sResolution.ulHeight = m_sResolution.ulHeight;
					sNewGenlockSettings.sResolution.ulWidth = m_sResolution.ulWidth;
					sNewGenlockSettings.sResolution.eScanMode = m_sResolution.eScanMode;
					sNewGenlockSettings.ui32SourceIndex = 0;
					hr = pJGenlockConfig->SetGenlockSettings(sNewGenlockSettings);
				}
			}

			return hr;
		}
		// ----------------------------------------------------------------------------
		HRESULT CmvsOutputTopology::BuildTopology(const char *in_kszName, uint8_t in_ui8OutputIndex, bool keyout)
		{
			CMvHResult oHr;

			// Setup a genlock clock to match the clock used at the input. If the same clock is not used between the input 
			// and output, the timestamp computation for the output must be compensated because of the drift between 
			// the input and output clock. For this sample, just use the same clock.
			SetupClock(NULL);
			//_SetupGenlockResolution();
			// Create a new topology.
			std::wstring sname = L"ConsumerTopolopy" + boost::lexical_cast<std::wstring>((in_ui8OutputIndex));
			oHr = _CreateTopology(in_kszName);
			if (oHr.DidFail())
			{
				return oHr;
			}

			// Init node settings.
			SMvNodeSettings sNodeSettings;
			SMvNodeSettingsVideo sVideoSettings;
			SMvNodeSettingsAudio sAudioSettings;
			SMvNodeSettingsVanc  sVancSettings;
			//需要配置 keMvSurfaceFormatYUYV422 keMvSurfaceFormatYUAYVA4224
			sname = L"OutputHostNode" + boost::lexical_cast<std::wstring>((in_ui8OutputIndex));
			if (keyout)
			{
				_InitNodeSettings(u8(sname).c_str(), keMvSurfaceFormatYUAYVA4224, &sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings);
			}
			else
				_InitNodeSettings(u8(sname).c_str(), keMvSurfaceFormatYUYV422, &sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings);
			switch (out_channel_)
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
			// Create host node.
			oHr = m_pJTopology->CreateHostNode(sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings, &m_pJHostNode);
			if (oHr.DidFail())
			{
				return oHr;
			}
			// Create card node.
			sname = L"OutputCardNode" + boost::lexical_cast<std::wstring>((in_ui8OutputIndex));
			
			strcpy(sNodeSettings.szName ,u8(sname).c_str());
			oHr = m_pJTopology->CreateCardNode(sNodeSettings, &sVideoSettings, &sAudioSettings, &sVancSettings, NULL, &m_pJCardNode);
			if (oHr.DidFail())
			{
				return oHr;
			}

			// Create the transfer stream.
			SMvTransferStreamSettings sTransferSettings = { sizeof(SMvTransferStreamSettings), 0 };
			sname = L"TransferStream" + boost::lexical_cast<std::wstring>((in_ui8OutputIndex));
			oHr = m_pJTopology->CreateTransferStream(u8(sname).c_str(), m_pJHostNode, m_pJCardNode, keMvTransferDirectionHostToCard, sTransferSettings, &m_pJTransferStream);
			if (oHr.DidFail())
			{
				return oHr;
			}

			// Get output stream settings.
			SMvOutputStreamSettings sOutStreamSettings;

			_InitOutputStreamSettings(sOutStreamSettings);

			int nNumberOfConnectors = 1;

			TMvSmartPtr<IMvSdiVideoOutputConnector> pJSdiVideoOutputConnector0 = NULL;
			TMvSmartPtr<IMvSdiVideoOutputConnector> pJSdiVideoOutputConnector1 = NULL;
			TMvSmartPtr<IMvSdiVideoOutputConnector> pJSdiVideoOutputConnector2 = NULL;
			TMvSmartPtr<IMvSdiVideoOutputConnector> pJSdiVideoOutputConnector3 = NULL;

			// QuadHD
			if (sVideoSettings.sResInfo.ulWidth >= 3840)
			{
				nNumberOfConnectors = 4;

				// Get video output connectors
				oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector0, 0);
				if (oHr.DidFail())
				{
					printf("Cannot find Video Output Connector 1...\n");
					return oHr;
				}

				oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector1, 1);
				if (oHr.DidFail())
				{
					printf("Cannot find Video Output Connector 2...\n");
					return oHr;
				}

				oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector2, 2);
				if (oHr.DidFail())
				{
					printf("Cannot find Video Output Connector 3...\n");
					return oHr;
				}

				oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector3, 3);
				if (oHr.DidFail())
				{
					printf("Cannot find Video Output Connector 4...\n");
					return oHr;
				}

				// Set up quadrant
				sOutStreamSettings.aeVideoConnectorPosition[0] = keMvQuadrantTopLeft;
				sOutStreamSettings.aeVideoConnectorPosition[1] = keMvQuadrantTopRight;
				sOutStreamSettings.aeVideoConnectorPosition[2] = keMvQuadrantBottomLeft;
				sOutStreamSettings.aeVideoConnectorPosition[3] = keMvQuadrantBottomRight;
			}
			else
			{
				if (keyout)
				{
					oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector0, in_ui8OutputIndex);
					if (oHr.DidFail())
					{
						printf("Cannot find any Video Output Connectors...\n");
						return oHr;
					}
					oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector1, in_ui8OutputIndex + 1);
					if (oHr.DidFail())
					{
						printf("Cannot find any Video Output Connectors...\n");
						return oHr;
					}
					nNumberOfConnectors = 1;
				}
				else
				{
					oHr = _GetVideoOutputConnector(&pJSdiVideoOutputConnector0, in_ui8OutputIndex);
					if (oHr.DidFail())
					{
						printf("Cannot find any Video Output Connectors...\n");
						return oHr;
					}
				}
				
				
				
			}

			IMvVideoOutputConnector* apIVideoOutConnector[4] = { pJSdiVideoOutputConnector0, pJSdiVideoOutputConnector1,
													pJSdiVideoOutputConnector2, pJSdiVideoOutputConnector3 };
			// Create the output stream.
			sname = L"OutputStream" + boost::lexical_cast<std::wstring>((int)in_ui8OutputIndex);
			oHr = m_pJTopology->CreateOutputStream(u8(sname).c_str(),
				m_pJCardNode,
				sVideoSettings.sResInfo,
				sOutStreamSettings,
				apIVideoOutConnector, nNumberOfConnectors,
				&m_pJOutputStream);
			if (oHr.DidSucceed())
			{
				EMvAudioPair aeAudioPair[8] = { keAudioPair0, keAudioPair1, keAudioPair2, keAudioPair3,
				   keAudioPair4, keAudioPair5, keAudioPair6, keAudioPair7 };
				oHr = pJSdiVideoOutputConnector0->SetSourceOutputStreamAndAudioPairs(m_pJOutputStream, aeAudioPair, 8);
				if (!oHr.DidSucceed())
				{
					return oHr;
				}
			}
			else
				return oHr;

			// Get vanc data packets interface from host node.
			oHr = m_pJHostNode->QueryInterface(IID_IMvVancDataPackets, (void**)&m_pJVancDataPackets);
			if (!oHr.DidSucceed())
			{
				LogError(oHr, "m_pJHostNode QueryInterface failed");
				return oHr;
			}
			if (vanc_output_)
			{
				oHr = m_pJVancDataPackets->EnableVancDataPackets();
				if (!oHr.DidSucceed())
				{
					LogError(oHr, "m_pJHostNode enable vanc data packet failed");
				}
			}
			return oHr;
		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsOutputTopology::QueueFieldOrFrame(void * pvideo, void * paudio,void*pvideo1,void *paudio1,
			SMvVancPacket* in_paVancPackets, uint32_t in_ui32PacketCount)
		{
			CMvHResult oHr;
			//寄场
			transferconfig sOutputBuffers;
			sOutputBuffers.pVideoBuffer = (uint8_t*)pvideo;
			sOutputBuffers.pAudioBuffer = (uint8_t*)paudio;
			sOutputBuffers.secondfiel = false;
			sOutputBuffers.RowPitchInbytes = m_sResolution.ulWidth * 2;
			if (!_IsFieldBased(m_sResolution))
			{
				in_paVancPackets[0].ui32LineNumber = 9;
				sOutputBuffers.in_paVancPackets = in_paVancPackets[0];
				sOutputBuffers.in_ui32PacketCount = in_ui32PacketCount;
				BuffersQueue.push(sOutputBuffers);
				
				return oHr;
			}
			//in_paVancPackets[0].ui32LineNumber = 13;
			sOutputBuffers.in_paVancPackets= in_paVancPackets[0];
			sOutputBuffers.in_ui32PacketCount = in_ui32PacketCount;

			
			BuffersQueue.push(sOutputBuffers);
			//偶场
			sOutputBuffers.secondfiel = true;
			//in_paVancPackets[0].ui32LineNumber = 9;
			sOutputBuffers.pVideoBuffer = (uint8_t*)pvideo1;
			sOutputBuffers.pAudioBuffer = (uint8_t*)paudio1;
			sOutputBuffers.in_paVancPackets = in_paVancPackets[0];
			sOutputBuffers.in_ui32PacketCount = in_ui32PacketCount;
			
			
			BuffersQueue.push(sOutputBuffers);
			
			return oHr;
		}
		

		HRESULT CmvsOutputTopology::NotifyForBufferAccess(const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters)
		{
			CMvHResult oHr;
			
			transferconfig lp;
			if (cout_>0)
			{
				cout_--;
				return MV_NOERROR;
			}
			BuffersQueue.pop(lp);
			if(MvGetSampleForNanoTime(in_krsNotificationParameters.ui64Timestamp, m_sResolution)%2==1)//偶场
			{
				if(lp.secondfiel)//偶场
				{
					for (int i = 0;i<in_krsNotificationParameters.ui32VideoHeight;i++)
					{
						memcpy(in_krsNotificationParameters.pVideoBuffer+i*in_krsNotificationParameters.ui32VideoRowPitchInBytes, (unsigned char *)lp.pVideoBuffer + i*lp.RowPitchInbytes , lp.RowPitchInbytes);
					}
					//memcpy(in_krsNotificationParameters.pVideoBuffer, lp.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					memcpy(in_krsNotificationParameters.pAudioBuffer, lp.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
					//if (lp.in_ui32PacketCount&&vanc_output_)
					//{
					//	uint64_t ui64OutputTimeInVideoUnits = MvGetSampleForNanoTime(m_pJClock->GetTime(), m_sResolution);
					//	ui64OutputTimeInVideoUnits += _IsFieldBased(m_sResolution) ? 6 : 3;
					//	uint64_t ui64OutputTimestamp = MvGetNanoTimeForSample(ui64OutputTimeInVideoUnits, m_sResolution);

					//	//oHr = m_pJVancDataPackets->SetVancPacketsField(in_krsNotificationParameters.ui64Timestamp, &lp.in_paVancPackets, lp.in_ui32PacketCount);
					//	oHr = m_pJVancDataPackets->SetVancPacketsField(ui64OutputTimestamp, &lp.in_paVancPackets, lp.in_ui32PacketCount);
					//	if (!oHr.DidSucceed())
					//	{
					//		CASPAR_LOG(info) << L"*";
					//	}
					//	if (oHr == MV_E_NOT_AVAILABLE)
					//	{
					//		CASPAR_LOG(info) << L"+";
					//	}
					//	if (oHr == MV_E_MAX_VALUE_REACHED)
					//	{
					//		CASPAR_LOG(info) << L"-";
					//	}
					//	if (oHr == MV_E_INCOMPATIBLE_SCAN_MODE)
					//	{
					//		CASPAR_LOG(info) << L"$";
					//	}
					//}
				}
				else
				{
					free(lp.pAudioBuffer);
					free(lp.pVideoBuffer);
					BuffersQueue.pop(lp);//丢一个
					
				}
			}else
			{
				if (!lp.secondfiel)
				{
					//memcpy(in_krsNotificationParameters.pVideoBuffer, lp.pVideoBuffer, in_krsNotificationParameters.ui32VideoRowPitchInBytes*in_krsNotificationParameters.ui32VideoHeight);
					for (int i = 0;i < in_krsNotificationParameters.ui32VideoHeight;i++)
					{
						memcpy(in_krsNotificationParameters.pVideoBuffer + i*in_krsNotificationParameters.ui32VideoRowPitchInBytes, (char *)lp.pVideoBuffer + i * lp.RowPitchInbytes, lp.RowPitchInbytes);
					}
					memcpy(in_krsNotificationParameters.pAudioBuffer, lp.pAudioBuffer, in_krsNotificationParameters.ui32AudioSize);
					if (lp.in_ui32PacketCount&&vanc_output_)
					{
						uint64_t ui64OutputTimeInVideoUnits = MvGetSampleForNanoTime(m_pJClock->GetTime(), m_sResolution);
						ui64OutputTimeInVideoUnits += _IsFieldBased(m_sResolution) ? 6 : 3;
						uint64_t ui64OutputTimestamp = MvGetNanoTimeForSample(ui64OutputTimeInVideoUnits, m_sResolution);
						// Send vanc to host node.
						if (_IsFieldBased(m_sResolution))
						{

							//oHr = m_pJVancDataPackets->SetVancPacketsField(in_krsNotificationParameters.ui64Timestamp, &lp.in_paVancPackets, lp.in_ui32PacketCount);
							oHr = m_pJVancDataPackets->SetVancPacketsField(ui64OutputTimestamp, &lp.in_paVancPackets, lp.in_ui32PacketCount);

							if (!oHr.DidSucceed())
							{
								CASPAR_LOG(info) << L"*";
							}
							if (oHr == MV_E_NOT_AVAILABLE)
							{
								CASPAR_LOG(info) << L"+";
							}
							if (oHr == MV_E_MAX_VALUE_REACHED)
							{
								CASPAR_LOG(info) << L"-";
							}
							if (oHr == MV_E_INCOMPATIBLE_SCAN_MODE)
							{
								CASPAR_LOG(info) << L"$";
							}
						}
						else
						{
							//m_pJVancDataPackets->SetVancPacketsFrame(in_krsNotificationParameters.ui64Timestamp, &lp.in_paVancPackets, lp.in_ui32PacketCount);
							m_pJVancDataPackets->SetVancPacketsFrame(ui64OutputTimestamp, &lp.in_paVancPackets, lp.in_ui32PacketCount);
						}
					
					}
					
				}
				else
				{
					free(lp.pAudioBuffer);
					free(lp.pVideoBuffer);
					BuffersQueue.pop(lp);//丢一个
					
				}
			}

			free(lp.pAudioBuffer);
			free(lp.pVideoBuffer);
			return MV_NOERROR;
		}
	}
}