#include <iostream>
#include <fstream>

using namespace std;

// The sort() function takes an array of integers and the length
// of the array and performs a selection sort on the array of
// that length. 
void sortRecursive(int *, int);

void sortLoop(int *, int);

// The binsearch() function takes a target value, an array of
// integers, the start of the array and the end of the array as
// its arguments, and it uses binary search to look through the
// array for the target value.
int binsearch(int, int *, int, int);

int main(int argc, char *argv[]) {
  
  int target;
  // Checks that the user entered the right number of command line
  // arguments. 
  if(argc < 2) {
    cout << "Provide a filename of the data to be searched." << endl;
    return 1;
  }

  // Creates an ifstream variable called datfile, and associates
  // the second command line argument as the file name to the
  // variable datfile. The ios::in argument is an optional argument
  // that signifies the file is going to be used for input. 
  ifstream datfile(argv[1], ios::in);
  // If the file was not opened the program will exit. 
  if(datfile.fail()){
    cout << "Unable to open file: " << argv[1] << endl;
    return 1;
  }
  
  // Here we count how many elements are in the file. 
  int count = 0;
  // This while loop will continue while input has not failed. 
  while(!datfile.fail()) {
    int temp;
    datfile >> temp;
    // If the input did not fail, we will incrememnt the count.
    if(!datfile.fail()) {
      count++;
    }
  }
  
  // When we reach the end of the file, the EOF flag is set.
  // To be able to read through the file again we need to clear
  // that flag so we can read more information.
  datfile.clear();
  // Since the datfile variable is associated with the same file,
  // we need to reset the position of the file pointer to the beginning
  // of the file.
  datfile.seekg(0, ios::beg);

  // Here we dynamically allocate an array to hold the information
  // located in the file, and read through that inforamtion. 
  int *data = new int[count];
  for(int i = 0; i < count; i++) {
    datfile >> data[i];
  }

  // Closes the file since we don't need it anymore.
  datfile.close();

  cout << "Read " << count << " integers from the data file.\n" << endl;
  cout << "Enter the target positive integer to search for: ";
  cin >> target;

  // This will sort the information in the data array.
  // Uncomment the line below to use the sorting algorithm.
  sortRecursive(data, count);
  // sortLoop(data, count);

  // Uncomment these lines of code to see the sorted array printed
  // to the screen, as proof that it works.
  
  for(int i = 0; i < count; i++) {
    cout << *(data + i) << " ";
  }
  cout << endl;
  

  // Call binary search on the array data. 
  int retval = binsearch(target, data, 0, count);

  // Interpret and print the results.
  if(retval == -1) {
    cout << target << " does not appear in the data." << endl;
  } else {
    cout << target << " appears at index " << retval << " in the data." << endl;
  }

  // Deallocate the data array
  delete [] data;

  return 0;
}

// This function will return -1 if the data is not in the list, which will 
// occur when the starting point is equal to the ending point, and otherwise
// it will return the index where the information is located. 
int binsearch(int target, int *data, int start, int end)
{
  // Set the middle point of start and end as the first point to be 
  // searched. 
  int middle = (start + end) / 2;
  // If the function starts and start == end, then we eject and give back the
  // number -1 to indicate the number was not found in the list. 
  if(start == end) {
    return -1;
  // If the data at the midpoint is less than the target, then we know the 
  // target has to be past the middle point. We add 1 because the starting
  // point is inclusive. 
  } else if(*(data + middle) < target) {
    start = middle + 1;
    // Here we use a return statement to make sure that there is a return 
    // statement at the end of every possible part of the if-else branch, 
    // and here we are returning an int, since that's what binsearch() 
    // will return. We re-call the function but with the new values of 
    // start or end. 
    return binsearch(target, data, start, end);
  // If the data at the midpoint is greater than the target, then we know the 
  // target has to be before the middle point. We do not need to add one since
  // the end of the list is exclusive. 
  } else if(*(data + middle) > target) {
    end = middle;
    return binsearch(target, data, start, end); 
  // When all other possibilities have been considered, the value must have
  // been found.  
  } else {
    return middle;
  }
}

// This function will sort the information in the array data using a 
// selection sort. 
void sortRecursive(int *data, int len)
{
  // Here we check if we are sorting an array of length 1, in which case
  // we do not need to do any work.
  if(len == 1) {
    return;
  }

  // Set the first value of the array equal to the largest number seen
  // so far. Set the index equal to the first spot in the array. 
  int largestValue = *(data);
  int index = 0;
  // Walks through the array and checks to see if there is a larger 
  // element in the array, and if so set that equal to the largest
  // element seen, and remember that index. At the end of the for
  // loop we will have the largest element of the array. 
  for(int i = 1; i < len; i++) {
    if(*(data + i) > largestValue) {
      largestValue = *(data + i);
      index = i;
    }
  }

  // Since we remembered the index where the largest number is, we 
  // set the value at that index equal to the last element of the
  // array.
  *(data + index) = *(data + len - 1);
  // And finally we put the largest value into the last element of
  // the array. 
  *(data + len - 1) = largestValue;
  
  sortRecursive(data, len - 1); 
}

void sortLoop(int *data, int len) {
  int i = len;
  while(i > 1) {
    int largestValue = *(data);
    int index = 0;
    for(int j = 0; j < i; j++) {
      if(*(data + j) > largestValue) {
        largestValue = *(data + j);
        index = j;
      }
    }
    *(data + index) = *(data + i - 1);
    *(data + i - 1) = largestValue;
    i--;
  }
}
