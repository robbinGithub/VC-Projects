#include <Windows.h>
#include <iostream>
using namespace std;

//static HANDLE CreateThread(
//	LPSECURITY_ATTRIBUTES lpsa,
//	DWORD dwStackSize,
//	LPTHREAD_START_ROUTINE pfnThreadProc,
//	void* pvParam,
//	DWORD dwCreationFlags,
//	DWORD* pdwThreadId
//) throw();
//Param


//DWORD 代表 unsigned long
//int会随着机器位数的不同而发生变化，比如在16位机上为16为，在32位机上为32位，在64位机上为64位。看看最原始的定义就知道了。
// DWORD 一般用于返回值不会有负数的情况

DWORD  WINAPI ThreadProc(PVOID lpParameter)
{   
	cout << "GetCurrentThreadId()=" << GetCurrentThreadId() << endl;
	int n = (int)lpParameter;
	while (n--)
	{
		Sleep(1000);
		cout <<"this is a test " << n << endl;
	}
	cout << "子线程结束!" << endl;
	return 0;
}

int main()
{  
	DWORD dwThreadId;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, (PVOID)5, 0, /*CREATE_SUSPENDED*/ &dwThreadId);
    if (hThread == NULL)
	{
		cout << "error with code" << GetLastError() << endl;
		exit(1);
	}
	ResumeThread(hThread);

	SuspendThread(hThread); // 挂起计数+1
	ResumeThread(hThread);  // 挂起计数-1
	/*

	// 轮询线程是否退出,消耗CPU资源
	DWORD exitCode = 0;
	do
	{
		GetExitCodeThread(hThread, &exitCode);
	} while (exitCode == STILL_ACTIVE);
	
	cout << "主线程结束!" << endl;*/
	
	// 等待：等待核心对象处于激发状态或超时
	DWORD ret;
	ret = WaitForSingleObject(hThread, INFINITE);

	if (ret == WAIT_FAILED) // WAIT_TIMEOUT
	{
		cout << "error with code" << GetLastError() << endl;
		exit(1);
	}
	else if (ret == WAIT_OBJECT_0)
	{
		cout << "wait success" << endl;
	}

	CloseHandle(hThread);

	// 多次关闭句柄
	// CloseHandle(hThread);
	// 0x7730BD37 处(位于 WinThread.exe 中)引发的异常: 0xC0000008: An invalid handle was specified。

	cout << "主线程结束!" << endl;
	system("pause");

	return 0;
}