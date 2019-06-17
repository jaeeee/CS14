#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    T min;
    min = vals.at(index);
    for (unsigned i = index; i < vals.size(); i++) {
        if(vals.at(i) < min) {
            min = vals.at(i);
            index = i; 
        }
    }
    return index;
}

template<typename T>
void selection_sort(vector<T> &vals) {
for (unsigned i = 0; i < vals.size(); i++) {
    unsigned minIndex = min_index(vals, i);
    T temp = vals[i]; //temporary store the current index
    vals[i] = vals[minIndex];
    vals[minIndex] = temp;
}    
}

template<typename T>
T getElement(vector<T> vals, int index) {
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){

    cout << "Vector before sort: " << endl;
    vector<int> tester;
    tester.push_back(100);
    tester.push_back(99);
    tester.push_back(10);
    tester.push_back(75);
    tester.push_back(34);
    for (int i = 0; i < tester.size(); i++) {
        cout << tester[i] << " ";
    }
    cout << endl;
    cout << "Vector after sort: " << endl;
    selection_sort(tester);
    for (int i = 0; i < tester.size(); i++) {
        cout << tester[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    //Part B
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    unsigned ind = 0;
    cout << "Array size: " << vals.size() << endl;
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;
        
        curChar = getElement(vals,index);
        cout << "Element located at " << index << ": is " << curChar << endl;
        
        try {
            if (ind > vals.size()) {
                throw std::out_of_range("Too high");
            }
            if (ind < 0) {
                throw std::out_of_range("Too low");
            }
            return vals.at(ind);
        }
        catch (const std::out_of_range& excpt) {
            cout << "out of range exception occured" << endl;
        }
        
    }
    return 0;
}
