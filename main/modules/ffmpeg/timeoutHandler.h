#pragma once
class timeoutHandler
{
public:
	timeoutHandler(unsigned long TimeOutMs);
	virtual ~timeoutHandler();

	void reset(unsigned long time);
	bool is_timeout();
	static int check_interrupt(void* t);

public:
	unsigned long timeout_ms_;
	DWORD        lastTime_;
};

