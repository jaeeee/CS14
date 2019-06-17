/**
 * Looked online for josephus code algorithm, found it on a forum called dreamincode,
 * because I spent an hour trying to figure out how to iterate a list properly and delete nodes without
 * resulting in dangling pointers
 * Modified the code so it could work for starting at certain index & kills people off
 * Originally, the code I found on the forum would ask for the "nth" value which kills every nth value
 * I re-wrote it so that it would kill off people to the left (like in class)
 * in the same way as wanted (person to left) as demonstrated in class
 * I also implemented a way for the user to assert which position (in the circle) does the killing start,
 * as demonstrated in class.
 * */


#include <iostream>
using namespace std;

struct node {
	int value;
	node *previous;
	node *next;
};

int main(){
	int numPeople;
	cout << "Circle size: " << endl;
	cin >> numPeople;

  //this is the initialization of the first node
	node *curNode = new node();
	//obviously, the first node's value is 1
	curNode->value = 1;
	
	//temporary pointer, pointers to the first node (head)
	node *beg = curNode;

	for (int i = 2; i <= numPeople; i++) {
	  //makes the next node into a new initalized node
		curNode->next = new node();
		//makes this new node point back to the node just created
		curNode->next->previous = curNode;
		//iterate to next node, let's start creating new nodes
		curNode = curNode->next;
		curNode->value = i;
	}
	curNode->next = beg; //links the last node back to the "head"
	curNode->next->previous = curNode; //links the head's previous node to the end of list
	curNode = curNode->next; //go back to the front of list
	int counter = 1; //keep track of skips
	cout << "Starting position: " << endl;
	int starting;
	cin >> starting;
	for (int i = 1; i < starting; i++) { //iterate to the starting position
	  curNode = curNode->next;
	 // cout << i << endl;
	}
	cout << "Starting at index: " << curNode->value << endl; 
	while (curNode->next != curNode) { //keep going until end of the circularly linked list (only one value left because it points to itself)
		if (counter == 2) { //kill every 2nd person, skip 1
			cout << "Killed " << curNode->value << endl;
			//set the node before's next value to the next node of the current
			curNode->previous->next = curNode->next;
			//set the next node's previous node to the node before the current
			curNode->next->previous = curNode->previous;
			node *next = curNode->previous->next;
			//delete current node
			delete(curNode);
			//set the pointer to the next node after the current (which was just deleted)
			curNode = next;
			//reset counter back to 1
			counter = 1;
		}
		else {
		  //if counter != 2, then skip this node, and count one more
			curNode = curNode->next;
			counter++;
		}
	}
	cout << "Survivor: " << curNode->value << endl;
	return 0;
}
