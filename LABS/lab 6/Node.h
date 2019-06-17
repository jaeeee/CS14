#ifndef Node_H
#define Node_H

#include <iostream>

using namespace std;

class Node {
    public:
        string data;
        int count;
        Node* left;
        Node* right;
        Node* parent;
        int height;
        Node(string data);
        Node();
        // string getData();
        // void setData(string data);
        // Node* getLeft();
        // Node* getRight();
        // void setLeft(Node* addNode);
        // void setRight(Node* addNode)
        // void setHeight(int h);
        // int getHeight();
};

#endif