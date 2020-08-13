// MiniThread.hpp
#ifndef __MINI_THREAD_G_HPP__
#define __MINI_THREAD_G_HPP__

//////////////////////////////////////////////////////////////////////////
/* Usage:

    class SampleThread
        : private Thread
    {
    public:
        bool Start()
        {
            if (Thread::IsRunning()) return false;
            exitFlag_ = false;
            return Thread::StartThread();
        }
        
        void Stop()
        {
            exitFlag_ = true;
            Thread::WaitForExit();
        }

        virtual int Run()
        {
            while (exitFlag_ == false)
            {
                // do something in thread....
            }
            return 0;
        }

    private:
        volatile bool exitFlag_;
    };

    void Foo()
    {
        SampleThread thread;
        thread.Start();

        // waiting for exit....

        thread.Stop();
    }

*/
// NOTE: class Thread is not thread-safe!
//       So starting one thread object in same thread is recommended
//////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define THREAD_MAIN_PROC DWORD WINAPI
typedef DWORD ThreadProcReturnType;

#else

#include <pthread.h>
#include <unistd.h>

#define THREAD_MAIN_PROC void*
typedef void* ThreadProcReturnType;

#endif

#include <cassert>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////

class Thread
{
public:
	Thread() : hThread_(0){}
    virtual ~Thread() { /*assert(hThread_ == 0);*/ }
private:
    Thread(const Thread&); // disable copy
    void operator = (const Thread&);

public:
	bool StartThread()
	{
		if (hThread_ != 0) return false;

#ifdef _WIN32
		DWORD threadId = 0;
		hThread_ = CreateThread(NULL, 0, ThreadMain, this, 0, &threadId);
		if (hThread_ == NULL)
		{
			return false;
		}
#else
        if (pthread_create(&hThread_, NULL, ThreadMain, this) != 0)
		{
			return false;
		}
		char theName[14] = {0};
		sprintf(theName, "T%u", (unsigned int)pthread_self());
 		pthread_setname_np(hThread_, theName);
#endif

		return true;
	}

	void WaitForExit()
	{
		while (IsRunning())
		{
			Sleep(1);
		}
	}

#ifdef _WIN32
	DWORD	GetCurrentThreadID()		{ return ::GetCurrentThreadId(); }
#else
	pthread_t	GetCurrentThreadID()	{ return ::pthread_self(); }
#endif	//(__PTHREADS__)
	bool IsRunning() const
	{
		return (hThread_ != 0);
	}

public:
    bool SetHighPriority()
    {
#ifdef _WIN32
        if (SetThreadPriority(hThread_, THREAD_PRIORITY_HIGHEST) == FALSE)
        {
            return false;
        }
#else
        struct sched_param param;
        param.sched_priority = sched_get_priority_max(SCHED_FIFO);
        if (pthread_setschedparam(hThread_, SCHED_FIFO, &param) != 0)
        {
            return false;
        }
#endif
        return true;
    }

    void TerminateThread()
    {
#ifdef _WIN32
        ::TerminateThread(hThread_, 0);
#else
        pthread_cancel(hThread_);
#endif
        hThread_ = 0;
    }

private:
    static THREAD_MAIN_PROC ThreadMain(void* param)
	{
		Thread* pThis = reinterpret_cast<Thread*>(param);

		ThreadProcReturnType n = 0;
		if (pThis->OnEnterThread() != false)
		{
			n = (ThreadProcReturnType)pThis->Run();
			pThis->OnExitThread();
		}

#ifdef _WIN32
		CloseHandle(pThis->hThread_);
#else
        pthread_detach(pThis->hThread_);
#endif
		pThis->hThread_ = 0;
        return n;
	}

	virtual int Run() = 0;

private:
	virtual bool OnEnterThread() { return true; }
	virtual void OnExitThread()  { }

protected:
#ifdef _WIN32
	volatile HANDLE hThread_;
#else
	pthread_t hThread_;
#endif

public:
    static void Sleep(long milliseconds)
    {
#ifdef _WIN32
        ::Sleep(milliseconds);
#else
        usleep(milliseconds * 1000);
#endif
    }
};

//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32

class ThreadLock
{
public:
    ThreadLock()  { InitializeCriticalSection(&cs_); }
    ~ThreadLock() { DeleteCriticalSection    (&cs_); }
private:
    ThreadLock(const ThreadLock&); // disable copy and assignment
    void operator = (const ThreadLock&);
public:
    void Lock()   { EnterCriticalSection     (&cs_); }
    void Unlock() { LeaveCriticalSection     (&cs_); }
private:
    CRITICAL_SECTION cs_;
};

#else//_WIN32

#include <pthread.h>

class ThreadLock
{
public:
    ThreadLock()  {
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init   (&mutex_, &attr); }
    ~ThreadLock() { pthread_mutex_destroy(&mutex_);       }
private:
    ThreadLock(const ThreadLock&); // disable copy and assignment
    void operator = (const ThreadLock&);
public:
    void Lock()   { pthread_mutex_lock   (&mutex_);       }
    void Unlock() { pthread_mutex_unlock (&mutex_);       }
private:
    pthread_mutex_t mutex_;
};

#endif//_WIN32
//////////////////////////////////////////////////////////////////////////

class ThreadLockZone
{
public:
    ThreadLockZone(ThreadLock& lock) : lock_(lock) { lock_.Lock();   }
    ~ThreadLockZone()                              { lock_.Unlock(); }
private:
    ThreadLock& lock_;
};

//////////////////////////////////////////////////////////////////////////
#endif//__MINI_THREAD_HPP__
