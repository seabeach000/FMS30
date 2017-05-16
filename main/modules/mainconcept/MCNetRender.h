#pragma once
#include "params.h"
#include <net_renderer.h>
#include <string>

using namespace MainConcept::NetworkStreaming;

class MCNetRender : public ISenderNotifier
{
public:
	MCNetRender();
	~MCNetRender();
public:
	virtual void OnConfigChanged(void *pData, uint32_t *uiDataLen);
	virtual void OnPacketSend(bool bMarker, uint32_t aBytesSent, int64_t i64TimeStamp, uint32_t uiSamplesCount);

	IBaseSender* GetNetSender() { return m_pSender; }
	bool init(net_path_params netparams);
	void senddata(uint8_t* pMediaData, uint32_t uiMediaDataLength);
private:
	int64_t m_iFirstSystemTime;
	int64_t m_iLastSystemTime;
	int64_t m_i64NewSegmentTime;
	IBaseSender* m_pSender;
};
