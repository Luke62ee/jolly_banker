#include "transaction.h"
#include <iostream>

// Constructor for Transaction class, initializes a transaction with its type and success status.
Transaction::Transaction()
{
	transactionType_ = "";
	isSuccessful_ = false;
}

Transaction::Transaction(string transactionType, bool isSuccessful)
{
	transactionType_ = transactionType;
	isSuccessful_ = isSuccessful;
}

Transaction::~Transaction()
{
}

string Transaction::transactionType()
{
    return transactionType_;
}

// Returns the success status of the transaction as a boolean value.
bool Transaction::isSuccessful()
{
    return isSuccessful_;
}

// Sets the success status of the transaction.
void Transaction::setSuccessful(bool isSuccessful)
{
	isSuccessful_ = isSuccessful;
}

ostream &operator<<(ostream &stream, const Transaction& rhs)
{
    stream <<  " " << rhs.transactionType_;
	if (!rhs.isSuccessful_)
	{
		stream << "(failed)"; 
	}
	return stream;
}
