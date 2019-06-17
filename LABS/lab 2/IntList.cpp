#include "IntList.h"

#include <iostream>
#include <string>

using namespace std;

IntList::IntList() {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    
    dummyHead->prev = NULL;
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    dummyTail->next = NULL;
}

IntList::~IntList() {
    IntNode *curr = dummyHead->next;
    while (curr != dummyTail) {
        curr = curr->next; 
        dummyHead->next = curr;
        delete curr->prev;
        curr->prev = dummyHead;
    }
}

void IntList::push_back(int value) {
    IntNode* curr = new IntNode(value);
    curr->next = dummyTail;
    curr->prev = dummyTail->prev;
    
    dummyTail->prev = curr;
    curr->prev->next = curr;
}

void IntList::push_front(int value) {
    IntNode *curr = new IntNode(value);
    curr->prev = dummyHead;
    curr->next = dummyHead->next;
    dummyHead->next = curr;
    curr->next->prev = curr;
}

void IntList::pop_front() {
    IntNode* curr = dummyHead;
    if (dummyHead->next == dummyTail) {
        return;
    } 
    curr = dummyHead->next->next;
    dummyHead->next = curr;
    delete curr->prev;
    curr->prev = dummyHead;
}

void IntList::pop_back() {
    if(dummyHead->next == dummyTail) {
        return;
    }
    
    dummyTail->prev = dummyTail->prev->prev;
    delete dummyTail->prev->next;
    dummyTail->prev->next = dummyTail;
}

bool IntList::empty() const {
    if (dummyHead->next == dummyTail) {
        return true;
    } else {
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs) {
    if (rhs.dummyHead == 0)
    return out;
    if (rhs.dummyHead->next == rhs.dummyTail) {
        return out;
    }
    IntNode* currObj = rhs.dummyHead;
    currObj = currObj->next;
    while (currObj->next != rhs.dummyTail) {
        out << currObj->data << " ";
        currObj = currObj->next;
    }
    out << currObj->data;
    return out;
}

void IntList::printReverse() const {
    IntNode* curr = dummyTail->prev;
    
    while (curr != dummyHead) {
        cout << curr->data << " ";
        curr = curr->prev;
    }
}