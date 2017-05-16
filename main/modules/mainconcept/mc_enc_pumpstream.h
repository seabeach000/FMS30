#pragma once

extern "C"
{
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <libswresample/swresample.h>
}

#include "params.h"
#include "DtNetRender.h"

#include "MCNetRender.h"
#include <enc_mp2v.h>
#include <enc_mpa.h>

#include <enc_avc.h>
#include <enc_aac.h>
#include <enc_pcm.h>

#include <mux_mp2.h>
#include "bufstream/buf_fifo.h"

#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include <core/frame/frame.h>
#include <core/video_format.h>
#include <core/frame/audio_channel_layout.h>

////////////////////////////////////////////////////////////////////////////////////
// Standard output functions.
void info_printf(const char * fmt, ...);
//
void warn_printf(const char * fmt, ...);
void error_printf(const char * fmt, ...);
void progress_printf(int32_t percent, const char * fmt, ...);
// resource functions dispatcher
void * MC_EXPORT_API get_rc(const char* name);

/**
* @brief AUXinfo handler type.
**/
typedef uint32_t(*auxinfo_handler_t)(bufstream_tt * bs, uint32_t offs, uint32_t info_id, void * info_ptr, uint32_t info_size);

/**
* @brief Extern original AUXinfo function.
**/
extern auxinfo_handler_t org_auxinfo;
/**
* @brief Encoder auxinfo handler
* @param[in] bs                  - Pointer to bufstream
* @param[in] offs                - offsets
* @param[in] info_id             - Information ID (TIME_STAMP_INFO,STATISTIC_INFO,VIDEO_AU_CODE,ID_PICTURE_START_CODE ...)
* @param[in] info_ptr            - Pointer to information data
* @param[in] info_size           - Size of information data
* @return     result of original auxinfo function
*/
uint32_t auxinfo(bufstream_tt * bs, uint32_t offs, uint32_t info_id, void * info_ptr, uint32_t info_size);
/////////////////////////////////////////////////////////////////////////////////////
namespace caspar {
	namespace mainconcept {

		struct mc_enc_pumpstream
		{
		public:
			mc_enc_pumpstream(const core::video_format_desc& format_desc,
				const core::audio_channel_layout& in_channel_layout, bool is_output_stream);
			~mc_enc_pumpstream();
		public:
			bool initialize(std::map<std::string, std::string>& options, 
				std::string path);
			void encode_video(core::const_frame &frame);
			void encode_audio(core::const_frame &frame);
		private:
			void set_params(std::map<std::string, std::string>& options);
			bool pathparse(std::string path, net_path_params& netparams);
			
			int32_t get_video_frame_size(int32_t w, int32_t h, uint32_t cs_fourcc, int32_t * linesize, int32_t * imgstart);
			bool get_video_enc_type(std::string vcodec = "");
			bool get_audio_enc_type(std::string acodec = "");
			bool get_muxer_type(std::string muxer = "");
			bool get_netrender_type(std::string netrender = "");

			bool init_h264_encoder(); 
			bool init_mpeg2_encoder(); 
			bool init_mpa_encoder(); 
			bool init_aac_encoder();
			bool init_pcm_encoder(); 
			bool init_mpeg_muxer();
			bool init_mc_netrender(std::string path);//mcnetrender
			bool init_dt_netrender(std::string path); //dektecnetrender

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
			NETRENDER netrender_type;
			//
			acodec_params a_enc_params;
			vcodec_params v_enc_params;
			muxer_params  mux_params;
			dtnetrender_params dt_params;
			//vcodec
			h264venc_tt*   v_enc_h264 = nullptr; 
			mpegvenc_tt *     v_enc_mp2v = nullptr; 
			//acodec
			mpegaenc_tt* a_enc_mpa = nullptr;
			aacaenc_tt*  a_enc_aac = nullptr;
			pcmaenc_tt*  a_enc_pcm = nullptr;
			//mux
			mp2muxer_tt *mp2muxer = nullptr; 
			//netrender
			MCNetRender*   mcrender = nullptr;
			CDtNetRender* dtrender = nullptr;

			//buffer
			fifo_stream_tt *videobs = nullptr;
			fifo_stream_tt *audiobs = nullptr;
			fifo_stream_tt *muxerbs = nullptr;
			bufstream_tt   *filebs = nullptr;
		private:
			tbb::atomic<bool>						is_running_;
			boost::thread							thread_;
			void pushstream();

		private:			
			template<typename T>
			static boost::optional<T> try_remove_arg(
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

