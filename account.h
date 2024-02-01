#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <iostream>
#include "fund.h"
#include <vector>
#include"transaction.h"
using namespace std;

class Account {
public:
	// Constructor and Desctructor
	Account();
	Account(int id, const string& name);
	~Account();

	// Getters-Setters
	int id() const;
	void setId(int id);

	//Action
	bool ExecuteWithdrawal(int fundIndex, int amountToWithdraw, Transaction& transaction);
	bool HandleLinkedFundWithdrawal(int fundIndex, int amount);
	bool Deposit(int fundIndex, int depositAmount);
	void AddTransaction(int fundIndex, const Transaction& transaction);
	void PrintAllDetails() const;
	
	// Operator
	friend ostream& operator<<(ostream& stream, const Account& rhs);

private:
	int id_;
	string name_;
	vector<Fund> funds_;
};
#endif


