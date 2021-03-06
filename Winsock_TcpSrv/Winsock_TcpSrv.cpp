// Winsock_TcpSrv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//需要与Ws2_32.lib链接
#pragma comment(lib, "ws2_32.lib")
#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#include <Windef.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
using namespace std;

/*
1>------ 已启动全部重新生成: 项目: Winsock_TcpSrv, 配置: Release Win32 ------
1>pch.cpp
1>Winsock_TcpSrv.cpp
1>k:\git\repos\vc-projects\winsock_tcpsrv\winsock_tcpsrv.cpp(111): warning C4996: 'inet_ntoa': Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
1>e:\windows kits\10\include\10.0.17134.0\um\winsock2.h(1848): note: 参见“inet_ntoa”的声明
1>正在生成代码
1>All 15 functions were compiled because no usable IPDB/IOBJ from previous compilation was found.
1>已完成代码的生成
1>Winsock_TcpSrv.vcxproj -> K:\Git\Repos\VC-Projects\Release\Winsock_TcpSrv.exe
1>已完成生成项目“Winsock_TcpSrv.vcxproj”的操作。
========== 全部重新生成: 成功 1 个，失败 0 个，跳过 0 个 ==========

 */

/*
 * 读取客户端数据，并回射给客户端，直到客户端关闭连接，则服务端关闭连接。
 */
void do_service(SOCKET conn)
{  
	cout << "========== 开始服务客户端【" << conn << "】========== " << endl;
	char buf[104] = { 0 };
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		int ret = recv(conn, buf, sizeof(buf), 0);

		if (ret == SOCKET_ERROR)
		{
			cout << "读取数据出错：error with code = " << WSAGetLastError();
			// exit(1);
			break;
		}

		if (ret == 0)
		{
			cout << "client close" << endl;

			cout << "sleeping..." << endl;
			Sleep(15 * 1000);
			cout << "Wake up" << endl;

			//memset(buf, 0, sizeof(buf));
			//char data[] = "robbin";
			//strcpy(buf, data);
			//send(conn, buf, strlen(buf), 0); // 测试客户端关闭，服务器再发送数据
			break;	
		} 

		cout << "接收数据：" << buf << endl;

		// 服务器主动关闭连接
		if (strcmp(buf, "server_close") == 0)
		{
			closesocket(conn);
			/*while (true)
			{
				Sleep(5000);
				memset(buf, 0, sizeof(buf));
				int ret = recv(conn, buf, sizeof(buf), 0);
				cout << "接收数据2：" << buf << endl;
			}*/

			break; 
		}

		send(conn, buf, strlen(buf), 0); // 回射
	}
	cout << "准备关闭客户端连接【" << conn << "】" << endl;
	closesocket(conn);
	cout << "关闭客户端连接【" << conn << "】成功" << endl;
	cout << "========== 服务客户端连接【" << conn << "】结束！========== " << endl;
	
}

int main()
{   
	Sleep(15 * 1000);
	cout << "Main Wake up" << endl;

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

	// 创建SOCKET
	SOCKET listenfd;
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenfd == INVALID_SOCKET)
	{
		cout << "创建监听SOCKET出错，error with code = " << WSAGetLastError() << endl;
		exit(1);
	}

	cout << "创建服务端监听Socket成功：listenfd:" << listenfd << endl;
	 
	// 绑定
	sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // IP地址
	serveraddr.sin_port = htons(8888);              // 端口号

	int ret;
	ret = bind(listenfd, (sockaddr *)&serveraddr, sizeof(serveraddr));
	if (ret == SOCKET_ERROR)
	{
		cout << "绑定端口号出错，error with code = " << WSAGetLastError();
		exit(1);
	}

    // 监听
	ret  = listen(listenfd, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		cout << "监听Socket出错，error with code = " << WSAGetLastError();
		exit(1);
	}

	cout << "开始监听..." << endl;

	// 授受连接
	sockaddr_in peeraddr; // 对等端socket
	int peerlen;
	SOCKET conn;
	while (1)
	{
		peerlen = sizeof(peeraddr);
		cout << "接受连接中..." << endl;
		conn = accept(listenfd, (sockaddr *)&peeraddr, &peerlen);
		if (conn == INVALID_SOCKET)
		{
			cout << "接受请求出错,error with code = " << WSAGetLastError()<< endl;
			exit(1);
		}

		

       // 严重性	代码	说明	项目	文件	行	禁止显示状态
       // 错误	C4996	'inet_ntoa': Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings	Winsock_TcpSrv	k : \git\repos\vc - projects\winsock_tcpsrv\winsock_tcpsrv.cpp	103
	   //  warning C4996: 'inet_ntoa': Use inet_ntop() or InetNtop() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

		// inet_ntoa 将一个十进制网络字节序转换为点分十进制IP格式的字符串。
		cout << "接受客户端:" << inet_ntoa(peeraddr.sin_addr) << ":" << ntohs(peeraddr.sin_port) << endl;
	
		// 创建连接之后，就关闭
		// closesocket(conn);

		// recv_after_close(conn);

		do_service(conn);
	}

	WSACleanup();
    std::cout << "服务端程序运行结束!\n"; 

	return 0;
}