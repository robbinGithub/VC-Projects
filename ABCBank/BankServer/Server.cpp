#include "Server.h"
#include "BankThread.h"
#include "../Public/Socket.h"
#include <memory>

int Server::start()
{
	Socket sock;
	sock.Create();
	if (!sock.Bind(NULL, 8888))
	{
		return 1;
	}

	if (!sock.Listen())
	{
		return 1;
	}

	while (1)
	{   
	
		// Socket conn; 循环结束，就释放,close掉了，传递至线程中也不能使用了
		// Socket* conn = new Socket(); 出现异常，无法销毁
		// 使用智能指针
		std::auto_ptr<Socket> conn(new Socket); 
		conn->socket_ = sock.Accept();
		if (!conn->IsValid())
			continue;

		// 线程结构体销毁，在线程执行完毕时，根据销毁标记AutoCode，释放
		// 不能使用局部对象（栈上)，否则线程执行依赖对象BankThread，线程未执行完毕，BankThread被释放掉了
		BankThread * bt = new BankThread(conn); // conn传递给线程
		bt->SetAutoDel(true); 
		bt->Start();
	}

	return 0;
}

Server::Server()
{
	Socket::Startup();
}

Server::~Server()
{
	Socket::Cleanup();
}
