#include "TimeUtil.h"

#ifdef WIN32
//header
#include	<time.h>
#include	<mmsystem.h>
#include	<process.h>
#include	<io.h>
#include	<direct.h>
#include    <sys/types.h>
#include    <sys/timeb.h>
#include    <Winsock2.h>
//lib
#pragma comment(lib,"winmm.lib")
#else
#include	<unistd.h>
#include	<sys/time.h>
#include	<sys/timeb.h>
#include	<net/if.h>
#include	<sys/ioctl.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#endif

INT64		TimeUtil::m_sMsecSince1970 = 0;
INT64		TimeUtil::m_sInitialMsec = 0;
INT64		TimeUtil::m_sCompareWrap = 0;
INT64		TimeUtil::m_sWrapMsec = 0;
INT64		TimeUtil::m_sLastMsecMilli = 0;
ThreadLock	TimeUtil::m_sLastMillisMutex;

TimeUtil::TimeUtil()
{
	if (m_sInitialMsec == 0)
	{
		_tzset();
		m_sMsecSince1970 = ::time(NULL);
		m_sMsecSince1970 *= 1000;
		m_sInitialMsec = milliseconds();
		m_sCompareWrap = ((INT64)0xffffffff << 32);
		m_sWrapMsec = ((INT64)0x00000001 << 32);
		m_sLastMsecMilli = 0;
	}
}

UINT64 TimeUtil::milliseconds()
{
#if	defined(WIN32)
	ThreadLockZone	locker(m_sLastMillisMutex);

	INT64	sCurrentMsecMilli = (UINT) ::timeGetTime() + (m_sLastMsecMilli & m_sCompareWrap);
	if ((sCurrentMsecMilli - m_sLastMsecMilli) < 0)
	{
		sCurrentMsecMilli += m_sWrapMsec;
	}
	m_sLastMsecMilli = sCurrentMsecMilli;


	return ((sCurrentMsecMilli - m_sInitialMsec) + m_sMsecSince1970);
#else
	/*
	struct timeval	t;
	int	nError	= ::gettimeofday(&t,NULL);
	TMASSERT((nError == 0));

	INT64	sCurrentMsec;
	sCurrentMsec	= t.tv_sec;
	sCurrentMsec	*= 1000;
	sCurrentMsec	+= (t.tv_usec / 1000);

	return ((sCurrentMsec - m_sInitialMsec) + m_sMsecSince1970);
	*/
	struct timespec	ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	INT64	sCurrentMsec;
	sCurrentMsec = ts.tv_sec;
	sCurrentMsec *= 1000;
	sCurrentMsec += (ts.tv_nsec / 1000000);

	return sCurrentMsec;
#endif	//(_WIN32_)
}
