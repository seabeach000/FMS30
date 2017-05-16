#pragma once

#include <asmlib.h>
#include <string.h>
#include <DTAPI.h>

#include <tbb/atomic.h>
#include <boost/thread.hpp>


#define CHECK_FIFO_INTERVAL         2000  //ms
#define ADJUST_BITRATE_RATIO		0.999 
#define FIFO_LOAD_CACHE_RATIO       0.5

struct dtnetrender_params
{
	int32_t  devtype;
	int32_t  devport;

	std::string   protocol;
	std::string   destip;
	int32_t       destport;	
	
	int32_t  tsbitrate;
	int64_t  txmode;
	int32_t  delaytime;//1000 ms

	dtnetrender_params()
	{
		devtype = 2162;
		devport = 1;
		tsbitrate = 0;
		txmode = DTAPI_TXMODE_188;
		delaytime = 1000;
	}
};

struct CDtNetRender
{
public:
	CDtNetRender();
	~CDtNetRender();
	bool init(dtnetrender_params dtparams);
	void senddata(uint8_t* pbuffer, int32_t nbufferLen); 
private:
	tbb::atomic<bool>						is_running_;
	boost::thread							thread_;
	void Adjust();
private:
	bool SetDektecType(int32_t devtype);
	bool SetDevOutPort(int32_t devport);
	bool SetTxControl(int32_t txcontrol);
	bool SetTxMode(int32_t txmode, int32_t stuffmode);
	bool SetIpPars(dtnetrender_params dtparams);
	bool SetTsRateBps(int32_t tsbitrate);
	bool SetFifoSize(int32_t delaytime, int32_t tsbitrate);
private:
	DtDevice m_dev;
	DtOutpChannel m_tsOutPort;
	DtIpPars m_ipPars;

	bool m_bStartSend;

	int32_t m_nCurLoad;
	int32_t m_nFifoSize;
	int32_t m_nTsBitRate;
};
