#ifndef FUND_H_
#define FUND_H_
#include "transaction.h"
#include <vector>
#include <iostream>

#include <iostream>

class Fund {
public:
	// Construtor and Destructor
	Fund();
	Fund(int balance, const string& fundName);
	~Fund();

	// getters and setters
	int currentBalance() const;
	string fundName() const;

	// Actions
	void UpdateBalance(int amount);
	void RecordTransaction(const Transaction& newTransation);
	void DisplayFundDetails() const;

	// Overloaded operators
	friend ostream& operator<<(ostream& stream, Fund rhs);
private:
	vector<Transaction> transactionsHistory_;
	int currentBalance_;
	string fundName_;
	
};
#endif
