// Winsock_TcpCli.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma comment（lib，“ws2_32.lib”）  
// C:\Windows\SysWOW64\WSHTCPIP.DLL
// C:\Windows\SysWOW64\mswsock.dll

#define _WINSOCK_DEPRECATED_NO_WARNINGS  

#include "pch.h"
#include <iostream>

#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <Windef.h>


using namespace std;

void print_green(const char * content)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//设置绿色
	cout << content << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	//设置颜色，没有添加颜色，故为原色
}

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/*使用在Windef.h中声明的MAKEWORD（低字节，高字节）宏*/
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}

	// 1.创建客户端SOCKET
	SOCKET sock;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		cout << "error with code = " << WSAGetLastError();
		exit(1);
	}

	cout << "创建客户端SOCKET成功:Client SocketId:" << sock << endl;

	// 定义要连接的服务端地址和端口号
	sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	// 严重性	代码	说明	项目	文件	行	禁止显示状态
	// 警告	C4996	'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings	Winsock_TcpCli	k : \git\repos\vc - projects\winsock_tcpcli\winsock_tcpcli.cpp	48
	// @see https://blog.csdn.net/xiaolongrenstep/article/details/69828819
	serveraddr.sin_addr.s_addr = inet_addr("101.37.33.19"); // 服务端IP地址 101.37.33.19 127.0.0.1 
	serveraddr.sin_port = htons(8888);                   // 客户端口号

	// 2.连接服务端
	int ret;
	ret = connect(sock, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR)
	{
		cout << "error with code = " << WSAGetLastError();
		exit(1);
	}

	cout << "连接成功" << endl;
	char buf[1024] = { 0 };
	char recv_buf[1024] = { 0 };
	while (1)
	{

		memset(buf, 0, sizeof(buf));
		memset(recv_buf, 0, sizeof(recv_buf));
		cout << "================== 【Echo】==================" << endl;
		cin >> buf;

		// 客户端关闭连接
		if (strcmp(buf, "quit") == 0)
		{
			cout << "Quit!" << endl;	
			break;
		}
		if (strcmp(buf, "sd") == 0)
		{
			cout << "shutdown SEND..." << endl;
			shutdown(sock, SD_SEND);

			Sleep(10 * 1000);

			cout << "shutdown RECEIVE..." << endl;
			shutdown(sock, SD_RECEIVE);
			Sleep(10 * 1000);
			break;
		}
		
		// 客户端连接关闭之后，再发送数据报错：10038
		ret = send (sock, buf, strlen(buf), 0);
		if (ret == SOCKET_ERROR)
		{
			cout << "error with code = " << WSAGetLastError();
			exit(1);
		}
		print_green("发送成功");

		// 客户端连接关闭之后，再接收数据报错：10038
		ret = recv(sock, recv_buf, sizeof(recv_buf), 0);
		if (ret == SOCKET_ERROR)
		{
			cout << "error with code = " << WSAGetLastError();
			exit(1);
		}

		if (ret == 0)
		{
			cout << "server close" << endl;
			break; 
			// 客户端发送quit,服务器关闭socket,客户端再接收socket
		}
		if (ret > 0)
		{
			cout << "接收数据："<< recv_buf << endl;
		}
	}
	cout << "准备关闭Socket连接【" << sock << "】" << endl;
	closesocket(sock);
	cout << "关闭Socket连接【" << sock << "】成功" << endl;
	WSACleanup();
	std::cout << "客户端程序结束!\n";

	return 0;
}

