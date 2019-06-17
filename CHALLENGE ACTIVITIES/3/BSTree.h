#ifndef BSTREE_H
#define BSTREE_H
#include "Node.h"

class BSTree
{
public:
	BSTree();
	void insert( const string &word);
	bool search(const string &key) const;
	string largest() const;
	string smallest() const;
	int height(const string &word) const;
	void remove(const string &word);
	void preOrder() const;
	void inOrder() const;
	void postOrder() const;
private:
	Node *root;
	bool search(Node *node, const string &key) const;
	int height(Node *node) const;
	Node* remove(Node *node, const string &key);
	Node* minNode(Node *node);
	void preOrder(Node* node) const;
	void inOrder(Node* node) const;
	void postOrder(Node* node) const;
	
	Node* findMax(Node* node);
	Node* findMin(Node* node);
};

#endif
