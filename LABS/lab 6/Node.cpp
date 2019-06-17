#include "Node.h"

Node::Node(string data) {
    this->data = data;
    count = 0;
    left = 0;
    right = 0;
    height = 0;
    parent = 0;
}
Node::Node() {
    data = "";
    count = 0;
    left = 0;
    right = 0;
    parent = 0;
    height = 0;
}

// string Node::getData() {
//     return data;
// }
// void Node::setData(string data) {
//     this->data = data;
// }
// Node* Node::getLeft() {
//     return left;
// }
// Node* Node::getRight() {
//     return right;   
// }
// void Node::setLeft(Node* addNode) {
//     left = addNode;
// }
// void Node::setRight(Node* addNode) {
//     right = addNode;
// }
// void Node::setHeight(int h) {
//     height = h;
// }
// int Node::getHeight() {
//     return height;
// }