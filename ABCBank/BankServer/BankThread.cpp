#include "BankThread.h"
#include <vector>
#include <string>
#include "../Public/StringUtil.h"
#include "../Public/Logging.h"
#include "BankSession.h"
#include "../Public/Exception.h"

using namespace PUBLIC;

BankThread::BankThread(std::auto_ptr<Socket>& socket):socket_(socket )
{
}

BankThread::~BankThread()
{
}

void BankThread::Run()
{
	/*int ret;
	while (1)
	{
		char buffer[1024] = { 0 };
		ret = socket_->Recv(buffer, sizeof(buffer));
		if (ret == -1)
		{
			LOG_INFO << "读取网络消息错误";
			break;
		}

		if (ret == 0)
		{
			LOG_INFO << "客户端关闭";
			break;
		}

		std::vector<std::string> v = StringUtil::Split(buffer, '#');
		if (v.size != 2)
		{
			LOG_INFO << "请求数据错误";
			break;
		}
		else
		{
			LOG_INFO << "use="<<v[0]<< "pass="<<v[1];
		}

		socket_->Send(buffer, ret);
	}*/

	BankSession* bs = new BankSession(socket_);
	while(!bs->IsDead())
	try
	{
		bs->Process();
	}
	catch (Exception& e)
	{
		LOG_INFO << e.what();
		bs->Kill();
	}

	delete bs;
}

