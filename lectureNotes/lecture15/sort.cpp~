#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "timer.h"
using namespace std;

// Prototype for bubble sort function
void bubble_sort(int* data, int len);

// used with stdlib's built-in qsort() quicksort implementation 
int comp_int(const void* a, const void* b);

int main(int argc, char *argv[])
{
  if(argc < 3){
    cout << "Please enter 2 command line arguments: size_of_list target_val search_type" << endl;
    cout << "\tsize_of_list = length of the list of numbers ot generate" << endl;
    cout << "\tsearch_type = 0 (bubble) or 1 (quicksort)" << endl;
    return 1;
  }

  // Read the number of integers specified as the 1st command
  // line argument
  int numInts = atoi(argv[1]);
  
  // Dynamically allocate an array of ints of size: numInts
  //  using the 'new' operator
  int* data = new int[ numInts  ];

  // Generate an array of random numbers
  srand(time(0));
  for( int i=0; i < numInts; i++){
    data[i] = rand(); // this mimics a large, arbitrary 
                      // list of numbers in reverse order
  }

  // Start a timer
  Timer t;
  t.start();

  // Used to store where in the array our target value is located
  int idx;

  // Perform the appropriate type of search
  if(atoi(argv[2]) == 0){
    bubble_sort(data, numInts);
  }
  else {
    qsort(data, numInts, sizeof(int), comp_int);
  }
  // Stop the timer
  t.stop();

  // Get and print the time it took to perform the search
  double ms = t.elapsed_ms();
  cout << "The sort of " << numInts << " numbers took " << ms << " ms." << endl;

  // Print the first 25  results as a sanity check
  for(int i=0; i < 25; i++){
    cout << setw(12) << data[i];
    if(i % 10 == 4 || i%10 == 9) cout << endl;
  }
  // Use delete to deallocate the array you new'ed
  delete [] data;

  return 0;
}

// Sort an array in ascending order
void bubble_sort(int* data, int len)
{
  for(int i = len - 1; i >= 0; i--) {
    for(int j = 0; j < i; j++) {
      if(data[j] > data[j + 1]) {
        int temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }

}

int comp_int(const void* a, const void* b)
{
  return *(int*)a - *(int*)b;
}
