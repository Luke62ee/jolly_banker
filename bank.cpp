#include "bank.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

Bank::Bank() 
{
    
}

Bank::~Bank()
{
}

void Bank::Process(Transaction transaction)
{
    
    // Get the transaction type.
    // Stream to parse transaction command.
    // Queue to hold transaction details.
    string transactionCmd = transaction.transactionType();
    stringstream cmdStream(transactionCmd);
    string transactionPart;
    queue <string> transactionDetails;

    // Parse the transaction command into parts and store in the queue.
    for (string transactionPart; cmdStream >> transactionPart; ) 
    {
        transactionDetails.push(transactionPart);
    }

    // Get transaction identifier
    string letter = transactionDetails.front();
    transactionDetails.pop();
    string temp = transactionDetails.front();
   
    // Get account ID
    int id = stoi(temp);
    transactionDetails.pop();

    if (letter == "O") 
    {
        // Combining first and last names from transaction details to form the full name of the account holder.
        string firstName = transactionDetails.front();
        transactionDetails.pop();
        string lastName = transactionDetails.front();
        transactionDetails.pop();
        string fullName = firstName + " " + lastName;

        // Creating a new account with the provided ID and full name, then inserting it into the bank's account tree.
        Account* newAccount = new Account(id, fullName);
        accounts_.Insert(id, newAccount); 
        return;
    }

    if (letter == "D") 
    {
        // Extracting fund number and deposit amount from transaction details
        int fund = stoi(transactionDetails.front());
        transactionDetails.pop();
        int deposit = stoi(transactionDetails.front());
        transactionDetails.pop();

       // Retrieving account and performing deposit operation
        Account* targetAccount = nullptr;
        bool operationResult = accounts_.Retrieve(id, targetAccount);
        if (operationResult) 
        {
            // Perform deposit and set transaction success status accordingly.
            bool depositSuccess = targetAccount->Deposit(fund, deposit);
            transaction.setSuccessful(depositSuccess);
            targetAccount -> AddTransaction(fund, transaction);  
        }
        else 
        {
            transaction.setSuccessful(false);
        }
        return;
    }

    
    if (letter == "W") {
        int fund = stoi(transactionDetails.front());
        transactionDetails.pop();
        int withdrawl = stoi(transactionDetails.front());
        transactionDetails.pop();

        // Retrieving the target account for the withdrawal.    
        Account* targetAccount = nullptr;
        accounts_.Retrieve(id, targetAccount);

        // If the account is found, execute the withdrawal.
        if(targetAccount)
        {
            targetAccount -> ExecuteWithdrawal(fund, withdrawl, transaction);
            return;
        }
    }

    if (letter == "T") 
    {
        // Figure out what funds are being used in the transfer
        int fromFund = stoi(transactionDetails.front());
        transactionDetails.pop();
        int recipientId = stoi(transactionDetails.front());
        transactionDetails.pop();
        int toFund = stoi(transactionDetails.front());
        transactionDetails.pop();
        int transferAmount = stoi(transactionDetails.front());

        // Retrieving the source account for the transfer.
        Account* sourceAccount = nullptr;
        bool sourceFound = accounts_.Retrieve(id, sourceAccount);

        // If the source account is found, use the TransferHelper method to execute the transfer.
        if (sourceFound && sourceAccount) 
        {
            if (TransferHelper(sourceAccount, fromFund, recipientId, toFund, transferAmount, transaction)) 
            {
                transaction.setSuccessful(true);
            } 
            else 
            {
                transaction.setSuccessful(false);
            }
        }
        return;
    }


    if (letter == "A") {

        // Retrieve the account using the provided ID
        Account* clientAccount = nullptr;
        bool accountExists = accounts_.Retrieve(id, clientAccount);

        // If the account exists, print all its transaction details.
        if (accountExists && clientAccount)
        {
            clientAccount -> PrintAllDetails();
        }
        return;
    }


    if (letter == "F") 
    {
        Account* clientAccount = nullptr;
        bool isAccountRetrieved = accounts_.Retrieve(id, clientAccount);


        // If the account is found, print the transaction history for a specific fund.
        if (isAccountRetrieved && clientAccount)
        {
            int fundId = stoi(transactionDetails.front());
            transactionDetails.pop();

            clientAccount -> PrintAllDetails();
        }
    }
}

// Facilitates transferring funds between accounts.
bool Bank::TransferHelper(Account* sourceAccount, int fromFund, int recipientId, int toFund, int amount, Transaction& transaction) 
{
    // Attempt withdrawal from the source account.
    bool withdrawalResult = sourceAccount->ExecuteWithdrawal(fromFund, amount, transaction);

    // If withdrawal successful, proceed with deposit into recipient account.
    if (withdrawalResult) 
    {
        Account* recipientAccount = nullptr;
        bool recipientFound = accounts_.Retrieve(recipientId, recipientAccount);

        // If recipient account found, deposit and record the transaction.
        if (recipientFound && recipientAccount) 
        {
            recipientAccount->Deposit(toFund, amount);
            recipientAccount->AddTransaction(toFund, transaction);
            return true;
        } 
        else 
        {
            // Reverting withdrawal due to recipient account not found
            sourceAccount->Deposit(fromFund, amount);
        }
    }
    return false;
}



// Reads commands in from a file and pushes them to a Queue in the form of Transaction objects
void Bank::Read(const string& filename) {
    
    ifstream file(filename);
    string line;
    
    while (getline(file, line))
    {
        if(!line.empty())
        {
            Transaction newTransaction(line, true);
            transactions_.push(newTransaction);
        }
    }
    file.close();
    ProcessTransactionQueue();
    PrintAccountBalances();
}

// Processes each transaction in the transaction queue.
void Bank::ProcessTransactionQueue()
{
    while (!transactions_.empty())
    {
        Transaction currentTransaction = transactions_.front();
        Process(currentTransaction);
        transactions_.pop();
    }
}

// Prints the balances of all accounts in the bank.
void Bank::PrintAccountBalances() const
{
    cout << "Account Balance:" << endl;
    accounts_.Print();
}

