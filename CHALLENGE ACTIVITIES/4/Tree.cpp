#include "Node.h"
#include "Tree.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Tree::Tree() {
    root = NULL;
}

Tree::~Tree() {
    deleteNode(root);
}

void Tree::insert(const string &ree) {
    if (root == NULL) {
        Node *current = new Node(ree);
        root = current;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->middle = NULL;
        return;
    } else {
        Node *current = root;
        while (current->left != NULL && current->right != NULL && current->middle != NULL) {
            if (ree < current->small) {
                current = current->left;
            } else if (ree > current->large) {
                current = current->right;
            } else if (ree > current->small && ree < current->large) {
                current = current->middle;                
            }
        }
        
        while (current->right != 0 && current->left != 0 && current->middle == 0) {
            if (ree < current->small) {
                current = current->left;
            } else if (ree > current->large) {
                current = current->right;
            } else if (ree > current->small && ree < current->large) {
                Node *newNode = new Node(ree);
                newNode->parent = current;
                current = current->middle;
                current = newNode;
            }
        }
        
        if (current->large == "") {
            if (ree > current->large) {
                current->large = ree;
            } else if (ree < current->small) {
                current->large = current->small;
                current->small = ree; 
            }
        } else {
        split(current, ree);
        }
    }
    return;
}

void Tree::split(Node *current, const string &word) {
    if (current->parent == 0) {
        if (word > current->small && word < current->large) { //no good!!! need to split
            Node *smolNode = new Node(current->small);
            Node *largeNode = new Node(current->large);
            current->left = smolNode;
            current->right = largeNode;
            //move the parent up
            current->left->parent = current;
            current->right->parent = current;
            current->small = word;
            current->large = "";
        } else if (word < current->small) {
            Node *xinNode = new Node(word);
            Node *youBianNode = new Node(current->large);
            current->left = xinNode;
            xinNode->parent = current;
            current->right = youBianNode;
            current->right->parent = current;
            current->large = "";
        } else if (word > current->large) {
            Node *zouBianNode = new Node(current->small);
            Node *xinNode = new Node(word);
            current->left = zouBianNode;
            zouBianNode->parent = current;
            current->right = xinNode;
            current->right->parent = current;
            current->large ="";
        }
    } else { //if parent exists then.....
        if (word < current->small) { 
            Node *newNode = new Node(word);
            current->parent->middle = newNode;
            newNode->parent = current->parent;
            current->parent->large = current->small;
            root = current->parent;
            current->small = current->large;
            current->large = "";
        } else if (word > current->large) {
            Node *zhongJianNode = new Node(current->small);
            current->parent->middle = zhongJianNode;
            zhongJianNode->parent = current->parent;
            current->parent->large = current->large;
            current->small = "";
            current->small = word;
            current->large = "";
        } else if (word > current->small && word < current->large) {
            Node *newNode = new Node(current->small);
            current->parent->middle = newNode;
            newNode->parent = current->parent;
            current->parent->large = word;
            current->small = current->large;
            current->large = "";
        }
    }
}

void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void Tree::preOrder(Node *current) const {
    if (current) {
        if (current -> small != "") {
            cout << current -> small << ", ";
        }
        preOrder(current -> left);
        if (isThree(current)) {
            if (current -> large != "") {
                cout << current -> large << ", ";
            }
            preOrder(current -> middle);
        }
        preOrder(current -> right);
    }
}

void Tree::inOrder(Node *current) const {
    if (current) {
        inOrder(current -> left);
        if (current -> small != "") {
            cout << current -> small << ", ";
        }
        if (isThree(current)) {
            inOrder(current-> middle);
            if (current -> large != "") {
                cout << current -> large << ", ";
            }
        }
        inOrder(current -> right);
    }
}
void Tree::postOrder(Node *current) const {
    if (current) {
        postOrder(current -> left);
        if (isThree(current)) {
            postOrder(current -> middle);
            if (current -> small != "") {
                cout << current -> small << ", ";
            }
        }
        postOrder(current -> right);
        if (isTwo(current)) {
            if (current -> small != "") {
                cout << current -> small << ", ";
            }
        }
        if (isThree(current)) {
            if (current -> large != "") {
                cout << current -> large <<", ";
            }
        }
    }
}


void Tree::remove(const string &movie) {
    Node *current = search(root, movie);
    Node *leaf = 0;
    if (current) {
        if (!ifLeaf(current)) {
            Node *nxt = getNext(current, movie);
            if (current -> small == movie) {
                swap(current -> small, nxt -> small);
            }
            else {
                swap(current -> large, nxt -> large);
            }
            leaf = nxt;
        }
        
        else {
            leaf = current;
        }
        
        if (movie == leaf -> large) {
            leaf -> large = "";
        }
        
        else {
            leaf -> small = leaf -> large;
            leaf -> large = "";
        }
        if (leaf -> small.empty()) {
            deleteNode(leaf);
        }
    }
}

bool Tree::search (const string &movie) const { 
    Node *key = search(root, movie);
    if (key -> small == movie || key -> large == movie) {
        return true;
    }
    
    return false;
}
bool Tree::isTwo(Node *current) const { 
    if (current -> large.empty()) {
        return true;
    }
    
    return false;
}

bool Tree::isThree(Node *current) const {
    if (!current -> small.empty() && !current -> large.empty()) {
        return true;
    }
    
    return false;
}

Node* Tree::search(Node *current, const string &movie) const {
    if (current) {
        if (ifLeaf(current)) {
            return current;
        }
        
        else if (isTwo(current)) {
            if (movie == current -> small || movie == current -> large) {
                return current;
            }
            else if (movie < current -> small) {
                return search(current -> left, movie);
            }
            else {
                return search(current -> right, movie);
            }
        }
        
        else {
            if (movie == current -> small || movie == current -> large) {
                return current;
            }
            else if (movie < current -> small) {
                return search(current -> left, movie);
            }
            else if (movie > current -> large) {
                return search(current -> right, movie);
            }
            else {
                return search(current -> middle, movie);
            }
        }
    }
    return 0;
}

bool Tree::ifLeaf(Node *x) const {
    //will return true if left middle and right are all null
    if (x -> left == NULL && x -> middle == NULL && x -> right == NULL) {
        return true;
    }
    
    return false;
}

void Tree::deleteNode(Node *x) {
     if (x == root) {
        if (ifLeaf(x)) {
            delete x;
            root = 0;
            return;
        }
        
        else {
            if (root -> right == 0) {
                root = root -> left;
            }
            else {
                root = root -> right;
            }
        }
        return;
    }
    
    else {
        Node* parentNode = x -> parent;
        Node* siblingNode = getSibling(x);
       
        if (isThree(siblingNode)) {
            if (parentNode -> left == x){
                if (isTwo(parentNode)){
                    x->small = parentNode->small;
                    parentNode->small = siblingNode->small;
                    siblingNode->small = siblingNode->large;
                    siblingNode->large = "";
                }
                else {
                    if (isTwo(parentNode->right)) {
                        x -> small = parentNode -> small;
                        parentNode -> small = siblingNode -> small;
                        siblingNode -> small = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                    else {
                        x -> small = parentNode -> small;
                        parentNode -> small = siblingNode -> small;
                        siblingNode -> small = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                }
            }
            
            else if (parentNode -> middle == x) { 
                if (parentNode -> left == siblingNode){
                    x -> small = parentNode -> small;
                    parentNode -> small = siblingNode -> large;
                    siblingNode -> large = "";
                }
                else{
                    x -> small = parentNode -> large;
                    parentNode -> large = siblingNode -> small;
                    siblingNode -> small = siblingNode -> large;
                    siblingNode -> large = "";
                }
            }
            else { 
                if (isTwo(parentNode)) {
                    x -> small = parentNode->small;
                    parentNode -> small = siblingNode -> large;
                    siblingNode -> large = "";
                }
                else {
                    if (isTwo(parentNode->left)) {
                        x->small = parentNode->large;
                        parentNode -> large = siblingNode -> small;
                        siblingNode -> small = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                    else { 
                        x -> small = parentNode -> large;
                        parentNode -> large = siblingNode -> large;
                        siblingNode -> large = "";
                    }
                }
            }

            if ((x -> left != 0 && x -> right == 0) || (x -> right != 0 && x -> left == 0)) { //internal node
                if (parentNode -> right == x) {
                    if (x -> left == 0){
                        x -> left = siblingNode -> right;
                        siblingNode -> right = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                    else{
                        x -> right = x -> left;
                        x -> left = siblingNode -> right;
                        siblingNode -> right = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                }
                else {
                    if (x -> right == 0) {
                        x -> right = siblingNode -> left;
                        siblingNode -> left = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                    else{
                        x -> left = x -> right;
                        x -> right = siblingNode -> left;
                        siblingNode -> left = siblingNode -> middle;
                        siblingNode -> middle = 0;
                    }
                }
            }
        }
        else {
            if (isTwo(parentNode)) {
                if (parentNode -> left == x) {
                    siblingNode -> large = siblingNode->small;
                    siblingNode -> small = parentNode->small;
                    parentNode -> small = "";
                } 
                else {
                    parentNode -> large = parentNode -> small;
                    parentNode -> small = siblingNode -> small;
                    siblingNode -> small = "";
                }
            }
            else {
                if (parentNode->left == x) {
                    if (isTwo(parentNode -> right)) {
                        siblingNode -> large = siblingNode -> small;
                        siblingNode -> small = parentNode -> small;
                        parentNode -> small = parentNode -> large;
                        parentNode -> large = "";
                        parentNode -> left = siblingNode;
                        parentNode -> middle = 0;
                    }
                    else {
                        x -> small = parentNode -> small;
                        parentNode -> small = siblingNode -> small;
                        siblingNode -> small = parentNode -> large;
                        parentNode -> large = parentNode -> right -> small;
                        parentNode -> right -> small = parentNode -> right -> large;
                        parentNode -> right -> large = "";
                    }
                }
                else if (parentNode -> middle == x) {
                    siblingNode -> large = parentNode -> small;
                    parentNode -> small = parentNode -> large;
                    parentNode -> large = "";
                    parentNode -> middle = 0;
                }
                else { 
                    if (isTwo(parentNode -> left)) {
                        siblingNode -> large = parentNode -> large;
                        parentNode -> large = "";
                        parentNode -> right = siblingNode;
                        parentNode -> middle = 0;
                    }
                    else {
                        x -> small = parentNode -> large;
                        parentNode -> large = siblingNode -> small;
                        siblingNode -> small = parentNode -> small;
                        parentNode -> small = parentNode -> left -> large;
                        parentNode -> left -> large = "";
                    }
                }
            }

            if ((x -> left != 0 && x -> right == 0) || (x -> right !=0 && x -> left == 0)) {
                if (parentNode -> right == x) {
                    siblingNode -> middle = siblingNode -> right;
                    if (x -> left == 0) {
                        siblingNode -> right = x -> right;
                    }
                    else {
                        siblingNode -> right = x -> left;
                    }
                }
                else {
                    siblingNode -> middle = siblingNode -> left;
                    if (x -> right == 0) {
                        siblingNode -> left = x -> left;
                    }
                    else {
                        siblingNode -> left = x -> right;
                    }
                }
            }

            delete x;
            x = 0;
            
            if (parentNode -> small.empty() && parentNode -> large.empty()) {
                deleteNode(parentNode);
            }
        }
    }
}

Node* Tree::getNext(Node *current, const string &movie) const {
    if (ifLeaf(current)) {
        return current;
    }
    
    else if (isTwo(current)) {
        if (movie < current -> small) {
            return getNext(current -> left, movie);
        }
        else {
            return getNext(current -> right, movie);
        }
    }
    
    else {
        if (movie < current -> small) {
            return getNext(current -> left, movie);
        }
        else if (movie < current -> large) {
            return getNext(current -> middle, movie);
        }
        else {
            return getNext(current -> right, movie);
        }
    }
}

Node* Tree::getSibling(Node *current) {
    Node *parentNode = current -> parent;
    if(isTwo(parentNode)) {
        if (parentNode -> left == current) {
            return parentNode -> right;
        }
        else if(parentNode -> right == current) {
            return parentNode -> left;
        }
    }
    else {
        if (parentNode -> right == current || parentNode -> left == current) {
            return parentNode -> middle;
        }
        else {
            if (isThree(parentNode -> left) && isThree(parentNode -> right)) {
                return parentNode -> right;
            }
            else if (isTwo(parentNode -> left) && isTwo(parentNode -> right)) {
                return parentNode -> left;
            }
            else if (isThree(parentNode -> left)) {
                return parentNode -> left;
            }
            else {
                return parentNode -> right;
            }
        }
    }
    return NULL;
}

