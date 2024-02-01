#ifndef BANK_H_
#define BANK_H_
#include <vector>
#include <iostream>
#include <queue>
#include "bstree.h"
#include "account.h"
#include "transaction.h"

using namespace std;

class Bank {
public:
	// Constructor and Destructor
	Bank();
	~Bank();

	// Action
	void Read(const string& filename);
	void Process(Transaction treansation);	
	bool TransferHelper(Account* sourceAccount, int fromFund, int recipientId, int toFund, int amount, Transaction& transaction);
	void ProcessTransactionQueue();
	void PrintAccountBalances() const;


private:
	queue<Transaction> transactions_;
	BSTree accounts_;

};
#endif
