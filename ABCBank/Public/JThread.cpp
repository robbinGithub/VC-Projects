#include "JThread.h"

#include <process.h>

using namespace PUBLIC;

JThread::JThread(bool isAutoDel)
	: isAutoDel_(isAutoDel)
{
	hThread_ = NULL;
	threadId_ = 0;
}

JThread::~JThread()
{
	if (hThread_ != NULL)
	{
		CloseHandle(hThread_);
		hThread_ = NULL;
	}
}
bool JThread::Start()
{
	// _beginthreadex是一个C运行时库的函数，CreateThread是一个系统API函 数，_beginthreadex内部调用了CreateThread
	hThread_ = (HANDLE)_beginthreadex(NULL,0,ThreadFun,(void*)this,0,&threadId_);
	return (hThread_ != NULL); 
}

unsigned __stdcall JThread::ThreadFun(void *p)
{
	JThread* jtp = (JThread*)p;
	jtp->Run();
	if (jtp->isAutoDel_)
	{
		delete jtp;
	}
	return 0;
}

void JThread::SetAutoDel(bool flag)
{
	isAutoDel_ = flag;
}

void JThread::Wait(DWORD timeout)
{
	WaitForSingleObject(hThread_,timeout);
}
