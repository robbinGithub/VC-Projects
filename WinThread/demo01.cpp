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


//DWORD ���� unsigned long
//int�����Ż���λ���Ĳ�ͬ�������仯��������16λ����Ϊ16Ϊ����32λ����Ϊ32λ����64λ����Ϊ64λ��������ԭʼ�Ķ����֪���ˡ�
// DWORD һ�����ڷ���ֵ�����и��������

DWORD  WINAPI ThreadProc(PVOID lpParameter)
{   
	cout << "GetCurrentThreadId()=" << GetCurrentThreadId() << endl;
	int n = (int)lpParameter;
	while (n--)
	{
		Sleep(1000);
		cout <<"this is a test " << n << endl;
	}
	cout << "���߳̽���!" << endl;
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

	SuspendThread(hThread); // �������+1
	ResumeThread(hThread);  // �������-1
	/*

	// ��ѯ�߳��Ƿ��˳�,����CPU��Դ
	DWORD exitCode = 0;
	do
	{
		GetExitCodeThread(hThread, &exitCode);
	} while (exitCode == STILL_ACTIVE);
	
	cout << "���߳̽���!" << endl;*/
	
	// �ȴ����ȴ����Ķ����ڼ���״̬��ʱ
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

	// ��ιرվ��
	// CloseHandle(hThread);
	// 0x7730BD37 ��(λ�� WinThread.exe ��)�������쳣: 0xC0000008: An invalid handle was specified��

	cout << "���߳̽���!" << endl;
	system("pause");

	return 0;
}