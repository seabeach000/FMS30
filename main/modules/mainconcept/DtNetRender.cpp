#include "DtNetRender.h"
#include <common/log.h>

CDtNetRender::CDtNetRender()
	:m_bStartSend(false)
	,m_nCurLoad(0)
{
	
}

CDtNetRender::~CDtNetRender()
{
	is_running_ = false;
	thread_.join();

	m_tsOutPort.SetTxControl(DTAPI_TXCTRL_IDLE);
	m_tsOutPort.Detach(DTAPI_INSTANT_DETACH);
	m_dev.Detach();
}

bool CDtNetRender::init(dtnetrender_params dtparams)
{
	bool bret = false;
	bret = SetDektecType(dtparams.devtype);
	if (!bret)
	{
		return bret;
	}

	bret = SetDevOutPort(dtparams.devport);
	if (!bret)
	{
		return bret;
	}

	bret = SetTxControl(DTAPI_TXCTRL_IDLE);
	if (!bret)
	{
		return bret;
	}

	bret = SetTxMode(static_cast<int32_t>(dtparams.txmode), static_cast<int32_t>(DTAPI_TXSTUFF_MODE_ON));
	if (!bret)
	{
		return bret;
	}

	bret = SetIpPars(dtparams);
	if (!bret)
	{
		return bret;
	}

	bret = SetTsRateBps(dtparams.tsbitrate);
	if (!bret)
	{
		return bret;
	}

 	
	m_tsOutPort.ClearFifo();          // Clear FIFO (i.e. start with zero load)

	bret = SetFifoSize(dtparams.delaytime, dtparams.tsbitrate);
	if (!bret)
	{
		return bret;
	}

	bret = SetTxControl(DTAPI_TXCTRL_HOLD);
	if (!bret)
	{
		return bret;
	}
	is_running_ = true;
	thread_ = boost::thread([this] {Adjust(); }); //码率调整
	return true;
}

void CDtNetRender::senddata(uint8_t* pbuffer, int32_t nbufferLen)
{ 
	DTAPI_RESULT dr;
	if (!m_bStartSend)
	{
		if (m_nCurLoad < m_nFifoSize*FIFO_LOAD_CACHE_RATIO)
		{
			dr = m_tsOutPort.Write((char*)pbuffer, nbufferLen);
			if (dr != DTAPI_OK)
			{
				CASPAR_LOG(error) << L"Write failed, ERROR:" << DtapiResult2Str(dr);
				return;
			}
			m_nCurLoad += nbufferLen;
			return;
		}
		else
		{
			m_bStartSend = true;
			dr = m_tsOutPort.SetTxControl(DTAPI_TXCTRL_SEND);	// Start transmission
			if (dr != DTAPI_OK)
			{
				CASPAR_LOG(error) << L"SetTxControl failed,ERROR:" << DtapiResult2Str(dr);
			}
		}
	}

	dr = m_tsOutPort.Write((char*)pbuffer, nbufferLen);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"Write failed, ERROR:" << DtapiResult2Str(dr);
	}
}

void CDtNetRender::Adjust()
{
	int nFifoLoad = 0;
	int nFifoSize = 0;
	int nTsRate = 0;
	while (is_running_)
	{
		if (m_bStartSend)
		{
			m_tsOutPort.GetFifoLoad(nFifoLoad);
			m_tsOutPort.GetFifoSize(nFifoSize);
			m_tsOutPort.GetTsRateBps(nTsRate);
			if (nFifoLoad <= nFifoSize*FIFO_LOAD_CACHE_RATIO)
			{
				if (nTsRate == m_nTsBitRate)
				{
					m_tsOutPort.SetTsRateBps(static_cast<int>(m_nTsBitRate * ADJUST_BITRATE_RATIO));
					CASPAR_LOG(debug) << L"Adjust GetFifoLoad: " << nFifoLoad;
				}
			}
			else
			{
				if ((nTsRate != m_nTsBitRate) && (nFifoLoad > nFifoSize*FIFO_LOAD_CACHE_RATIO))
				{
					m_tsOutPort.SetTsRateBps(m_nTsBitRate);
					CASPAR_LOG(debug) << L"Adjust GetFifoLoad: " << nFifoLoad;
				}
			}
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(CHECK_FIFO_INTERVAL));
	}
}


bool CDtNetRender::SetDektecType(int32_t devtype)
{
	DTAPI_RESULT dr;
	m_dev.Detach();
	dr = m_dev.AttachToType(devtype);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"Failed to attach to the DTA-" << devtype << L", ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}
bool CDtNetRender::SetDevOutPort(int32_t devport)
{
	DTAPI_RESULT dr;
	m_tsOutPort.Detach(DTAPI_INSTANT_DETACH);
	dr = m_tsOutPort.AttachToPort(&m_dev,devport);
	if (dr != DTAPI_OK && dr != DTAPI_OK_FAILSAFE)
	{
		CASPAR_LOG(error) << L"Can't attach to the channel " <<devport << L", ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool CDtNetRender::SetTxControl(int32_t txcontrol)
{
	DTAPI_RESULT dr;
	dr = m_tsOutPort.SetTxControl(txcontrol);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetTxControl failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool CDtNetRender::SetTxMode(int32_t txmode, int32_t stuffmode)
{
	DTAPI_RESULT dr;
	dr = m_tsOutPort.SetTxMode(txmode, stuffmode);  
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetTxMode failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}

bool CDtNetRender::SetIpPars(dtnetrender_params dtparams)
{
	DTAPI_RESULT dr;
	DtapiInitDtIpParsFromIpString(m_ipPars, dtparams.destip.c_str(), NULL);
	m_ipPars.m_Port = static_cast<unsigned short>(dtparams.destport);
	if (0 == dtparams.protocol.compare("udp"))
	{
		m_ipPars.m_Protocol = DTAPI_PROTO_UDP;
 	}
	m_ipPars.m_TimeToLive = 64;
	m_ipPars.m_NumTpPerIp = 7;
	m_ipPars.m_Flags = DTAPI_IP_V4;
 	dr = m_tsOutPort.SetIpPars(&m_ipPars);
	if (dr!= DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetIpPars failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}


bool CDtNetRender::SetTsRateBps(int32_t tsbitrate)
{
	DTAPI_RESULT dr;
	dr = m_tsOutPort.SetTsRateBps(tsbitrate);
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"SetTsrateBps failed, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	m_nTsBitRate = tsbitrate;
	return true;
}

bool CDtNetRender::SetFifoSize(int32_t delaytime, int32_t tsbitrate)
{
	DTAPI_RESULT dr;
	m_nFifoSize = static_cast<int32_t>(double(delaytime) / 1000 * tsbitrate /8);
	m_nFifoSize = static_cast<int32_t>(m_nFifoSize / FIFO_LOAD_CACHE_RATIO);
	m_nFifoSize = m_nFifoSize / 16 * 16; //16的倍数
	dr = m_tsOutPort.SetFifoSize(m_nFifoSize); 
	if (dr != DTAPI_OK)
	{
		CASPAR_LOG(error) << L"Failed to set Fifo size, ERROR:" << DtapiResult2Str(dr);
		return false;
	}
	return true;
}
