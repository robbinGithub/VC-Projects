#include "BankSession.h"
#include "../Public/Exception.h"
#include "../Public/Singleton.h"

BankSession::BankSession(std::auto_ptr<Socket>& socket):socket_(socket)
{
	requestPack_ = (RequestPack*)buffer_;
}


BankSession::BankSession(std::auto_ptr<Socket>& socket)
{
}

BankSession::~BankSession()
{
}

void BankSession::Process()
{
	Recv();     // ������������
	DoAction(); // ��������ִ����Ӧ��ҵ���߼�
}

void BankSession::Send(const char * buf, size_t len)
{
}

void BankSession::Recv()
{
	int ret;
	// ���հ�ͷ
	ret = socket_->RecvN(buffer_, sizeof(RequestHead));
	if (ret == 0)
		throw Exception("�ͻ��˹ر�");
	else if (ret != sizeof(RequestHead))
	{
		throw Exception("�������ݰ�����");
	}

	uint16 cmd = Endian::NetworkToHost16(requestPack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(requestPack_->head.len);

	// ���հ���+��β
	ret = socket_->RecvN(/*buffer_+sizeof(RequestHead)*/requestPack_->buf, len);
	if (ret == 0)	// �ͻ��˹ر�
		throw Exception("�ͻ��˹ر�");
	else if (ret != len)
	{
		throw Exception("�������ݰ�����");
	}

	// ����Hash
	unsigned char hash[16]; // 16�ֽ�
	MD5 md5;         
	md5.MD5Make(hash, (unsigned char const  *) buffer_, sizeof(RequestHead) + len - 8);

	if (memcmp(hash, buffer_ + sizeof(RequestHead) + len - 8, 8))
		throw Exception("��������ݰ�");

	requestPack_->head.cmd = cmd;
	requestPack_->head.len = len;
}

void BankSession::DoAction()
{
	// Singleton<TransactionManager>::Instance().DoAction(*this);
}
