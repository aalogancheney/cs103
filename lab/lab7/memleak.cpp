#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;


// sum an array of numbers
int test1(int *data, int len)
{
  int sum = 0;
  // This for loop initially had the conditional at i <= len, which caused
  // the for loop to try and read past the end of the array.
  for(int i=0; i < len; i++){
    sum += data[i];
  }
  return sum;
}

// Allocate a random number array
char* test2_init(int len)
{
  char buf[80];
  cout << "Enter a word: ";
  cin >> buf;
  char* mydat = new char[strlen(buf)+1];
  strcpy(mydat, buf);
  return mydat;
}

char* test2_reverse(char* word)
{
  int len = strlen(word);
  char* otherword = new char[len+1];
  
  for(int i=0; i < strlen(word); i++){
    otherword[i] = word[len-i-1];
  }
  // This line originally tried to write the null character past the end
  // of the array with otherword[len + 1] = '\0', which is unnecessary since
  // the last element of the array is located at the length of the word,
  // because of indexing starting at 0. 
  otherword[len] = '\0';
  delete [] word;
  return otherword;
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please enter the test number you want to run [1-2]" << endl;
    return 1;
  }
  const int len = 7;
  int test = atoi(argv[1]);

  if(test == 1){
    // Test should sum up the array values and print it
    int *data = new int[len];
    for(int i=0; i < len; i++){
      data[i] = rand()%100;
    }
    int sum = test1(data, len);
    cout << "Test 1 sum is " << sum << endl;
    // This delete statement was not originally in the file, it is
    // added here once the work has been done with the array of int.
    delete [] data;
  }

  else if(test == 2){
    // Test should create a random string & then reverse a copy
    char* myword = test2_init(len);
    cout << "myword is " << myword << endl;
 
    char* otherword = test2_reverse(myword);    
    cout << "otherword is " << otherword << endl;
   
    // There were originally two delete [] statements that tried to delete the
    // same bit of memory. Although the pointers myword and word are different,
    // they are pointing to the same bit of memory. We could have either gotten
    // rid of this delete statement or the one on line 43, but we cannot have
    // both.
    // delete [] myword;
    delete [] otherword;
  }
  else {
    cout << "Unknown test number" << endl;
  }

  return 0;
}
