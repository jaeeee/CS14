#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include "BSTree.h"
#include <cstdlib>

using namespace std;

void printOrders(BSTree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder( );
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder( );
  cout << endl;
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
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
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

  BSTree tree;

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
  

// 	t = clock();
  // time_t start,end;
// time (&start);
  // clock_t begin = clock();

// 	cout << CLOCKS_PER_SEC << " clocks per second" << endl;
// 	cout << "time: " << t*1.0/CLOCKS_PER_SEC << " seconds" << endl;

// 	system("pause");
  // time (&end);
// double dif = difftime (end,start);
// cout << "Elasped time is %.2lf seconds." << endl;
  // clock_t end = clock();
  // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  // cout << elapsed_secs << " taken" << endl;

  // int choice = menu();

  // string entry;
  
  // while (choice != 8) {
    
  //   if (choice == 1) {
  //     cout << "Enter string to insert: ";
  //     getline(cin, entry);
  //     cout << endl;
      
  //     tree.insert(entry);
      
  //   } else if (choice == 2) {
  //     cout << "Enter string to remove: ";
  //     getline(cin, entry);
  //     cout << endl;
      
  //     tree.remove(entry);
      
  //   } else if (choice == 3) {
  //     printOrders(&tree);
      
  //   } else if (choice == 4) {
  //     cout << "Enter string to search for: ";
  //     getline(cin, entry);
  //     cout << endl;
      
  //     if (tree.search(entry)) {
  //       cout << "Found" << endl;
  //     } else {
  //       cout << "Not Found" << endl;
  //     }

  //   } else if (choice == 5) {
  //     cout << "Smallest: " << tree.smallest() << endl;
      
  //   } else if (choice == 6) {
  //     cout << "Largest: " << tree.largest() << endl;
      
  //   } else if (choice == 7) {
  //     cout << "Enter string: ";
  //     getline(cin, entry);
  //     cout << endl;
  //     cout << "Height of subtree rooted at " << entry << ": " 
  //       << tree.height(entry) << endl;
        
  //   }
  //   //fix buffer just in case non-numeric choice entered
  //   choice = menu();
  // }
  
  return 0;
}
