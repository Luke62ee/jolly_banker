#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <string>
#include <iostream>
using namespace std;

class Transaction {
public:
	// Constructor and Desctuctor
	Transaction();
	Transaction(string transactionType, bool isSuccessful);
	~Transaction();

	// Getter-Setter
	string transactionType();
	bool isSuccessful();
	void setSuccessful(bool isSuccessful);

	// Operator
	friend ostream& operator<<(ostream& stream, const Transaction& rhs);

private:
	string transactionType_;
	bool isSuccessful_;
};
#endif
