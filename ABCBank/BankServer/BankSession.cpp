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
	Recv();     // 接收请求数据
	DoAction(); // 根据请求执行相应的业务逻辑
}

void BankSession::Send(const char * buf, size_t len)
{
}

void BankSession::Recv()
{
	int ret;
	// 接收包头
	ret = socket_->RecvN(buffer_, sizeof(RequestHead));
	if (ret == 0)
		throw Exception("客户端关闭");
	else if (ret != sizeof(RequestHead))
	{
		throw Exception("接收数据包出错");
	}

	uint16 cmd = Endian::NetworkToHost16(requestPack_->head.cmd);
	uint16 len = Endian::NetworkToHost16(requestPack_->head.len);

	// 接收包体+包尾
	ret = socket_->RecvN(/*buffer_+sizeof(RequestHead)*/requestPack_->buf, len);
	if (ret == 0)	// 客户端关闭
		throw Exception("客户端关闭");
	else if (ret != len)
	{
		throw Exception("接收数据包出错");
	}

	// 计算Hash
	unsigned char hash[16]; // 16字节
	MD5 md5;         
	md5.MD5Make(hash, (unsigned char const  *) buffer_, sizeof(RequestHead) + len - 8);

	if (memcmp(hash, buffer_ + sizeof(RequestHead) + len - 8, 8))
		throw Exception("错误的数据包");

	requestPack_->head.cmd = cmd;
	requestPack_->head.len = len;
}

void BankSession::DoAction()
{
	// Singleton<TransactionManager>::Instance().DoAction(*this);
}
