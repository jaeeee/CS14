#include <iostream>
#include <string>
#include "IntList.h"

using namespace std; 

void printMenu() {
    cout << "what are you trying to do bro" << endl;
    cout << "a - push front " << endl;
    cout << "b - pop front " << endl;
    cout << "c - push back " << endl;
    cout << "d - pop back " << endl;
    cout << "e - empty " << endl;
    cout << "f - print list " << endl;
    cout << "g - print reverse" << endl;
    cout << "q - quit " << endl;
    cout << "ENTER OPTION: ";
}

int main() {
  char option;
  bool continu = true;
  IntList swag;
  while(continu == true) {
      printMenu(); 
      cin >> option;
      switch(option) {
          case 'a': // push front
          cout << "value you like to push front: " << endl;
          int val;
          cin >> val;
          swag.push_front(val);
          break;
          case 'b': // pop front
          cout << "popped front " << endl;
          swag.pop_front();
          break;
          case 'c': // push back
          cout << "value you like to push back: " << endl;
          int topush;
          cin >> topush;
          swag.push_back(topush);
          break;
          case 'd': // pop back
          swag.pop_back();
          break;
          case 'e': // empty
          if (swag.empty() == true) {
              cout << "IntList empty " << endl;
          } else {
              cout << "IntList not empty" << endl;
          }
          break;
          case 'f': // print 
          cout << swag << endl;
          break;
          case 'g': // reverse print
          swag.printReverse();
          break;
          case 'q':
          continu = false;
          break;
      }
      cout << endl << endl;
  }
return 0;
}