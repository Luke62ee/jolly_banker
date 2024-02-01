#include "bstree.h"
#include <iostream>
using namespace std;


BSTree::BSTree() {
	root_ = nullptr;
}

// Delete all the data in the tree
BSTree::~BSTree() {
	this->Delete();
}

bool BSTree::Insert(int id, Account* account) {
	Node* temp = new Node; // Allocate new node
    temp->p_acct = account;
    temp->left = nullptr;
    temp->right = nullptr;

	// If the tree is empty, set the new node as root and return true.
    if (root_ == nullptr) 
	{
        root_ = temp; 
        return true;
    }

    Node* current = root_;
    while (true) {

		 // Check if account ID matches the current node's account ID.
        if (id == current-> p_acct -> id()) 
		{
            cerr << "ERROR: Account " << id << " is already open. Transaction refused." << endl;
            delete temp; 
            return false;
        }

		// Navigate to the left or right child based on account ID comparison.
        if (id < current -> p_acct -> id()) 
		{
            if (current->left == nullptr) 
			{
                current->left = temp;
                return true;
            }

			// Move to the left child.
            current = current->left;
        } 
		else 
		{
            if (current->right == nullptr) 
			{
                current->right = temp;
                return true;
            }

			// Move to the right child.
            current = current->right;
        }
    }
} 

// Retrieves an account based on its ID.
// Call the helper function to search for the account starting from the root of the tree since the tree is private.
bool BSTree::Retrieve(const int id, Account*& account) const
{
	return (RetrieveHelper(id, account, this->root_));
}


// Helper function to recursively search for an account in the tree.
bool BSTree::RetrieveHelper(const int id, Account*& account, Node* current) const {
	
	// Base case: If current node is null, account not found.
	if (!current) {
		cerr << "ERROR: Account " << id << " not found." << endl;
		return false;
	}

	int CurrentID = current -> p_acct -> id();
	if (CurrentID == id)
	{
		// Account found, assign it to the reference
		account = current -> p_acct;
		return true;
	}

	// Determine the direction of the search (left or right) and recurse accordingly.
	bool isLeftSearch = id < CurrentID;
	Node* nextNode = isLeftSearch ? current -> left : current -> right;
	
	return RetrieveHelper(id, account, nextNode); 
}


void BSTree::Print()const 
{
	PrintHelper(this->root_);
}


// Prints the accounts in the tree in an in-order traversal.
// In this case, the order will be incremental 
// A private method that can be used inside this code
// But can be called by Print
void BSTree::PrintHelper(Node* current) const 
{
	
	// If the tree is empty, then return
	if (!current)
	{
		return;
	}

	PrintHelper(current -> left);
	cout << *current -> p_acct << endl;
	PrintHelper(current -> right);
}

void BSTree::Delete() 
{
	DeleteHelper(this->root_);
}

// Deletes the tree using post-order traversal
// // A private method that can be used inside this code
// But can be called by Delete
void BSTree::DeleteHelper(Node* current) 
{

	if (!current) {
		return;
	}

	DeleteHelper(current -> left);
	DeleteHelper(current -> right);

	delete current -> p_acct;
	delete current;
}
