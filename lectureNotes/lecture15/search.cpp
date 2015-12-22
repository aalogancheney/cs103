#include <iostream>
#include <cstdlib>
#include "timer.h"
using namespace std;

// prototype for linear search algorithm
int lsearch(int* data, int len, int target);

// prototype for binary search algorithm
int bsearch(int* data, int len, int target);

int main(int argc, char *argv[])
{
  if(argc < 4){
    cout << "Please enter 3 command line arguments: size_of_list target_val search_type" 
         << endl;
    cout << "\tsize_of_list = length of the list of numbers ot generate" << endl;
    cout << "\ttarget_val = integer value to search for in the list" << endl;
    cout << "\tsearch_type = 0 (linear) or 1 (binary)" << endl;
    return 1;
  }

  // Read the number of integers specified as the 1st command
  // line argument
  int numInts = atoi(argv[1]);
  
  // Dynamically allocate an array of ints of size: numInts
  // using the 'new' operator
  int *data = new int[numInts];

  // Generate an array of the first numInts even numbers
  for(int i=0; i < numInts; i++) {
    data[i] = 2*i; // this mimics a large, arbitrary list of numbers
  }

  // Convert the 2nd command line argument to an integer named target
  int target = atoi(argv[2]);

  // Start a timer
  Timer t;
  t.start();

  // Used to store where in the array our target value is located
  int idx;

  // Perform the appropriate type of search
  if(atoi(argv[3]) == 0){
    idx = lsearch(data, numInts, target);
  }
  else {
    idx = bsearch(data, numInts, target);
  }
  // Stop the timer
  t.stop();

  // Get and print the time it took to perform the search
  double us = t.elapsed_us();
  cout << "The search of " << numInts << " numbers took " << us << " us." << endl;

  // Interpret and print results
  if(idx != -1){
    cout << target << " appears at index=" << idx << endl;
  }
  else {
    cout << target << " does not appear in the list" << endl;
  }

  // Use delete to deallocate the array you new'ed
  delete [] data;

  return 0;
}

// Linear search function
int lsearch(int* data, int len, int target)
{
  for(int i=0; i < len; i++){
    if(target == data[i]){
      return i;
    }
  }
  return -1;
}

// Binary search function
int bsearch(int *data, int len, int target)
{
  int start = 0, end = len;
  while(start != end) {
    int mid = (start + end) / 2;
    if(data[mid] == target) {
      return mid;
    } else if(data[mid] > target) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return -1;
}
