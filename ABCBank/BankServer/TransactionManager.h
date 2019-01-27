#ifndef _TRANSACTIONMANAGER_H_
#define _TRANSACTIONMANAGER_H_

#include "../Public/Singleton.h"
#include "CMD/Transaction.h"
#include "BankSession.h"
#include <map>
#include <string>
using namespace std;

using namespace CMD;

class TransactionManager
{
	friend class Singleton<TransactionManager>;

public:
	bool DoAction(BankSession& session);
private:
	map<uint16, Transaction*> m_actions;
	TransactionManager();
	TransactionManager(const TransactionManager& rhs);
	~TransactionManager();
};
#endif

