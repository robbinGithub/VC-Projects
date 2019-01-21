#ifndef _BANKTHREAD_H_
#define _BANKTHREAD_H_

#include <memory>
#include "../Public/Socket.h"
#include "../Public/JThread.h"

using namespace PUBLIC;


class BankThread:public JThread
{
public:
	BankThread(std::auto_ptr<Socket>& socket);
	~BankThread();
	void Run();

	std::auto_ptr<Socket> socket_;  // 使用智能指针，不需要手工释放
};
#endif

