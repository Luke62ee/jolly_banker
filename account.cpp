#include "account.h"
#include <iostream>
#include "fund.h"
using namespace std;

Account::Account()
{
	id_ = 0;
	name_ = "";
}

Account::Account(int id, const string &name)
{
	id_ = id;
	name_ = name;

    // Initialize the funds in the account. 
    // The 'Fund' objects are added to the 'funds_' vector which holds all the funds for this account.
    // The initial balance for most funds is set to 0, except for the "Money Market" fund.
    // "Money Market" should be 200 based on instruction

	funds_.push_back(Fund(200, "Money Market"));
	funds_.push_back(Fund(0, "Prime Money Market"));
	funds_.push_back(Fund(0, "Long-Term Bond"));
	funds_.push_back(Fund(0, "Short-Term Bond"));
	funds_.push_back(Fund(0, "500 Index Fund"));
	funds_.push_back(Fund(0, "Capital Value Fund"));
	funds_.push_back(Fund(0, "Growth Equity Fund"));
	funds_.push_back(Fund(0, "Growth Index Fund"));
    funds_.push_back(Fund(0, "International Fund"));
}

Account::~Account()
{
}

int Account::id() const
{
    return id_;
}

void Account::setId(int id)
{
    id_ = id;
}

// Executes a withdrawal from a specified fund of an account.
bool Account::ExecuteWithdrawal(int fundIndex, int amountToWithdraw, Transaction &transaction)
{
    // Check if the fund is one of the first four (linked funds) and if it has insufficient balance.
    // These funds are linked with another fund, so a special handling for withdrawal is required.
    // Attempt withdrawal from the linked fund if the primary fund has insufficient balance.
    if (fundIndex < 4 && funds_[fundIndex].currentBalance() < amountToWithdraw) 
    {
        bool isSuccess = HandleLinkedFundWithdrawal(fundIndex, amountToWithdraw);
        if (!isSuccess) 
        {
            cerr << "ERROR: Not enough funds to withdraw " << amountToWithdraw << " from " << name_ << " " << funds_[fundIndex].fundName() << endl;
        }
        return isSuccess;
    }

    // Standard withdrawal
    if (funds_[fundIndex].currentBalance() >= amountToWithdraw) 
    {
        funds_[fundIndex].UpdateBalance(-amountToWithdraw);
        transaction.setSuccessful(true);
    }
     // If the fund has insufficient balance, print an error message and transaction history. 
    else 
    {
        cerr << "ERROR: Not enough funds to withdraw " << amountToWithdraw << " from " << name_ << " " << funds_[fundIndex].fundName() << endl;
        transaction.setSuccessful(false);
        cout << "Transaction History for " << name_ << " by fund." << endl;
        
        // Display details of all funds for this account.
        for (const auto& fund : funds_) 
        {
            fund.DisplayFundDetails();
        }
    }

    // Record this transaction in the account's transaction history
    AddTransaction(fundIndex, transaction);
    return transaction.isSuccessful();
}

// Handles the withdrawal process when funds are linked and the primary fund has insufficient balance.
bool Account::HandleLinkedFundWithdrawal(int fundIndex, int amount)
{
    // Determine the index of the linked fund based on the fundIndex.
    // For indices 0 and 1, they are linked with each other, as are indices 2 and 3.
    int linkedFundIndex = (fundIndex < 2) ? (fundIndex == 0 ? 1 : 0) : (fundIndex == 2 ? 3 : 2);
    
    // Calculate the current balances of the primary and linked funds
    int primaryBalance = funds_[fundIndex].currentBalance();
    int linkedBalance = funds_[linkedFundIndex].currentBalance();


    // Check if the combined balance of the primary and linked fund is less than the withdrawal amount.
    if (primaryBalance + linkedBalance < amount) 
    {
        return false;  
    }

    // Calculate the amount to withdraw from the primary fund. 
    // Withdraw as much as possible from the primary fund before using the linked fund.
    int withdrawFromPrimary = min(amount, primaryBalance);
    funds_[fundIndex].UpdateBalance(-withdrawFromPrimary);
    funds_[linkedFundIndex].UpdateBalance(-(amount - withdrawFromPrimary));

    // Record transactions for both funds
    string transactionDescPrimary = "Withdrawal from Fund: " + to_string(fundIndex) + " Amount: " + to_string(withdrawFromPrimary);
	Transaction transactionPrimary(transactionDescPrimary, true);  // Assuming withdrawal was successful
	AddTransaction(fundIndex, transactionPrimary);

    // Create transaction for linked fund.
	string transactionDescLinked = "Withdrawal from Linked Fund: " + to_string(linkedFundIndex) + " Amount: " + to_string(amount - withdrawFromPrimary);
	Transaction transactionLinked(transactionDescLinked, true);  // Assuming withdrawal was successful
	AddTransaction(linkedFundIndex, transactionLinked);
    return true;
}

// Deposits an amount into a specified fund of the account.
bool Account::Deposit(int fundIndex, int depositAmount) 
{
	// Validate the fund index.
    if (fundIndex < 0 || fundIndex >= funds_.size())
	{
		cerr << "Invalid fund index: " << fundIndex << endl;
		return false;
	}

	funds_[fundIndex].UpdateBalance(depositAmount);
	return true;
}

// Adds a transaction record to a specified fund.
void Account::AddTransaction(int fundIndex, const Transaction &transaction)
{
	if (fundIndex >= 0 && fundIndex < funds_.size()) 
    {
        funds_[fundIndex].RecordTransaction(transaction);
    } 
    else 
    {
        cerr << "Invalid fund index: " << fundIndex << endl;
    }
}

//// Prints the transaction history for all funds of the account.
void Account::PrintAllDetails() const
{
	cout << "Transaction History for " << name_ << " by fund." << endl;
    for (const auto& fund : funds_) 
    {
        fund.DisplayFundDetails();
    }
}


ostream& operator<<(ostream& stream, const Account& rhs) 
{
	stream << rhs.name_ << " Account ID: " << rhs.id_ << endl;
	for (int i = 0; i < 9; i++) 
    {
		stream << rhs.funds_[i] << endl;
	}
	return stream;
}

