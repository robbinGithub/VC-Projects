#include "Server.h"
#include "BankThread.h"

#include "../Public/Socket.h"
#include "../Public/Logging.h"

#include <memory>
#include <iostream>
#include <sstream>

int Server::start()
{
	LOG_INFO << "����������...";
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

Server::Server() : config_("server.conf")
{
	Socket::Startup();
	serverIp_ = config_.GetProperty("SERVER.SERVER_IP");
	string port = config_.GetProperty("SERVER.PORT");

	stringstream ss;
	ss << port;
	ss >> port_;

	dbServerIp_ = config_.GetProperty("DB.IP");

	port = config_.GetProperty("DB.PORT");
	ss.clear();
	ss.str("");
	ss << port;
	ss >> dbServerPort_;

	dbUser_ = config_.GetProperty("DB.USER");
	dbPass_ = config_.GetProperty("DB.PASS");
	dbName_ = config_.GetProperty("DB.NAME");

	ss.clear();
	ss.str("");
	string interetRate = config_.GetProperty("BANK.INTERATE");
	if (interetRate.empty())
	{
		interetRate_ = 0.0035;
	}
	else
	{
		ss << interetRate;
		ss >> interetRate_;
	}
}

Server::~Server()
{
	Socket::Cleanup();
}
