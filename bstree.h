#ifndef BSTREE_H_
#define BSTREE_H_
#include "account.h"

class BSTree {
public:
	// Constructor and Descructor
	BSTree();
	~BSTree();

	// Actions
	bool Insert(int id, Account* account);
	bool Retrieve(const int id, Account*& account) const;
	void Print()const;
	void Delete(); 
	

private:
	struct Node
	{
		Account* p_acct;
		Node* right;
		Node* left;
	};
	Node* root_;	
	void PrintHelper(Node* root_node) const;
	void DeleteHelper(Node* current);
	bool RetrieveHelper(const int id, Account*& account, Node* current) const;
};
#endif