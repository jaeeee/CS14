#include "BSTree.h"

Node* BSTree::findMax(Node* node) {
    Node* x = node;
    while(x!=0 && x!=NULL) {
        x = x->right;
    }
    return x;
}

Node* BSTree::findMin(Node* node) {
    Node* y = node;
    while(y!=0 && y!=NULL) {
        y = y->right;
    }
    return y;
}

BSTree::BSTree() {
    root = NULL;
}

void BSTree::insert( const string &word) {
	if (word == "\n") {
		cout << "error nullpointer entered";
		return;
	}
	
	Node *newNode = new Node(word);
	/**
	 * Create a new tree
	 * 
	 * */
	if (root == NULL) {
		root = newNode;
		root->left = NULL;
		root->right = NULL;

		root->countIncrement();
	}
	else {
		Node *temp = root;
		while (temp != NULL) {
			if (newNode->data == temp->data) {
				
				temp->countIncrement();
				return;
			}

			if (newNode->data < temp->data) {
				if (temp->left == NULL) {
					temp->left = newNode;
					newNode->countIncrement();
					temp = NULL;
				}
				else {
					temp = temp->left;
				}
			}
			else {
				if (newNode->data > temp->data) {
					if (temp->right == NULL) {
						temp->right = newNode;
						newNode->countIncrement();
						temp = NULL;
					}
					else {
						temp = temp->right;
					}
				}
			}
		}
	}
}

bool BSTree::search(const string &key) const {
	bool yayornay = search(root, key);
	return yayornay;
}

string BSTree::largest() const {
	if (root == NULL)
		return "";

	string largest;
	Node *temp = root;

	while (temp->right != NULL)
	{
		temp = temp->right;
	}
	largest = temp->data;
	return largest;
}

string BSTree::smallest() const {
	if (root == NULL)
		return "";

	string smallest = "";
	Node *temp = root;

	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	smallest = temp->data; 
	return smallest;
}

int BSTree::height(const string &key) const {
	if (root == NULL) {
		return -1;
	}

	Node *temp = root;
	while (temp != NULL)
	{
		if (temp->data == key)
			break;
		else
		{
			if (temp->data > key)
			{
				temp = temp->left;
			}
			else
				temp = temp->right;
		}
	}

	int path = 0;

	if (temp == NULL)
		return -1;
	if (temp->left == NULL && temp->right == NULL)
		return 0;
	else
		path = height(temp);

	return path - 1;
}

void BSTree::remove(const string &key) {
    if(root->left == NULL && root->right == NULL) {
        delete root;
        root = NULL;
        return;
    }
	remove(root, key);
}

void BSTree::preOrder() const {
	preOrder(root);
}

void BSTree::inOrder() const {
	inOrder(root);
}

void BSTree::postOrder() const {
	postOrder(root);
}

bool BSTree::search(Node *node, const string &key) const {
	Node *temp = node;
	if (temp == NULL) {
		return false;
	}
	if (key == temp->data) {
		return true;
	}
	else {
		if (temp->data < key) {
			return search(temp->right, key);
		}
		else{
			return search(temp->left, key);
		}
	}
}

int BSTree::height(Node *node) const {
	if (node == NULL) {
		return 0;
	}

	int left = height(node->left);
	int right = height(node->right);

	if (left > right) {
		return left + 1;
	}
	else {
		return right + 1;
	}
}


Node* BSTree::remove(Node* node, const string  &word) {
	/**
	 * Handle spacing
	 * */
	if (word == "\n") {
		return root;
	}

    /**
     * NULL -> Nothing/empty tree
     * */
	if (root == NULL) {
		return root;
	}

	
	/**
	 * Left side
	 * */
	if (word < node->data) { 
		node->left = remove(node->left, word);
	}
	else if (word > node->data) {  
		node->right = remove(node->right, word);
	}
	else {
		if (node->count > 1) {
			node->countDecrement();
		}
		else if (node->left == NULL && node->right == NULL) {
			if (root == node) {
				return root = NULL;
			}
			delete node;
			return 0;
		}
		else if (node->left == NULL) {
			Node *temp = findMin(node->right);
			node->data = temp->data;
			node->count = temp->count;
			temp->count = 0;

			node->right = remove(node->right, temp->data);
			return node;
		}
		else if (node->right == NULL) {
			Node *temp = findMax(node->left);
			node->data = temp->data;
			node->count = temp->count;
			temp->count = 0;

			node->left = remove(node->left, temp->data);
			return node;
		}
		else {
			Node *temp2 = findMax(node->left);
			node->data = temp2->data;
			node->count = temp2->count;
			temp2->count = 1;
			node->left = remove(node->left, temp2->data);
		}
	}
	return node;
}

Node* BSTree::minNode(Node *node) {
	while (node->left != NULL) { node = node->left; }
	return node;
}

void BSTree::preOrder(Node *node) const {
	if (node == NULL)
		return;

	cout << node->data << "(" << node->count << "), ";
	preOrder(node->left);
	preOrder(node->right);
}

void BSTree::inOrder(Node *node) const {
	if (node == NULL)
		return;

	inOrder(node->left);
	cout << node->data << "(" << node->count << "), ";
	inOrder(node->right);
}

void BSTree::postOrder(Node *node) const {
	if (node == NULL)
		return;

	postOrder(node->left);
	postOrder(node->right);
	cout << node->data << "(" << node->count << "), ";
}

