#pragma once
#include "Minithread/Minithread.hpp"
#include "GCommon.h"

class TimeUtil
{
public:
	TimeUtil();
public:
	static UINT64			milliseconds();
private:
	static ThreadLock		m_sLastMillisMutex;
	static INT64			m_sMsecSince1970;
	static INT64			m_sInitialMsec;
	static INT64			m_sCompareWrap;
	static INT64			m_sWrapMsec;
	static INT64			m_sLastMsecMilli;
};
