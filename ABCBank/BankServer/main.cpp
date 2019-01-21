
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define _DEFINE_DEPRECATED_HASH_CLASSES 0


#include "server.h"


int main(void)
{  
	Singleton<Server>::Instance().start();
 	return 0;
}