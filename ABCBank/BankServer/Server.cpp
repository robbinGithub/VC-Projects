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
	
		// Socket conn; ѭ�����������ͷ�,close���ˣ��������߳���Ҳ����ʹ����
		// Socket* conn = new Socket(); �����쳣���޷�����
		// ʹ������ָ��
		std::auto_ptr<Socket> conn(new Socket); 
		conn->socket_ = sock.Accept();
		if (!conn->IsValid())
			continue;

		// �߳̽ṹ�����٣����߳�ִ�����ʱ���������ٱ��AutoCode���ͷ�
		// ����ʹ�þֲ�����ջ��)�������߳�ִ����������BankThread���߳�δִ����ϣ�BankThread���ͷŵ���
		BankThread * bt = new BankThread(conn); // conn���ݸ��߳�
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
