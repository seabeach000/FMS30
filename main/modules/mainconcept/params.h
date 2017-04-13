#pragma once
#include <string>
#define ITEM_NOT_INIT -123456


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

enum NETRENDER
{
	NETRENDER_MC, //mainconcept
	NETRENDER_DT, //Dektec
	NETRENDER_UNKNOWN
};

//vcodec params
struct vcodec_params
{
	/*
	*for H264£º2-H264_MAIN 5-H264_HIGH
	*for mpeg2£º2-MPEG_MPEG2
	*/
	int32_t     preset = ITEM_NOT_INIT;
	int32_t		profile = ITEM_NOT_INIT;
	int32_t     level = ITEM_NOT_INIT;
	/*
	*for H264£º 0-H264_PERF_FASTEST    9-H264_PERF_BALANCED   15-H264_PERF_BEST_Q  ,default 9
	*for mpeg2: 0~31,  default 15
	*/
	int32_t     perf = ITEM_NOT_INIT;
	/*
	*for H264£º 0-H264_PROGRESSIVE  1-H264_INTERLACED  2-H264_MBAFF
	*for mpeg2£º0-interlaced        1-progressive
	*/
	int32_t     frame_type = ITEM_NOT_INIT;
	/*
	*for h264£º  0-top field first      1-bottom field first
	*for mpeg2£º 1-top field first      0-bottom field first
	*/
	int32_t     field_order = ITEM_NOT_INIT;
	double      frame_rate = ITEM_NOT_INIT;

	int32_t     gop_size = ITEM_NOT_INIT;
	int32_t     b_frames = ITEM_NOT_INIT;
	/*
	*for H264£º0-H264_CBR        1-H264_CQT      2-H264_VBR  3-H264_TQM         4-H264_INTRARC
	*for mpeg2£º0-VBR_VARIABLE1  1-VBR_CONSTANT  2-VBR_CQT   3-VBR_CQT_STRICT
	*/
	int32_t     bit_rate_mode = ITEM_NOT_INIT;
	int32_t     bit_rate = ITEM_NOT_INIT;
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
	int32_t audio_layer = ITEM_NOT_INIT;
	int32_t audio_mode = ITEM_NOT_INIT;

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
	int32_t video_pid = ITEM_NOT_INIT;
	int32_t audio_pid = ITEM_NOT_INIT;
};

//netrenderer params;
struct net_path_params
{
	std::string protocol;
	std::string ipAddr;
	int32_t port;
	std::string localAddr;
};