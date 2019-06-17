#include "Tree.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

void printOrders(Tree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << "Inorder = ";
  tree->inOrder( );
  cout << "Postorder = ";
  tree->postOrder( );
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Quit" << endl;
  cin >> choice;
  
  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int randNum(int min, int max)
{
   return rand() % max + min;
}

int main( ) {

  Tree tree;
  
   int numElements; 

  cout << "Testing insertion (enter # elements)" << endl;
  cin >> numElements;
    clock_t t;
	t = clock();
	tree.insert("hi");
  for (int i = 0; i < numElements; i++) {
      std::ostringstream os ;
      
      os << randNum(i, numElements) ;
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
  
  // while (choice != 5) {
  //   if (choice == 1) {
  //     cout << "Enter movie title to insert: ";
  //     getline(cin, entry);
  //     cout << endl;
      
  //     tree.insert(entry);
      
  //   } else if (choice == 2) {
  //     cout << "Enter movie title to remove: ";
  //     getline(cin, entry);
  //     cout << endl;
      
  //     tree.remove(entry);
      
  //   } else if (choice == 3) {
  //     printOrders(&tree);
      
  //   } else if (choice == 4) {
  //     cout << "Enter movie title to search for: ";
  //     getline(cin, entry);
  //     cout << endl;
      
  //     if (tree.search(entry)) {
  //       cout << "Found" << endl;
  //     } else {
  //       cout << "Not Found" << endl;
  //     }
  //   }

  //   //fix buffer just in case non-numeric choice entered
  //   choice = menu();
  // }
  
  return 0;
}
