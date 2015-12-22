#include <iostream>

using namespace std;

void binary(char *array, int current, int length);

int main() {
  cout << "Enter how many bits you want to print: ";
  int numberOfBits;
  cin >> numberOfBits;

  char *binaryNumber = new char[numberOfBits + 1];
  *(binaryNumber + numberOfBits) = '\0';

  binary(binaryNumber, 0, numberOfBits);

  delete [] binaryNumber;

  return 0;
}

void binary(char *array, int current, int length) {
  if(current == length) {
    cout << array << endl;
  } else {
    *(array + current) = '0';
    binary(array, current + 1, length);
    *(array + current) = '1';
    binary(array, current + 1, length);
  }
}


