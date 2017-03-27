#include "stdafx.h"
#include "timeoutHandler.h"
#include <common/log.h>

timeoutHandler::timeoutHandler(unsigned long TimeOutMs) :timeout_ms_(TimeOutMs)
{
}


timeoutHandler::~timeoutHandler()
{
}

void timeoutHandler::reset(unsigned long time)
{
	timeout_ms_ = time;
	lastTime_ = GetTickCount();
}

bool timeoutHandler::is_timeout()
{
	const DWORD actualDelay = GetTickCount() - lastTime_;
	bool istimeout = (actualDelay > timeout_ms_);
	if (istimeout)
	{
		CASPAR_LOG(info) << L"open input or av_read_frame timeout > 30000 ";
	}
	return istimeout;
}

int timeoutHandler::check_interrupt(void* t)
{
	return t && static_cast<timeoutHandler*>(t)->is_timeout();
}
