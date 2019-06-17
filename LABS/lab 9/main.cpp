//
//  main.cpp
//  Lab 9
//
//  Created by Daniel Kwong on 3/5/19.
//  Copyright © 2019 Daniel Kwong. All rights reserved.
//
#include <iostream>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 10;
//const int NUMBERS_SIZE = 1000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

// You can use the following function to generate three similar array of random integers.

int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//partitions inputs into low and high parts
int partition_midpoint(int numbers[], int i, int k) {
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;
    
    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];
    
    l = i;
    h = k;
    
    while (!done) {
        
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }
        
        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }
        
        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    return h;
}

// The pivot is the median of the following three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k])
int partition_median(int numbers[], int i, int k) {
    int l = 0;
    int h = 0;
    
    int midpoint = 0;
    int pivot = 0;
    int median = 0;
    
    int temp = 0;
    bool done = false;
    
    /* Pick median element as pivot */
    midpoint = i + (k - i) / 2;
    
    // if the midpoint is the median. So the middle of the 3 values.
    if ((numbers[midpoint] >= numbers[i] && numbers[midpoint] <= numbers[k]) || (numbers[midpoint] >= numbers[k] && numbers[midpoint] <= numbers[i])) {
        
        median = midpoint;
        
    }
    // if the leftmost is the median. SO the middle of the 3 values.
    else if ((numbers[i] <= numbers[midpoint] && numbers[i] >= numbers[k]) || (numbers[i] >= numbers[midpoint] && numbers[i] <= numbers[k])) {
        
        median = i;
        
    }
    // if the rightmost is the median. So the middle of the 3 values.
    else if ((numbers[k] <= numbers[i] && numbers[k] >= numbers[midpoint]) || (numbers[k] >= numbers[i] && numbers[k] <= numbers[midpoint])) {
        
        median = k;
        
    }
    
    // pivot is the median value
    pivot = numbers[median];
    
    l = i;
    h = k;
    
    while (!done) {
        
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }
        
        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }
        
        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    return h;
}

//this function sorts the given array in the range from i to k
//using quicksort method. In this function, pivot is the midpoint
//element (numbers[(i+k)/2]). (implementation of this function is
//given in section 21.5).
void Quicksort_midpoint(int numbers[], int i, int k) {
    int pivotIndex = 0;
    
    //Base case
    // If 1 or zero elements are in the boundary, then you have reached the last partition of certain side. Start working back up the recursive calls.
    // and since its only 1 or zero elements it's already sorted don't need to continue recursion.
    if (i >= k) {
        return;
    }
    
    // get the midpoint of the partition.
    pivotIndex = partition_midpoint(numbers, i, k);
    
    // first recursively sort left side/ lesser values  with partitioning
    Quicksort_midpoint(numbers, i, pivotIndex);
    // afterwards recursively sort right side/ higher values with partitioning
    Quicksort_midpoint(numbers, pivotIndex + 1, k);
    
    return;
}

//this function utilizes different pivot selection technique in
//quicksort algorithm. The pivot is the median of the following
//three values: leftmost (numbers[i]), midpoint (numbers[(i+k)/2])
//and rightmost (numbers[k]). You should modify the partition
//function given in section 21.5 to select the pivot using
//median-of-three technique.
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    int pivotIndex = 0;
    
    //Base case
    // If 1 or zero elements are in the boundary, then you have reached the last partition of certain side. Start working back up the recursive calls.
    // also since its only 1 or zero elements it's already sorted don't need to continue recursion.
    if (i >= k) {
        return;
    }
    
    // get the median of the partition
    pivotIndex = partition_median(numbers, i, k);
    
    // recursively sort the left hand side
    Quicksort_medianOfThree(numbers, i, pivotIndex);
    // afterwards sort the right hand side
    Quicksort_medianOfThree(numbers, pivotIndex + 1, k);
    
    return;
}

//this function sorts the given array using InsertionSort method.
//(implementation of this method is provided in section 21.3).
void InsertionSort(int numbers[], int numbersSize) {
    int i = 0;
    int j = 0;
    int temp = 0;  // Temporary variable for swap
    
    for (i = 1; i < numbersSize; ++i) {
        j = i;
        // Insert numbers[i] into sorted part
        // stopping once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            // Swap numbers[j] and numbers[j - 1]
            temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            --j;
        }
    }
    
    return;
}

void printArray(int arr[]) {
    for (int i = 0; i < NUMBERS_SIZE;i++) {
        cout << arr[i] << " ";
    }
                    cout << endl;
}

int main() {
    
    // clock_t Start = clock();
    // //call sort function here
    // clock_t End = clock();
    // int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    
    // create three arrays of size 50000
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    
    // for calculating the elapsed time between sorted and unsorted runtime
    int elapsedTime = 0;
    clock_t Start = 0;
    clock_t End = 0;
    
    // fills the three arrays with randomly generated numbers
    fillArrays(arr1, arr2, arr3);
    
    // Comparing the sorting algorithms for unsorted arrays.
    cout  << "================================" << endl;
    cout << "Starting Quicksort Midpoint on unsorted array" << endl;
    Start = clock();
                    printArray(arr1);
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1); // sort whole array. 0 to length-1
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    printArray(arr1);
    cout << "Elapsed time: " << elapsedTime << endl;
    
    cout  << "================================" << endl;
    
    cout << "Starting Quicksort Median on unsorted array" << endl;
    Start = clock();
     printArray(arr2);
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1); // sort whole array. 0 to length-1
    End = clock();
     printArray(arr2);
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    
    cout  << "================================" << endl;
    
    cout << "Starting Insertion Sort on unsorted array" << endl;
    Start = clock();
     printArray(arr3);
    InsertionSort(arr3, NUMBERS_SIZE); // sort whole array.
    End = clock();
     printArray(arr3);
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    
    cout  << "================================" << endl;
    
    // Comparing the elapsed time between the sorts for already sorted arrays.
    
    cout << "Starting Quicksort Midpoint on sorted array" << endl;
    Start = clock();
     printArray(arr1);
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1); // sort whole array. 0 to length-1
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
     printArray(arr1);
    cout << "Elapsed time: " << elapsedTime << endl;
    
    cout  << "================================" << endl;
    
    cout << "Starting Quicksort Median on sorted array" << endl;
    Start = clock();
     printArray(arr2);
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1); // sort whole array. 0 to length-1
    End = clock();
     printArray(arr2);
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    
    cout  << "================================" << endl;
    
    cout << "Starting Insertion Sort on sorted array" << endl;
    Start = clock();
     printArray(arr3);
    InsertionSort(arr3, NUMBERS_SIZE); // sort whole array.
    End = clock();
     printArray(arr3);
    elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed time: " << elapsedTime << endl;
    
    cout  << "================================" << endl;
    
    
    return 0;
}
