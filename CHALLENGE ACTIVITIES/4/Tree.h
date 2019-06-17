#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string & str) ;
  void preOrder() const;
  void preOrder(Node *current) const;
  void inOrder() const;
  void inOrder(Node *current) const;
  void postOrder() const;
  void postOrder(Node*current) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  void split(Node* current, const string & word);  
  bool isTwo(Node*current) const;
  bool isThree(Node*current) const;
  Node* search(Node *current, const string &movie) const;
  bool ifLeaf(Node *x) const; 
  void deleteNode(Node *x);
  Node* getNext(Node *current, const string &movie) const;
  Node* getSibling(Node *current);
  void removeNode(Node *current);
  
};

#endif
