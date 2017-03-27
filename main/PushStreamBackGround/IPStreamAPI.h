#ifndef _IPSTREAMAPI_
#define _IPSTREAMAPI_

#ifdef __cplusplus
extern "C"	{
#endif    //__cplusplus

//输入解码参数类型定义应和解码链路一致
enum VideoFormat
{
	AVC =       0,
	MPEG2 = AVC+1,
	HEVC = MPEG2+1,
};

enum AudioFormat
{
	MPEG1_LAYER2 =	   0,
	AC3 = MPEG1_LAYER2+1,
	AAC = MPEG1_LAYER2+2,
};

//编码复用参数定义
typedef struct _tagMp2MuxConfPara{
	int  m_videoPID;
	int  m_audioPID;
	bool m_paddingOn;
	long m_bitRate;		
}Mp2MuxConfPara;

typedef struct  _tagVideoEncConfPara
{
	VideoFormat videoFormat;
	int encode_preset;
	int encode_profile;
	int encode_level;
	int encode_gopSize;
	int encode_interlace_mode;
	int encode_bitrate;
	int encode_performance;
}VideoEncConfPara;

typedef struct _tagAudioEncConfPara
{
	AudioFormat audioFormat;
	int layer;
	int bitrate;
}AudioEncConfPara;

typedef struct _tagRenderConfPara
{
	char* cServerNic;
	char* cIP;
	DWORD dwPort;
	unsigned RenderType;
	int dektecCachebyte;
	char* dektec_serial_number;
	char* dektec_serial_number_bak;
	bool isRedundancy;
	char* cServerNic_bak;
	char* cIP_bak;
	DWORD dwPort_bak;
}RenderConfPara;

enum RenderType
{
	MCRender = 0,
	FounderRender =1,
	DekTec = 2,
	DtRender = 3,
};

struct IPStream_API
{
	virtual bool vPlayCueWithData(
		 LPCWSTR lpwsClipPath,
		 __int64 som,
		 __int64 duration,
		 int videoFormat,
		 int audioFormat,
		 int audioGain,
		 int videoCacheCount,
		 int audioCacheCount) = 0;

	virtual int  vPlay()   = 0;
	virtual bool vRelease() = 0;
};

IPStream_API* __stdcall CreateInstanceIPStreamAPI(VideoEncConfPara* videoPara,AudioEncConfPara* audioPara,Mp2MuxConfPara* muxPara,RenderConfPara* renderPara, int nCacheFrames, LPCWSTR virtualSourceName);

#ifdef __cplusplus
};

#endif	//__cplusplus
#endif//_IPSTREAMAPI_