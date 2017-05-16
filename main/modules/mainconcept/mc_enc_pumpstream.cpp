#include "mc_enc_pumpstream.h"
#include "enc_avc_def.h"
#include <mcfourcc.h>
#include <mccolorspace.h>
#include "bufstream/buf_file.h"
#include <auxinfo.h>

#include <string>

#include <tbb/parallel_for.h>
#include <common/memcpy.h>

//////////////////////////////////////////////////////
void info_printf(const char * fmt, ...)
{
	char lst[1024];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(info) << lst;
}


void warn_printf(const char * fmt, ...)
{
	char lst[2048];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(warning) << lst;
}


void error_printf(const char * fmt, ...)
{
	char lst[256];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(error) << lst;
}


void progress_printf(int32_t percent, const char * fmt, ...)
{
	char lst[256];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(info) << percent << L" - " << lst;
}



void* mmalloc(size_t _Size) {
	return malloc(_Size);
}
void mfree(void* _Block) {
	free(_Block);
}
// resource functions dispatcher
void * MC_EXPORT_API get_rc(const char* name)
{
	if (!strcmp(name, "err_printf"))
		return (void*)error_printf;
	else if (!strcmp(name, "prg_printf"))
		return (void*)progress_printf;
	else if (!strcmp(name, "wrn_printf"))
		return (void*)warn_printf;
	else if (!strcmp(name, "inf_printf"))
		return (void*)info_printf;
	else if (!strcmp(name, "malloc"))
		return (void*)mmalloc;
	else if (!strcmp(name, "free"))
		return (void*)mfree;

	return nullptr;
}

auxinfo_handler_t org_auxinfo;
// encoder auxinfo handler
uint32_t auxinfo(bufstream_tt * bs, uint32_t offs, uint32_t info_id, void * info_ptr, uint32_t info_size)
{
	//sample_info_struct * sample_info;
	encode_stat_struct * encode_stat;
	//v_au_struct * vau;
	//pic_start_info *ref_pic_info;

	switch (info_id)
	{
// 	case TIME_STAMP_INFO:
// 		sample_info = (sample_info_struct *)info_ptr;
// 		break;
// 
	case STATISTIC_INFO:
		encode_stat = (encode_stat_struct *)info_ptr;
// 		if (0 == encode_stat->frames_encoded % 25 )
// 		{
// 			CASPAR_LOG(info)<< encode_stat->frames_incoming - encode_stat->frames_encoded <<L" "<< encode_stat->average_speed << L" fps";
// 		}
		break;
// 
// 	case VIDEO_AU_CODE:
// 		vau = (v_au_struct *)info_ptr;
// 		break;
// 
// 	case ID_PICTURE_START_CODE:
// 		ref_pic_info = (pic_start_info*)info_ptr;
// 		pic_info = *ref_pic_info;
// 		break;
	case MUX_STATISTIC_INFO:
		mpgmux_stat_struct* mux_info = (mpgmux_stat_struct*)info_ptr;
		CASPAR_LOG(info) << L"mux info :" << mux_info->num_units_queued_v << L" " << mux_info->video_underflows;
		break;
	}

	// call original auxinfo handler
	return org_auxinfo(bs, offs, info_id, info_ptr, info_size);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace caspar {
	namespace mainconcept {
		mc_enc_pumpstream::mc_enc_pumpstream(const core::video_format_desc& format_desc,
			const core::audio_channel_layout& in_channel_layout, bool is_output_stream)
			:format_desc_(format_desc)
			,in_channel_layout_(in_channel_layout)
			,is_output_stream_(is_output_stream)
		{
			//32bit transfer to 16bit
			int intype = static_cast<int>(av_get_default_channel_layout(in_channel_layout_.num_channels));
			int outtype = static_cast<int>(av_get_default_channel_layout(in_channel_layout_.num_channels));
			swr_ = {
				swr_alloc_set_opts(
					nullptr,
					outtype,
					AV_SAMPLE_FMT_S16,
					format_desc_.audio_sample_rate,
					intype ,
					AV_SAMPLE_FMT_S32,    
					format_desc_.audio_sample_rate,
					0,
					nullptr),
				[](SwrContext* p)
			{
				swr_free(&p);
			}
			};
			swr_init(swr_.get());

			//default
			v_enc_type = VIDEOENC_H264;
			a_enc_type = AUDIOENC_MPA; 
			muxer_type = MUXER_MPEGTS; 
			netrender_type = NETRENDER_MC;

			//video src
			width = format_desc_.width;
			height = format_desc.height;
			fourcc = FOURCC_BGRA;
			video_frame_size = get_video_frame_size(width, height, fourcc, &line_size, &img_start);
			audio_sample_rate = format_desc_.audio_sample_rate;
		}


		mc_enc_pumpstream::~mc_enc_pumpstream()
		{
			is_running_ = false;
			thread_.join();
			if (v_enc_h264)
			{
				h264OutVideoDone(v_enc_h264, 0);
				h264OutVideoFree(v_enc_h264);
			}
			if (v_enc_mp2v)
			{
				mpegOutVideoDone(v_enc_mp2v, 0);
				mpegOutVideoFree(v_enc_mp2v);
			}
			if (a_enc_mpa)
			{
				mpegOutAudioDone(a_enc_mpa, 0);
				mpegOutAudioFree(a_enc_mpa);
			}
			if (a_enc_aac)
			{
				aacOutAudioDone(a_enc_aac, 0);
				aacOutAudioFree(a_enc_aac);
			}
			if (a_enc_pcm)
			{
				pcmOutAudioDone(a_enc_pcm, 0);
				pcmOutAudioFree(a_enc_pcm);
			}
			if (mp2muxer)
			{
				mpegOutMP2MuxDone(mp2muxer, 0);
				mpegOutMP2MuxFree(mp2muxer);
			}
			if (mcrender)
			{
				delete mcrender;
				mcrender = nullptr;
			}
			if (dtrender)
			{
				delete dtrender;
				dtrender = nullptr;
			}

			if (videobs)
			{
				free_fifo_buf(videobs);
			}
			if (audiobs)
			{
				free_fifo_buf(audiobs);
			}
			if (muxerbs)
			{
				free_fifo_buf(muxerbs);
			}
			if (filebs)
			{
				close_file_buf(filebs, 0);
			}
		}

		bool mc_enc_pumpstream::initialize(std::map<std::string, std::string>& options,
			std::string path)
		{
			//buffer
			videobs = new_fifo_buf(video_frame_size * 4, video_frame_size);
			audiobs = new_fifo_buf(1920 * 32 * 4, 1920 * 32);
			if (is_output_stream_)
			{
				muxerbs = new_fifo_buf(16 * 1024 * 1024, 4 * 1024 * 1024);
			}
			else
			{
				filebs = open_file_buf_write((u16(path)).c_str(), 1024 * 1024 * 100, nullptr);
			}

			//vcodec
			const auto video_codec_name =
				try_remove_arg<std::string>(
					options,
					boost::regex("^c:v|codec:v|vcodec$"));

			if (!(video_codec_name ? get_video_enc_type(video_codec_name->c_str()): get_video_enc_type(""))) return false;

			//acodec
			const auto audio_codec_name =
				try_remove_arg<std::string>(
					options,
					boost::regex("^c:a|codec:a|acodec$"));
			if (!(audio_codec_name ? get_audio_enc_type(audio_codec_name->c_str()) : get_audio_enc_type(""))) return false;

			//format
			const auto oformat_name =
				try_remove_arg<std::string>(
					options,
					boost::regex("^f|format$"));
			if (!(oformat_name ? get_muxer_type(oformat_name->c_str()) : get_muxer_type(""))) return false;

			//netrender
			if (is_output_stream_)
			{
				const auto render_name =
					try_remove_arg<std::string>(
						options,
						boost::regex("netrender$"));
				if (!(render_name ? get_netrender_type(render_name->c_str()) : get_netrender_type(""))) return false;

			}


			//params
			set_params(options);

			//video encoder
			switch (v_enc_type)
			{
			case VIDEOENC_H264:
				if (false == init_h264_encoder())	{return false;}
				break;
			case VIDEOENC_MPEG2:
				if (false == init_mpeg2_encoder()) { return false; }
				break;
			case VIDEOENC_UNKNOWN:
			default:
				return false;
			}

			//audio encoder
			switch (a_enc_type)
			{
			case AUDIOENC_MPA:
				if (false == init_mpa_encoder()) { return false; }
				break;
			case AUDIOENC_AAC:
				if (false == init_aac_encoder()) { return false; }
				break;
			case AUDIOENC_PCM:
				if (false == init_pcm_encoder()) { return false; }
				break;
			case AUDIOENC_UNKNOWN:
			default:
				return false;
			}

			//muxer
			switch(muxer_type)
			{
			case MUXER_MPEGTS:
				if (false == init_mpeg_muxer()) { return false; }
				break;
			case MUXER_UNKNOWN:
			default:
				return false;
			}

			if (is_output_stream_)
			{
				//netrender
				switch (netrender_type)
				{
				case NETRENDER_MC:
					if (false == init_mc_netrender(path)) { return false; }
					break;
				case NETRENDER_DT:
					if (false == init_dt_netrender(path)) { return false; }
					break;
				case NETRENDER_UNKNOWN:
				default:
					return false;
				}

				is_running_ = true;
				//push stream thread
				thread_ = boost::thread([this] {pushstream(); });
			}

			return true;
		}

		void mc_enc_pumpstream::set_params(std::map<std::string, std::string>& options)
		{
			auto it = options.begin();
			while (it != options.end())
			{
				//video
				if (it->first == "vpreset")
				{
					v_enc_params.preset = atol((it->second).c_str());
				}
				else if (it->first == "vprof")
				{
					v_enc_params.profile = atoi((it->second).c_str());
				}
				else if (it->first == "vlevel")
				{
					v_enc_params.level = atoi((it->second).c_str());
				}
				else if (it->first == "vperf") //performance
				{
					v_enc_params.perf = atol((it->second).c_str());
				}
				else if (it->first == "vframetype") //frame type
				{
					v_enc_params.frame_type = atol((it->second).c_str());
				}
				else if(it->first == "vfieldorder") //field order
				{
					v_enc_params.field_order = atol((it->second).c_str());
				}
				else if (it->first == "vframerate") //frame rate
				{
					v_enc_params.frame_rate = atof((it->second).c_str());
				}
				else if (it->first == "vratemode") //rate-mode CBR VBR
				{
					v_enc_params.bit_rate_mode = atol((it->second).c_str());
				}
				else if(it->first == "vbitrate")
				{
					v_enc_params.bit_rate = atoi((it->second).c_str());
				}
				else if (it->first == "vgop")
				{
					v_enc_params.gop_size = atol((it->second).c_str());
				}
				else if (it->first == "vbframes")
				{
					v_enc_params.b_frames = atol((it->second).c_str());
				}
				//audio
				else if (it->first == "abitrateindex")
				{
					a_enc_params.bit_rate_index = atol((it->second).c_str());
				}
				else if (it->first == "amode")
				{
					a_enc_params.audio_mode = atol((it->second).c_str());
				}
				else if (it->first == "alayer")
				{
					a_enc_params.audio_layer = atol((it->second).c_str());
				}
				else if (it->first == "aversion")
				{
					a_enc_params.mpeg_version = atol((it->second).c_str());
				}
// 				else if (it->first == "aobjtype")
// 				{
// 					a_enc_params.aac_object_type = atol((it->second).c_str());
// 				}
				else if (it->first == "aheader")
				{
					a_enc_params.header_type = atol((it->second).c_str());
				}
				else if (it->first == "ahe")
				{
					a_enc_params.he = atol((it->second).c_str());
				}
				else if (it->first == "avbr")
				{
					a_enc_params.vbr = atol((it->second).c_str());
				}
				//mux
				else if (it->first == "enablepaddings")
				{
					mux_params.enabled_paddings = atol((it->second).c_str());
				}
				else if (it->first == "requiredbitrate")
				{
					mux_params.required_bitrate = atol((it->second).c_str());
				}
				else if (it->first == "pcrinterval")
				{
					mux_params.PCR_repetition_rate = atol((it->second).c_str());
				}
				else if (it->first == "psiinterval")
				{
					mux_params.PSI_repetition_rate = atol((it->second).c_str());
				}
				else if (it->first == "videopid")
				{
					mux_params.video_pid = atol((it->second).c_str());
				}
				else if (it->first == "audiopid")
				{
					mux_params.audio_pid = atol((it->second).c_str());
				}
				//dtnetrender
				else if (it->first == "devtype")
				{
					dt_params.devtype = atoi((it->second).c_str());
				}
				else if (it->first == "devport")
				{
					dt_params.devport = atoi((it->second).c_str());
				}
				else if (it->first == "txmode")
				{
					dt_params.txmode = atoi((it->second).c_str());
				}
				else if (it->first == "delaytime")
				{
					dt_params.delaytime = atoi((it->second).c_str());
				}

				it = options.erase(it);
			}
		}

		bool mc_enc_pumpstream::init_h264_encoder()
		{
			h264_v_settings v_settings;
			if (v_enc_params.preset == ITEM_NOT_INIT)		v_enc_params.preset = H264_MAIN;
			if (v_enc_params.perf == ITEM_NOT_INIT)         v_enc_params.perf = H264_PERF_BALANCED;
			if (v_enc_params.frame_rate == ITEM_NOT_INIT)	v_enc_params.frame_rate = 25;
			if (v_enc_params.frame_type == ITEM_NOT_INIT)	v_enc_params.frame_type = H264_INTERLACED;
			if (v_enc_params.field_order == ITEM_NOT_INIT)   v_enc_params.field_order = H264_TOPFIELD_FIRST;
			if (v_enc_params.bit_rate_mode == ITEM_NOT_INIT) v_enc_params.bit_rate_mode = H264_CBR;
			if (v_enc_params.bit_rate == ITEM_NOT_INIT)      v_enc_params.bit_rate = 6000000;
			if (v_enc_params.gop_size == ITEM_NOT_INIT)		 v_enc_params.gop_size = 33;
			if (v_enc_params.b_frames == ITEM_NOT_INIT)		 v_enc_params.b_frames = 2;
						
			h264OutVideoDefaultSettings(v_enc_params.preset, width, height, v_enc_params.frame_rate, v_enc_params.frame_type, get_rc, &v_settings, nullptr);
			h264OutVideoPerformance(&v_settings, 0, v_enc_params.perf, 0);

			if (v_enc_params.profile != ITEM_NOT_INIT)		 v_settings.profile_id = v_enc_params.profile;
			if (v_enc_params.level != ITEM_NOT_INIT)		 v_settings.level_id = v_enc_params.level;
			v_settings.field_order		= v_enc_params.field_order; 
			v_settings.bit_rate_mode	= v_enc_params.bit_rate_mode;
			v_settings.bit_rate			= v_enc_params.bit_rate;
			v_settings.idr_interval		= v_enc_params.gop_size;
			v_settings.reordering_delay = v_enc_params.b_frames + 1;


			v_settings.buffering = 3;
			v_settings.encoding_buffering = 2;

			if (h264OutVideoChkSettings(get_rc, &v_settings, H264_CHECK_AND_ADJUST | H264_CHECK_FOR_LEVEL, nullptr) == H264ERROR_FAILED)
			{
				CASPAR_LOG(error) << L"h264OutVideoChkSettings failed.";
				return false;
			}

			v_enc_h264 = h264OutVideoNew(get_rc, &v_settings, 0, 0xFFFFFFFF, 0, 0);
			if (!v_enc_h264)
			{
				CASPAR_LOG(error) << L"h264OutVideoNew failed.";
				return false;
			}

			int32_t init_options = 0;
			void *opt_list[10];
			org_auxinfo = videobs->input.auxinfo;
			videobs->input.auxinfo = auxinfo;
			if (h264OutVideoInit(v_enc_h264, &(videobs->input), init_options, &opt_list[0]))
			{
				CASPAR_LOG(error) << L"h264OutVideoInit failed.";
				h264OutVideoFree(v_enc_h264);
				return false;
			}

			return true;
		}
		bool mc_enc_pumpstream::init_mpeg2_encoder()
		{
			mpeg_v_settings v_settings;
			if (v_enc_params.preset == ITEM_NOT_INIT)		 v_enc_params.preset = MPEG_MPEG2;
			if (v_enc_params.perf == ITEM_NOT_INIT)          v_enc_params.perf = 15;  //0~31
			if (v_enc_params.frame_rate == ITEM_NOT_INIT)	 v_enc_params.frame_rate = 25;
			if (v_enc_params.frame_type == ITEM_NOT_INIT)    v_enc_params.frame_type = 0; //0-Interlaced 1-Progressive
			if (v_enc_params.field_order == ITEM_NOT_INIT)   v_enc_params.field_order = 1; //0- bottom field first    1-top field first
			if (v_enc_params.bit_rate_mode == ITEM_NOT_INIT) v_enc_params.bit_rate_mode = VBR_CONSTANT;
			if (v_enc_params.bit_rate == ITEM_NOT_INIT)      v_enc_params.bit_rate = 6000000;
			if (v_enc_params.gop_size == ITEM_NOT_INIT)		 v_enc_params.gop_size = 15;
			if (v_enc_params.b_frames == ITEM_NOT_INIT)      v_enc_params.b_frames = 2;

			mpegOutVideoDefaults(&v_settings, v_enc_params.preset, VM_PAL); 
			
			if (v_enc_params.profile != ITEM_NOT_INIT)		 v_settings.profile = v_enc_params.profile; 
			if (v_enc_params.level   != ITEM_NOT_INIT)		 v_settings.level = v_enc_params.level;		
			
			v_settings.frame_rate			= v_enc_params.frame_rate;
			v_settings.prog_frame			= v_enc_params.frame_type;
			v_settings.topfirst				= v_enc_params.field_order;
			v_settings.constant_bitrate		= v_enc_params.bit_rate_mode;
			v_settings.bit_rate				= v_enc_params.bit_rate;
			v_settings.N					= v_enc_params.gop_size;
			v_settings.M					= v_enc_params.b_frames + 1;
			v_settings.def_horizontal_size	= width;
			v_settings.def_vertical_size	= height;

			if (v_settings.constant_bitrate == VBR_CONSTANT) 
				v_settings.fixed_vbv_delay = 0;

			mpegOutVideoPerformance(&v_settings, PERF_ONLINE, v_enc_params.perf, 0);
			if (mpegOutVideoChkSettings(get_rc, &v_settings, CHECK_ALL, nullptr))
			{
				CASPAR_LOG(error) << L"mpegOutVideoChkSettings failed.";
				return false;
			}

			v_enc_mp2v = mpegOutVideoNew(get_rc, &v_settings, 0, 0xFFFFFFFF, 0, 0); 
			if (!v_enc_mp2v)
			{
				CASPAR_LOG(error) << L"mpegOutVideoNew failed.";
				return false;
			}

			int32_t init_options = 0;
			if (mpegOutVideoInit(v_enc_mp2v, &(videobs->input), init_options))
			{
				CASPAR_LOG(error) << L"mpegOutVideoInit failed.";
				mpegOutVideoFree(v_enc_mp2v);
				return false;
			}

			return true;
		}

		bool mc_enc_pumpstream::init_mpa_encoder() 
		{
			mpeg_a_settings a_settings;
			if (a_enc_params.audio_layer == ITEM_NOT_INIT) a_enc_params.audio_layer = MPEG_AUDIO_LAYER2;
			if (a_enc_params.audio_mode == ITEM_NOT_INIT) a_enc_params.audio_mode = MPG_MD_STEREO;
			if (a_enc_params.bit_rate_index == ITEM_NOT_INIT) a_enc_params.bit_rate_index = L2_AUDIOBITRATE256;

			mpegOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);

			a_settings.audio_mode = a_enc_params.audio_mode;
			a_settings.audio_bitrate = a_enc_params.bit_rate_index;
			a_settings.audio_layer = a_enc_params.audio_layer;
			if (mpegOutAudioChkSettings(get_rc, &a_settings, MCPROFILE_DEFAULT, audio_sample_rate, CHECK_ALL, nullptr))
			{
				CASPAR_LOG(error) << L"mpegOutAudioChkSettings failed.";
				return false;
			}
			// audio encoder instance
			a_enc_mpa = mpegOutAudioNew(get_rc, &a_settings, 0, 0, audio_sample_rate);
			if (!a_enc_mpa)
			{
				CASPAR_LOG(error) << L"mpegOutAudioNew failed.";
				return false;
			}

			// Attach previously created bufstream to new encoder instance
			if (mpegOutAudioInit(a_enc_mpa, &(audiobs->input)))
			{
				CASPAR_LOG(error) << L"mpegOutAudioInit failed.";
				mpegOutAudioFree(a_enc_mpa);
				return false;
			}
			return true;
		}
		bool mc_enc_pumpstream::init_aac_encoder()
		{
			aac_a_settings a_settings;
			if (a_enc_params.mpeg_version == ITEM_NOT_INIT) a_enc_params.mpeg_version = MPEG4_AAC_AUDIO;
			//if (a_enc_params.aac_object_type == ITEM_NOT_INIT) a_enc_params.aac_object_type = AAC_LC;
			if (a_enc_params.header_type == ITEM_NOT_INIT) a_enc_params.header_type = AAC_HEADER_ADTS;
			if (a_enc_params.he == ITEM_NOT_INIT) a_enc_params.he = AAC_HE_NOTUSED;
			if (a_enc_params.vbr == ITEM_NOT_INIT) a_enc_params.vbr = AAC_VBR_NOTUSED;
			if (a_enc_params.bit_rate_index == ITEM_NOT_INIT) a_enc_params.bit_rate_index = AAC_AUDIOBITRATE_128;

			aacOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);
			a_settings.mpeg_version = a_enc_params.mpeg_version;
			//a_settings.aac_object_type = a_enc_params.aac_object_type;
			a_settings.header_type = a_enc_params.header_type;
			a_settings.he = a_enc_params.he;
			a_settings.vbr = a_enc_params.vbr;
			a_settings.audio_bitrate_index = a_enc_params.bit_rate_index;

			a_settings.bits_per_sample = AAC_BITS_PER_SAMPLE_16;
			switch (in_channel_layout_.num_channels)
			{
			case 1:
				a_settings.input_channels = AAC_CHANNELS_1_MONO;
				break;
			case 2:
				a_settings.input_channels = AAC_CHANNELS_2_STEREO;
				break;
			case 3:
				a_settings.input_channels = AAC_CHANNELS_3_FL_FR_FC;
				break;
			case 4:
				a_settings.input_channels = AAC_CHANNELS_4_FL_FR_FC_BC;
				break;
			case 5:
				a_settings.input_channels = AAC_CHANNELS_5_FL_FR_FC_BL_BR;
				break;
			case 6:
				a_settings.input_channels = AAC_CHANNELS_6_FL_FR_FC_BL_BR_LF;
				break;
			case 8:
				a_settings.input_channels = AAC_CHANNELS_8_FL_FR_FC_LF_BL_BR_SL_SR;
				break;
			default:
				break;
			}

			if (aacOutAudioChkSettings(get_rc, &a_settings, MCPROFILE_DEFAULT, audio_sample_rate, CHECK_ALL, nullptr))
			{
				CASPAR_LOG(error) << L"aacOutAudioChkSettings failed.";
				return false;
			}
			a_enc_aac = aacOutAudioNew(get_rc, &a_settings, 0, 0xFFFFFFFF, audio_sample_rate);
			if (!a_enc_aac)
			{
				CASPAR_LOG(error) << L"aacOutAudioNew failed.";
				return false;
			}

			if (aacOutAudioInit(a_enc_aac, &(audiobs->input)))
			{
				CASPAR_LOG(error) << L"aacOutAudioInit failed.";
				aacOutAudioFree(a_enc_aac);
				return false;
			}
			return true;
		}
		bool mc_enc_pumpstream::init_pcm_encoder()
		{
			pcm_a_settings a_settings;
			pcmOutAudioDefaults(&a_settings, MCPROFILE_DEFAULT);

			a_settings.num_channels = static_cast<int16_t>(in_channel_layout_.num_channels);
			a_settings.pcm_quantization = PCM_16BITS;
			a_settings.audio_layer = AES3_302M_AUDIO;
		
			if (pcmOutAudioChkSettings(get_rc, &a_settings, 0, audio_sample_rate, CHECK_ALL, nullptr))
			{
				CASPAR_LOG(error) << L"pcmOutAudioChkSettings failed.";
				return false;
			}

			a_enc_pcm = pcmOutAudioNew(get_rc, &a_settings, 0, FRAMERATE25, audio_sample_rate);
			if (!a_enc_pcm)
			{
				CASPAR_LOG(error) << L"pcmOutAudioNew failed.";
				return false;
			}

			if (pcmOutAudioInit(a_enc_pcm, &(audiobs->input)))
			{
				CASPAR_LOG(error) << L"pcmOutAudioInit failed.";
				pcmOutAudioFree(a_enc_pcm);
				return false;
			}
			return true;
		}
		bool mc_enc_pumpstream::init_mpeg_muxer() 
		{
			mp2muxer_set_struct muxer_settings;
			mp2mux_ext_set_struct ext_muxer_settings;
			mp2mux_stream_set_struct stream_settings;

			memset(&muxer_settings, 0, sizeof(muxer_settings));
			memset(&ext_muxer_settings, 0, sizeof(ext_muxer_settings));
			memset(&stream_settings, 0, sizeof(stream_settings));

			if (mux_params.enabled_paddings == ITEM_NOT_INIT) mux_params.enabled_paddings = 0;
			if (mux_params.PCR_repetition_rate == ITEM_NOT_INIT) mux_params.PCR_repetition_rate = 30;
			if (mux_params.PSI_repetition_rate == ITEM_NOT_INIT) mux_params.PSI_repetition_rate = 100;
			
			mpegOutMP2MuxDefaults(&muxer_settings, MPEG_TS);
			muxer_settings.VBR_multiplex = !mux_params.enabled_paddings;
			if (muxer_settings.VBR_multiplex == 0) //constant bitrate
			{
				if (mux_params.required_bitrate == ITEM_NOT_INIT)
				{
					CASPAR_LOG(error) << L"mpegOutMP2Mux must specifies required bitrate.";
					return false;
				}
				else
				{
					muxer_settings.user_mux_rate_bps = mux_params.required_bitrate;
				}
			}

			mp2muxer = mpegOutMP2MuxNew(get_rc, &muxer_settings);
			if (!mp2muxer)
			{
				CASPAR_LOG(error) << L"mpegOutMP2MuxNew failed.";
				return false;
			}
			
			ext_muxer_settings.PCR_LIMIT = mux_params.PCR_repetition_rate;
			ext_muxer_settings.PSI_LIMIT = mux_params.PSI_repetition_rate;
			if (is_output_stream_)
			{
				if (mpegOutMP2MuxInitStream(mp2muxer, &ext_muxer_settings, (&muxerbs->input)) != MUX_OK)
				{
					CASPAR_LOG(error) << L"mpegOutMP2MuxInitStream failed.";
					mpegOutMP2MuxFree(mp2muxer);
					return false;
				}
			}
			else
			{
				if (mpegOutMP2MuxInitStream(mp2muxer, &ext_muxer_settings, filebs) != MUX_OK)
				{
					CASPAR_LOG(error) << L"mpegOutMP2MuxInitStream failed.";
					mpegOutMP2MuxFree(mp2muxer);
					return false;
				}

			}

			//video data stream
			stream_settings.flags = STREAM_FLAG_VIDEO_STREAM;
			if (mux_params.video_pid != ITEM_NOT_INIT) stream_settings.PID = mux_params.video_pid;
			if (mpegOutMP2MuxAddStream(mp2muxer, &stream_settings, &(videobs->output)) != MUX_OK)
			{
				CASPAR_LOG(error) << L"mpegOutMP2MuxAddStream video failed.";
				mpegOutMP2MuxFree(mp2muxer);
				return false;
			}

			//audio data stream
			stream_settings.flags = STREAM_FLAG_AUDIO_STREAM;
			if (mux_params.audio_pid != ITEM_NOT_INIT) stream_settings.PID = mux_params.audio_pid;
			if (mpegOutMP2MuxAddStream(mp2muxer, &stream_settings, &(audiobs->output)) != MUX_OK)
			{
				CASPAR_LOG(error) << L"mpegOutMP2MuxAddStream audio failed.";
			 	mpegOutMP2MuxFree(mp2muxer);
			 	return false;
			}
			return true;
		}
		bool mc_enc_pumpstream::pathparse(std::string path, net_path_params& netparams)
		{
			//eg. udp://234.1.1.1:2345?localaddr=172.16.3.106 
			int32_t nIdx = static_cast<int32_t>(path.find(':'));
			if (nIdx < 0)
			{
				CASPAR_LOG(error) << L"Invalid path: " << path;
				return false;
			}
			std::string protocolstr = path.substr(0, nIdx + 3);
			if (protocolstr.compare("udp://"))
			{
				CASPAR_LOG(error) << L"Invalid path: " << path;
				return false;
			}
			netparams.protocol = path.substr(0, nIdx); //protocol

			path.erase(0, nIdx + 3);
			nIdx = static_cast<int32_t>(path.find(':'));
			if (nIdx < 0)
			{
				CASPAR_LOG(error) << L"Invalid path: " << path;
				return false;
			}

			netparams.ipAddr = path.substr(0, nIdx); //ipAddr
			path.erase(0, nIdx + 1);
			nIdx = static_cast<int32_t>(path.find("?"));
			if (nIdx <0)
			{
				netparams.port = atoi(path.c_str()); //port
				netparams.localAddr = "";
			}
			else
			{
				std::string strport = path.substr(0, nIdx);
				netparams.port = atoi(strport.c_str()); //port
				path.erase(0, nIdx + 1);
				//localaddr=172.16.3.106 
				nIdx = static_cast<int32_t>(path.rfind("="));
				if (nIdx < 0)
				{
					CASPAR_LOG(error) << L"Invalid path: " << path;
					return false;
				}
				else
				{
					path.erase(0, nIdx + 1);
					netparams.localAddr = path;
				}
			}	
			return true;
		}

		bool mc_enc_pumpstream::init_mc_netrender(std::string path)
		{
			//parse path: udp://234.1.1.1:2345?localaddr=172.16.3.106 
			net_path_params netparams;
			bool bparse = pathparse(path, netparams);
			if (bparse == false)
			{
				return false;
			}

			mcrender = new MCNetRender();
			bool bret = mcrender->init(netparams);

			return bret;
		}

		bool mc_enc_pumpstream::init_dt_netrender(std::string path)
		{
			//parse path: udp://234.1.1.1:2345?localaddr=172.16.3.106 
			net_path_params netparams;
			bool bparse = pathparse(path, netparams);
			if (bparse == false)
			{
				return false;
			}
			dt_params.destip = netparams.ipAddr;
			dt_params.destport = netparams.port;
			dt_params.protocol = netparams.protocol;
			if (mux_params.required_bitrate!= ITEM_NOT_INIT)
			{
				dt_params.tsbitrate = mux_params.required_bitrate;
			}
			else
			{
				CASPAR_LOG(error) << L"MPEG Muxer required bitrate is not set.";
				return false;
			}

			dtrender = new CDtNetRender();
			bool bret =dtrender->init(dt_params);
			return bret;
		}

		void mc_enc_pumpstream::encode_video(core::const_frame &frame)
		{
			void *ext_info_stack[16] = { 0 };
			uint32_t option_flags = 0;
			void **ext_info = &ext_info_stack[0];

			//video
			uint8_t* tmp_video_buffer = (uint8_t*)malloc(frame.size());
			if (tmp_video_buffer)
			{
				fast_memcpy(
					reinterpret_cast<char*>(tmp_video_buffer),
					frame.image_data().begin(),
					height * width * 4
				);

				switch (v_enc_type)
				{
				case VIDEOENC_H264:
					h264OutVideoPutFrame(v_enc_h264, tmp_video_buffer + img_start, line_size, width, height, fourcc, option_flags, ext_info);
					break;
				case VIDEOENC_MPEG2:
					mpegOutVideoPutFrame(v_enc_mp2v, tmp_video_buffer + img_start, line_size, width, height, fourcc, option_flags);
					break;
				case VIDEOENC_UNKNOWN:
				default:
					break;
				}
				free(tmp_video_buffer);
				tmp_video_buffer = nullptr;
			}
		}
		void mc_enc_pumpstream::encode_audio(core::const_frame &frame)
		{
			//audio
			uint8_t* input_audio_buffer = (uint8_t*)malloc(frame.audio_data().size() * sizeof(int32_t));
			uint8_t* tmp_audio_buffer = (uint8_t*)malloc(frame.audio_data().size() * sizeof(int16_t));
			if (tmp_audio_buffer)
			{
				fast_memcpy((void*)input_audio_buffer, frame.audio_data().begin(), frame.audio_data().size() * sizeof(int32_t));
				//32bit transfer to 16bit
				const uint8_t **in = const_cast<const uint8_t**>(&input_audio_buffer);
				uint8_t* out[] = { reinterpret_cast<uint8_t*>(tmp_audio_buffer) };
				const auto channel_samples = swr_convert(
					swr_.get(),
					out,
					static_cast<int>(frame.audio_data().size() * sizeof(int16_t) / in_channel_layout_.num_channels),
					in,
					static_cast<int>(frame.audio_data().size() / in_channel_layout_.num_channels));
				//////////////////////////////
				switch (a_enc_type)
				{
				case AUDIOENC_MPA:
					mpegOutAudioPutBytes(a_enc_mpa, tmp_audio_buffer, static_cast<uint32_t>(frame.audio_data().size() * sizeof(int16_t)));
					break;
				case AUDIOENC_AAC:
					aacOutAudioPutBytes(a_enc_aac, tmp_audio_buffer, static_cast<uint32_t>(frame.audio_data().size() * sizeof(int16_t)));
					break;
				case AUDIOENC_PCM:
					pcmOutAudioPutBytes(a_enc_pcm, tmp_audio_buffer, static_cast<uint32_t>(frame.audio_data().size() * sizeof(int16_t)));
					break;
				case AUDIOENC_UNKNOWN:
				default:
					break;
				}
				free(input_audio_buffer);
				input_audio_buffer = nullptr;
				free(tmp_audio_buffer);
				tmp_audio_buffer = nullptr;
			}
		}
		void mc_enc_pumpstream::pushstream()
		{
			while(is_running_)
			{ 
				uint32_t uiMediaDataLength = muxerbs->output.usable_bytes(&muxerbs->output);
				if (uiMediaDataLength > 0/* 1500*/)
				{
					uint8_t* pMediaData = (uint8_t*)malloc(uiMediaDataLength);
					muxerbs->output.copybytes(&muxerbs->output, pMediaData, uiMediaDataLength);
					switch (netrender_type)
					{
					case NETRENDER_MC:
						if (mcrender)
						{
							mcrender->senddata(pMediaData, uiMediaDataLength);
						}
						break;
					case NETRENDER_DT:
						if (dtrender)
						{
							dtrender->senddata(pMediaData, uiMediaDataLength);
						}
						break;
					case NETRENDER_UNKNOWN:
					default:
						break;
					}
									
					free(pMediaData);
					pMediaData = nullptr;
				}
				boost::this_thread::sleep_for(boost::chrono::milliseconds(20));
			}
		}

		// This functions is deprecated. Use functions from mccolorspace.h
		int32_t mc_enc_pumpstream::get_video_frame_size(int32_t w, int32_t h, uint32_t cs_fourcc, int32_t *linesize, int32_t *imgstart)
		{
			frame_colorspace_info_tt cs_info;
			int32_t error = get_frame_colorspace_info(&cs_info, w, h, cs_fourcc, 0);
			if (error)
				return 0;
			/* comment out by zibj 20170424   not need flip
			//if (get_cs_type(cs_fourcc) == CS_FORMAT_RGB)
			//	flip_colorspace(&cs_info);
			*/

			*linesize = cs_info.stride[0];
			*imgstart = cs_info.plane_offset[0];
			return cs_info.frame_size;
		}

		bool mc_enc_pumpstream::get_video_enc_type(std::string vcodec)
		{
			if (vcodec.empty())
			{
				return true;
			}
			else if(0 == vcodec.compare("h264"))
			{
				v_enc_type = VIDEOENC_H264;
			}
			else if (0 == vcodec.compare("mpeg2"))
			{
				v_enc_type = VIDEOENC_MPEG2;
			}
			else
			{
				v_enc_type = VIDEOENC_UNKNOWN;
				CASPAR_LOG(error) << L"not support this video format:" << vcodec;
				return false;
			}
			return true;
		}

		bool mc_enc_pumpstream::get_audio_enc_type(std::string acodec)
		{
			if (acodec.empty())
			{
				return true;
			}
			else if (0 == acodec.compare("mpa"))
			{
				a_enc_type = AUDIOENC_MPA;
			}
			else if (0 == acodec.compare("aac"))
			{
				a_enc_type = AUDIOENC_AAC;
			}
// 			else if (0 == acodec.compare("pcm")) //TS not support PCM
// 			{
// 				a_enc_type = AUDIOENC_PCM;
// 			}
			else
			{
				a_enc_type = AUDIOENC_UNKNOWN;
				CASPAR_LOG(error) << L"not support this audio format:" << acodec;
				return false;
			}
			return true;
		}

		bool mc_enc_pumpstream::get_muxer_type(std::string muxer)
		{
			if (muxer.empty())
			{
				return true;
			}			
			else if (0 == muxer.compare("mpegts"))
			{
				muxer_type = MUXER_MPEGTS;
			}
			else
			{
				muxer_type = MUXER_UNKNOWN;
				CASPAR_LOG(error) << L"not support this mxuer format:" << muxer;
				return false;
			}
			return true;
		}

		bool mc_enc_pumpstream::get_netrender_type(std::string netrender)
		{
			if (netrender.empty())
			{
				return true;
			}
			else if (0 == netrender.compare("mc"))
			{
				netrender_type = NETRENDER_MC;
			}
			else if (0 == netrender.compare("dt"))
			{
				netrender_type = NETRENDER_DT;
			}
			else
			{
				netrender_type = NETRENDER_UNKNOWN;
				CASPAR_LOG(error) << L"not support this netrender format:" << netrender;
				return false;
			}
			return true;
		}

		
	}
}
