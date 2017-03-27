#pragma once

extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libswresample/swresample.h>
}

#include <string>

#include "enc_avc.h"
#include "enc_mp2v.h"
#include "enc_mpa.h"
#include "enc_aac.h"
#include "enc_pcm.h"

#include "mux_mp2.h"
#include "net_renderer.h"
#include "bufstream/buf_fifo.h"

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include <core/frame/frame.h>
#include <core/video_format.h>
#include <core/frame/audio_channel_layout.h>
using namespace MainConcept::NetworkStreaming;

#define ITEM_NOT_INIT -123456

////////////////////////////////////////////////////////////////////////////////////
// Standard output functions.
void info_printf(const char * fmt, ...);
//
void warn_printf(const char * fmt, ...);
void error_printf(const char * fmt, ...);
void progress_printf(int32_t percent, const char * fmt, ...);
// resource functions dispatcher
void * MC_EXPORT_API get_rc(const char* name);

////////////////////////////////////////////////////////////////////////////////////
class SenderNotifier : public ISenderNotifier
{
public:
	SenderNotifier();
	~SenderNotifier();
public:
	virtual void OnConfigChanged(void *pData, uint32_t *uiDataLen);
	virtual void OnPacketSend(bool bMarker, uint32_t aBytesSent, int64_t i64TimeStamp, uint32_t uiSamplesCount);
};


/////////////////////////////////////////////////////////////////////////////////////
namespace caspar {
	namespace mainconcept {
		enum VIDEOENC
		{
			VIDEOENC_MPEG2,
			VIDEOENC_H264,
			VIDEOENC_UNKNOWN
		};

		enum AUDIOENC
		{
			AUDIOENC_MPA,
			AUDIOENC_AAC,
			AUDIOENC_PCM,
			AUDIOENC_UNKNOWN
		};

		enum MUXER
		{
			MUXER_MPEGTS,
			MUXER_UNKNOWN
		};

		//vcodec params
		struct vcodec_params
		{
			/*
			*for H264£º2-H264_MAIN 5-H264_HIGH
			*for mpeg2£º2-MPEG_MPEG2
			*/
			int32_t     preset		=	ITEM_NOT_INIT;	
			int32_t		profile		=	ITEM_NOT_INIT;
			int32_t     level		=   ITEM_NOT_INIT;
			/*
			*for H264£º 0-H264_PERF_FASTEST    9-H264_PERF_BALANCED   15-H264_PERF_BEST_Q  ,default 9
			*for mpeg2: 0~31,  default 15
			*/
			int32_t     perf		=   ITEM_NOT_INIT; 
			/*
			*for H264£º 0-H264_PROGRESSIVE  1-H264_INTERLACED  2-H264_MBAFF 
			*for mpeg2£º0-interlaced        1-progressive 
			*/
			int32_t     frame_type	=	ITEM_NOT_INIT; 
			/*
			*for h264£º  0-top field first      1-bottom field first  
			*for mpeg2£º 1-top field first      0-bottom field first   
			*/
			int32_t     field_order =	ITEM_NOT_INIT;    
			double      frame_rate	=	ITEM_NOT_INIT;

			int32_t     gop_size	=   ITEM_NOT_INIT;
			int32_t     b_frames    =	ITEM_NOT_INIT;
			/*
			*for H264£º0-H264_CBR        1-H264_CQT      2-H264_VBR  3-H264_TQM         4-H264_INTRARC  
			*for mpeg2£º0-VBR_VARIABLE1  1-VBR_CONSTANT  2-VBR_CQT   3-VBR_CQT_STRICT
			*/
			int32_t     bit_rate_mode	=	ITEM_NOT_INIT;
			int32_t     bit_rate	=   ITEM_NOT_INIT;
		}; 

		//acodec params
		struct acodec_params
		{
			//common
			/*
			*for MPEG-1 layer 2:1~14; 1-3¡¢5 for mono, 11-14 not for mono, default 12-L2_AUDIOBITRATE256 
			*for AAC :  1~31 ,default 19-AAC_AUDIOBITRATE_128
			*/
			int32_t bit_rate_index = ITEM_NOT_INIT;

			//mpa param
			int32_t audio_layer	= ITEM_NOT_INIT; 
			int32_t audio_mode	= ITEM_NOT_INIT; 

			//aac param	
			int32_t mpeg_version = ITEM_NOT_INIT;
			//int32_t aac_object_type = ITEM_NOT_INIT;
			int32_t header_type = ITEM_NOT_INIT;
			int32_t he = ITEM_NOT_INIT;
			int32_t vbr = ITEM_NOT_INIT;
		};

		//muxer params
		struct muxer_params
		{
			int32_t enabled_paddings = ITEM_NOT_INIT;
			int32_t required_bitrate = ITEM_NOT_INIT;
			int32_t PCR_repetition_rate = ITEM_NOT_INIT;
			int32_t PSI_repetition_rate = ITEM_NOT_INIT;
			int32_t video_pid  = ITEM_NOT_INIT;
			int32_t audio_pid  = ITEM_NOT_INIT;
		};

		//netrenderer params;
		struct net_params
		{
			std::string protocol;
			std::string ipAddr;
			int32_t port;
			std::string localAddr;
		};

		struct mc_enc_pumpstream
		{
		public:
			mc_enc_pumpstream(const core::video_format_desc& format_desc,
				const core::audio_channel_layout& in_channel_layout, bool is_output_stream);
			~mc_enc_pumpstream();
		public:
			bool initialize(std::map<std::string, std::string>& options, 
				std::string path);
			bool pushframe(core::const_frame &frame);
		private:
			void set_params(std::map<std::string, std::string>& options);
			bool pathparse(std::string path, net_params& netparams);
			
			int32_t get_video_frame_size(int32_t w, int32_t h, uint32_t cs_fourcc, int32_t * linesize, int32_t * imgstart);
			bool get_video_enc_type(std::string vcodec = "");
			bool get_audio_enc_type(std::string acodec = "");
			bool get_muxer_type(std::string muxer = "");

			bool init_h264_encoder(); 
			bool init_mpeg2_encoder(); 
			bool init_mpa_encoder(); 
			bool init_aac_encoder();
			bool init_pcm_encoder(); 
			bool init_mpeg_muxer();
			bool init_net_renderer(std::string path);//mcrender

		private:
			bool is_output_stream_;//true-output_stream  false-record_file
			core::video_format_desc					format_desc_;
			const core::audio_channel_layout		in_channel_layout_;
			std::shared_ptr<SwrContext>				swr_;

			//src
			int32_t  width;
			int32_t  height;
			int32_t  fourcc;
			int32_t	 line_size;
			int32_t  img_start;
			int32_t  video_frame_size;
			int32_t  audio_sample_rate;

			//
			VIDEOENC v_enc_type;
			AUDIOENC a_enc_type;
			MUXER    muxer_type;
			//
			acodec_params a_enc_params;
			vcodec_params v_enc_params;
			muxer_params  mux_params;
			//vcodec
			h264venc_tt*   v_enc_h264 = nullptr; 
			mpegvenc_tt *     v_enc_mp2v = nullptr; 
			//acodec
			mpegaenc_tt* a_enc_mpa = nullptr;
			aacaenc_tt*  a_enc_aac = nullptr;
			pcmaenc_tt*  a_enc_pcm = nullptr;
			//mux
			mp2muxer_tt *mp2muxer = nullptr; 
			//netrenderer
			IBaseSender * pSender = nullptr;
			SenderNotifier* pSenderNotifier = nullptr;

			//buffer
			fifo_stream_tt *videobs = nullptr;
			fifo_stream_tt *audiobs = nullptr;
			fifo_stream_tt *muxerbs = nullptr;
			bufstream_tt   *filebs = nullptr;
		private:
			tbb::atomic<bool>						is_running_;
			boost::thread							thread_;
			void pushstream();

		private:			template<typename T>
			static boost::optional<T> mc_enc_pumpstream::try_remove_arg(
				std::map<std::string, std::string>& options,
				const boost::regex& expr)
			{
				for (auto it = options.begin(); it != options.end(); ++it)
				{
					if (boost::regex_search(it->first, expr))
					{
						auto arg = it->second;
						options.erase(it);
						return boost::lexical_cast<T>(arg);
					}
				}
				return boost::optional<T>();
			}
		};
	}
}

