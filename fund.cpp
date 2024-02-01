#include "fund.h"
#include <iostream>


Fund::Fund()
{
	currentBalance_ = 0;
	fundName_ = "Default Fund";
}

Fund::Fund(int balance, const string &fundName)
{
	currentBalance_ = balance;
	fundName_ = fundName;
}

Fund::~Fund()
{
}

int Fund::currentBalance() const
{
    return currentBalance_;
}

string Fund::fundName() const
{
    return fundName_;
}

// Showing the newest amount of balance
void Fund::UpdateBalance(int amount)
{
	currentBalance_ += amount;
}

void Fund::RecordTransaction(const Transaction &newTransation)
{
	transactionsHistory_.push_back(newTransation);
}

// Displays the details of the fund, including its name, current balance, and transaction history.
void Fund::DisplayFundDetails() const
{
	cout << fundName_ << ": $" << currentBalance_ << endl;
	if (!transactionsHistory_.empty())
	{
		for (const auto& transaction : transactionsHistory_)
		{
			cout << transaction << endl;
		}
	}

}

ostream &operator<<(ostream &stream, Fund rhs)
{
    stream << rhs.fundName() << ": $" << rhs.currentBalance();
	return stream;
}
