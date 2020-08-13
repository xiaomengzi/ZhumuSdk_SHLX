#pragma once
#include "Minithread/Minithread.hpp"

class CFakeSystemTime :
	public Thread
{
public:
	static CFakeSystemTime* Initialize();
	static CFakeSystemTime* GetInstance();
	static void Uninitialize();

private:
	CFakeSystemTime();
	~CFakeSystemTime();
	CFakeSystemTime(const CFakeSystemTime &val);
	const CFakeSystemTime& operator= (const CFakeSystemTime &val);

protected:
	virtual int Run();

protected:
	virtual bool Process();

public:
	long long GetFakeSystmeTime();
	void StopThread();

private:
	static CFakeSystemTime* m_pInstance;
	long long				m_llCurSystemTime;
	long long				m_llTimeSpace;
	bool					m_bExitFlag;
};

