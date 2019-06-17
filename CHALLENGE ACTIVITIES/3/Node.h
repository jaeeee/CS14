
#pragma once

#ifndef NODE_H
#define NODE_H
#include<iostream>
#include<string>
using namespace std;

class Node
{
public:
	Node(string newData);

	void countIncrement();
	void countDecrement();

	string data;
	int count;

	Node *left;
	Node *right;
};

#endif
