/**
 * Got help from Anthony Pham
 * */


#include <fstream>
#include <iterator>

#include "WordLadder.h"

using namespace std;

WordLadder::WordLadder(const string & fileName) {
    ifstream inFS;
    string word;
    inFS.open(fileName);
    if (!inFS.is_open()) {
      cout <<"Error: cannot open file" << endl;
      return;
    }
    
    /**
     * basically check if size is 5 bc dictionary only has words
     * with 5 characters
     * */
    while(!(inFS.eof())) {
      inFS >> word;
      if (word.size() != 5) {
        cout << "Error" << endl;
        return;
      }
      dict.push_back(word);
    }
    inFS.close();
    return;
}

    
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  /**
   * Variables
   * */
  ofstream outFS;
  stack<string> temp;
  queue<stack<string>> queue_stack;
  stack<string> main_stack;
  list<string>::iterator i; 
  unsigned count = 0;
  outFS.open(outputFile);
  if(!outFS.is_open()) {
    cout <<"Error: cannot open file" << endl;
    return;
  }
  //start from beginning
  //check if start exists
  for (i = dict.begin(); i != dict.end(); i++) {
      if (start == *i) {
        count++;
        break;
      }
  }
  if (count == 0) {
      cout <<"Error: start does not exist" << endl;
      return;
  }
  /**
   * Go through the dictionary again, and look for "end"
   * */
  count = 0;
  for (i = dict.begin(); i != dict.end(); i++) {
      if (end == *i) {
        count++;
        break;
      }
  }
  if (count == 0) {
      cout <<"Error: end does not exist" << endl;
      return;
  }
  /**
   * Condition: if start and end are the same
   * */
  if (start == end) {
    outFS << start << endl;  
    outFS.close();
    return;
  }
  string topWord;
  temp.push(start);
  queue_stack.push(temp);
  //not empty
  while (!queue_stack.empty()) {
    main_stack  = queue_stack.front();
    topWord = main_stack.top();
    //iterate from beginning to end of the dictionary
    for (i = dict.begin(); i != dict.end();) {
      unsigned counter = 0;
      string currWord = *i;
      for (unsigned j = 0; j < topWord.size(); ++j ) {
          if (topWord.at(j) != currWord.at(j)) {
            counter++;
          }
      }
      if (counter <= 1) {
        //push the strings onto stack
        stack<string> newmain_stack = main_stack;
        newmain_stack.push(*i);
        if (*i == end) {
          list<string> outList;
          //transfer the the "newmain" stack onto the outlist
          while(!newmain_stack.empty()) {
            outList.push_front(newmain_stack.top());
            newmain_stack.pop();
          }
          // outputting into the file
          for (i = outList.begin(); i != outList.end(); ++i) {
            outFS << *i << " ";
          }
          outFS << endl;
          outFS.close();
          return;
        }
        else {
          queue_stack.push(newmain_stack);
          i = dict.erase(i);
        }
      }
      else {
        i++;
      }
    }
    queue_stack.pop();
  }
  outFS.close();
  return;
}

