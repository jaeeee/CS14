#include <iostream>
// #include <iostream>
#include <sstream>
#include "AVLTree.h"

using namespace std;

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Print" << endl
    << "3. Quit" << endl;
  cin >> choice;

  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main( ) {

  AVLTree tree;
  
     int numElements; 

  cout << "Testing insertion (enter # elements)" << endl;
  cin >> numElements;
    clock_t t;
	t = clock();
	tree.insert("hi");
  for (int i = 0; i < numElements; i++) {
      std::ostringstream os ;
      os << i ;
  // string text = "hi";
  // text += os.str();
    tree.insert(os.str());
    // cout << text << endl;
  }

      // if (tree.search("hi")) {
      //   cout << "Found" << endl;
      // } else {
      //   cout << "Not Found" << endl;
      // }
  t = clock() - t;
	cout << "time: " << t * 1000000 << " nanoseconds" << endl;
  

  // int choice = menu();

  // string entry;

  // while (choice != 3) {

  //   if (choice == 1) {
  //     cout << "Enter string to insert: ";
  //     getline(cin, entry);
  //     cout << endl;

  //     tree.insert(entry);

  //   } else if (choice == 2) {
  //     tree.printBalanceFactors();
  //     tree.visualizeTree("wth.dot");
  //   } 
  //   //fix buffer just in case non-numeric choice entered
  //   choice = menu();
  // }

  return 0;
}