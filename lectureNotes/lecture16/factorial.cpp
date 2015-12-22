#include <iostream>

using namespace std; 

int factorial(int n);

int main(int argc, char *argv[]) {
  int myNumber;
  cout << "Enter a number to compute the factorial: " << endl;
  cin >> myNumber;

  cout << myNumber << " factorial is " << factorial(myNumber) << "." << endl;

  return 0;  
}

int factorial(int n) {
  if(n == 1) {
    return 1;
  } else {
    int nLessOne = factorial(n - 1);
    return n * nLessOne;
  }
}
