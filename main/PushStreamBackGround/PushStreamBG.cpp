#include "windows.h"
#include "IPStreamAPI.h"
#include "tinyxml.h"
#include <atlconv.h>

void InitParasByXML(
	LPCWSTR VirtualSourceName, 
	VideoEncConfPara* videoPara, 
	AudioEncConfPara* audioPara, 
	Mp2MuxConfPara* muxPara, 
	RenderConfPara* renderPara,
	int *cachetime
	)
{
	TiXmlDocument doc("PushStreamBackGround/stream_configue.xml");
	
	bool loadOkay = doc.LoadFile();
	if (loadOkay == false)
	{
		MessageBoxA(NULL, "Failed to open stream_configue.xml, please check the path.", "error", MB_OK);

		return;
	}
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* streamnode;// = root->FirstChildElement();
	TiXmlNode* pTargetStreamNode = NULL;
	bool findout = false;
	for (streamnode = root->FirstChildElement(); streamnode != NULL&&!findout; streamnode = streamnode->NextSiblingElement())
	{
		
		TiXmlNode* child = streamnode->FirstChild();
		
		USES_CONVERSION;
		while (child!=NULL)
		{

			if (strcmp(child->Value(), "source_name") != 0)
			{
				continue;
			}
			else
			{
				if (strcmp(child->ToElement()->GetText(), (W2A(VirtualSourceName))) == 0)
				{
					pTargetStreamNode = streamnode;
					findout = true;
				}
				break;
			}
			
			child = child->NextSiblingElement();
		}
	}
	if (pTargetStreamNode == NULL)
	{
		MessageBoxA(NULL, "Can not find the stream name, please check stream_configue.xml.", "error", MB_OK);
		
		return ;
	}
	TiXmlNode* streamchild = pTargetStreamNode->FirstChild();
	while (streamchild != NULL)
	{
		if (!strcmp(streamchild->Value(), "stream_ip"))
		{
			strcpy(renderPara->cIP, streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "stream_ip_bak"))
		{
			strcpy(renderPara->cIP_bak, streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "stream_port"))
		{
			renderPara->dwPort = atoi(streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "stream_port_bak"))
		{
			renderPara->dwPort_bak = atoi(streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "server_ip"))
		{
			strcpy(renderPara->cServerNic, streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "server_ip_bak"))
		{
			strcpy(renderPara->cServerNic_bak, streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "cachetime"))
		{
			(*cachetime) = atoi(streamchild->ToElement()->GetText());
		}
		else if (!strcmp(streamchild->Value(), "Redundancy"))
		{
			renderPara->isRedundancy = false;
			if (!strcmp(streamchild->ToElement()->GetText(), "1"))
			{
				renderPara->isRedundancy = true;
			}
		}
		else if (!strcmp(streamchild->Value(), "video"))
		{
			TiXmlNode* videolabel = streamchild;
			TiXmlNode* videochildnode = videolabel->FirstChild();
			while (videochildnode!=NULL)
			{
				if (!strcmp(videochildnode->Value(), "video_format"))
				{
					const char* name = videochildnode->ToElement()->GetText();
					if (!strcmp(name, "AVC"))
					{
						videoPara->videoFormat = AVC;
					}
					else if (!strcmp(name, "MPEG2"))
					{
						videoPara->videoFormat = MPEG2;
					}
				}
				else if (!strcmp(videochildnode->Value(), "preset"))
				{
					videoPara->encode_preset = atoi(videochildnode->ToElement()->GetText());
				}
				else if (!strcmp(videochildnode->Value(), "profile"))
				{
					videoPara->encode_profile = atoi(videochildnode->ToElement()->GetText());
				}
				else if (!strcmp(videochildnode->Value(), "level"))
				{
					videoPara->encode_level = atoi(videochildnode->ToElement()->GetText());
				}
				else if (!strcmp(videochildnode->Value(), "gop_size"))
				{
					videoPara->encode_gopSize = atoi(videochildnode->ToElement()->GetText());
				}
				else if (!strcmp(videochildnode->Value(), "performance"))
				{
					videoPara->encode_performance = atoi(videochildnode->ToElement()->GetText());
				}
				else if (!strcmp(videochildnode->Value(), "bit_rate"))
				{
					videoPara->encode_bitrate = atoi(videochildnode->ToElement()->GetText());
				}
				else if (!strcmp(videochildnode->Value(), "interlace_mode"))
				{
					videoPara->encode_interlace_mode = atoi(videochildnode->ToElement()->GetText());
				}
				videochildnode = videochildnode->NextSiblingElement();
			}

		}
		else if (!strcmp(streamchild->Value(), "audio"))
		{

			TiXmlNode* audiolabel = streamchild;
			TiXmlNode* audiochildnode = audiolabel->FirstChild();
			while (audiochildnode!=NULL)
			{
				if (!strcmp(audiochildnode->Value(), "audio_format"))
				{
					if (!strcmp(audiochildnode->ToElement()->GetText(), "MPEG1_LAYER2"))
					{
						audioPara->audioFormat = MPEG1_LAYER2;
					}
					else if (!strcmp(audiochildnode->ToElement()->GetText(), "AC3"))
					{
						audioPara->audioFormat = AC3;
					}
					else if (!strcmp(audiochildnode->ToElement()->GetText(), "AAC"))
					{
						audioPara->audioFormat = AAC;
					}
				}
				else if (!strcmp(audiochildnode->Value(), "audio_bitrate"))
				{
					audioPara->bitrate = atoi(audiochildnode->ToElement()->GetText());
				}
				else if (!strcmp(audiochildnode->Value(), "audio_layer"))
				{
					audioPara->layer = atoi(audiochildnode->ToElement()->GetText());
				}
				audiochildnode = audiochildnode->NextSiblingElement();
			}
		}
		else if (!strcmp(streamchild->Value(), "mux"))
		{

			TiXmlNode* muxlabel = streamchild;
			TiXmlNode* muxchildnode = muxlabel->FirstChild();
			while (muxchildnode != NULL)
			{
				if (!strcmp(muxchildnode->Value(), "padding_enable"))
				{
					muxPara->m_paddingOn = atoi(muxchildnode->ToElement()->GetText());
				}
				else if (!strcmp(muxchildnode->Value(), "video_pid"))
				{
					muxPara->m_videoPID = atoi(muxchildnode->ToElement()->GetText());
				}
				else if (!strcmp(muxchildnode->Value(), "audio_pid"))
				{
					muxPara->m_audioPID = atoi(muxchildnode->ToElement()->GetText());
				}
				else if (!strcmp(muxchildnode->Value(), "bit_rate"))
				{
					muxPara->m_bitRate = atoi(muxchildnode->ToElement()->GetText());
				}
				muxchildnode = muxchildnode->NextSiblingElement();
			}

		}
		else if (!strcmp(streamchild->Value(), "net_render"))
		{
			TiXmlNode* net_renderlabel = streamchild;
			TiXmlNode*net_renderchildnode = net_renderlabel->FirstChild();
			while (net_renderchildnode != NULL)
			{
				if (!strcmp(net_renderchildnode->Value(), "render_type"))
				{
					renderPara->RenderType = atoi(net_renderchildnode->ToElement()->GetText());
				}
				else if (!strcmp(net_renderchildnode->Value(), "serial_number"))
				{
					strcpy(renderPara->dektec_serial_number, net_renderchildnode->ToElement()->GetText());
				}
				else if (!strcmp(net_renderchildnode->Value(), "serial_number_bak"))
				{
					strcpy(renderPara->dektec_serial_number_bak, net_renderchildnode->ToElement()->GetText());
				}
				else if (!strcmp(net_renderchildnode->Value(), "dektecCacheByte"))
				{
					renderPara->dektecCachebyte = atoi(net_renderchildnode->ToElement()->GetText());
				}
				net_renderchildnode = net_renderchildnode->NextSiblingElement();
			}
		}
		streamchild = streamchild->NextSiblingElement();
	}
	
}

IPStream_API* IPStreamCreate(LPCWSTR VirtualSourceName)
{
	VideoEncConfPara videoPara;
	AudioEncConfPara audioPara;
	Mp2MuxConfPara muxPara;
	RenderConfPara renderPara;
	
	char cIPBuffer[20] = { 0 };
	char cIPBuffer_bak[20] = { 0 };
	char cServerNicBuffer[20] = { 0 };
	char cServerNicBuffer_bak[20] = { 0 };
    
	char dektec_serial_number[50] = { 0 };
	char dektec_serial_number_bak[50] = { 0 };

	renderPara.cIP = cIPBuffer;
	renderPara.cIP_bak = cIPBuffer_bak;
	renderPara.cServerNic = cServerNicBuffer;
	renderPara.cServerNic_bak = cServerNicBuffer_bak;
	renderPara.dektec_serial_number = dektec_serial_number;
	renderPara.dektec_serial_number_bak = dektec_serial_number_bak;

	int cachetime = 0;
	
	InitParasByXML(
		VirtualSourceName, &videoPara,
		&audioPara,
		&muxPara,
		&renderPara,
		&cachetime
		);
	if (cachetime > 0)
	{
		cachetime = (cachetime + 39) / 40;
	}
	IPStream_API* IPStream = CreateInstanceIPStreamAPI(
		&videoPara,
		&audioPara,
		&muxPara,
		&renderPara,
		cachetime,
		VirtualSourceName
	);

	return IPStream;
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow
	)
{
	IPStream_API* stream = IPStreamCreate(lpCmdLine);
	if (stream == NULL)
	{
		MessageBoxA(NULL, "Failed to create ip stream, program will be quit!", "error", MB_OK);

		return 0;
	}
	HANDLE hEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, lpCmdLine);
	int Max_count = 5;
	if (hEvent == NULL)
	{
		while (true)
		{
			Sleep(100);
			hEvent = OpenEventW(EVENT_ALL_ACCESS, FALSE, lpCmdLine);
			if (hEvent != NULL || Max_count == 0)break;
			--Max_count;
		}
	}

	if (hEvent == NULL)
	{
		MessageBoxA(NULL, "Failed to open event, program will be quit!", "error", MB_OK);

		return 0;
	}
	stream->vPlay();
	WaitForSingleObject(hEvent, INFINITE);

	return 0;
}