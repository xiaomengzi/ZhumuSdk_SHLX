#include "FakeSystemTime.h"
#include "TimeUtil.h"

CFakeSystemTime* CFakeSystemTime::m_pInstance = NULL;

CFakeSystemTime* CFakeSystemTime::Initialize()
{
	return CFakeSystemTime::GetInstance();
}

CFakeSystemTime* CFakeSystemTime::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CFakeSystemTime;
	}
	return m_pInstance;
}

void CFakeSystemTime::Uninitialize()
{
	if (m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

CFakeSystemTime::CFakeSystemTime()
{
	m_llCurSystemTime = TimeUtil::milliseconds();
	m_llTimeSpace = 0;
	m_bExitFlag = false;
}


CFakeSystemTime::~CFakeSystemTime()
{
}

CFakeSystemTime::CFakeSystemTime(const CFakeSystemTime &val)
{
	m_llCurSystemTime = val.m_llCurSystemTime;
	m_llTimeSpace = val.m_llTimeSpace;
}

const CFakeSystemTime& CFakeSystemTime::operator = (const CFakeSystemTime &val)
{
	m_llCurSystemTime = val.m_llCurSystemTime;
	m_llTimeSpace = val.m_llTimeSpace;
	return *this;
}

int CFakeSystemTime::Run()
{
	int nSleepTime = 0;
	
	nSleepTime = 3;
	while (m_bExitFlag == false)
	{
		if (Process() == true)
		{
			
		}
		if (nSleepTime > 0)
		{
			Thread::Sleep(nSleepTime);
		}
	}

	return 0;
}

bool CFakeSystemTime::Process()
{
	long long llTmep = TimeUtil::milliseconds(); 
	if ((llTmep - m_llCurSystemTime - m_llTimeSpace < 0) || (llTmep - m_llCurSystemTime - m_llTimeSpace > 1000))
	{
		m_llCurSystemTime += 3;
		m_llTimeSpace = llTmep - m_llCurSystemTime;
	}
	else
	{
		m_llCurSystemTime = llTmep - m_llTimeSpace;
	}
	return true;
}

long long CFakeSystemTime::GetFakeSystmeTime()
{
	return m_llCurSystemTime;
}

void CFakeSystemTime::StopThread()
{
	if (Thread::IsRunning())
	{
		m_bExitFlag = true;
		WaitForExit();
	}
}
