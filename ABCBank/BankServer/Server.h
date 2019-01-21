#ifndef _SERVER_H_
#define _SERVER_H_H

#include "../Public/Singleton.h"
#include "../Public/Socket.h"
using namespace PUBLIC;
class Server
{
	friend class Singleton<Server>;
public:
	int start();
private:
	Server();
	Server(const Server& rhs);
	~Server();
};

#endif

