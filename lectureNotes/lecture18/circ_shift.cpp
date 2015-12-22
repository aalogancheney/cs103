#include <iostream>
#include <string>

using namespace std;

bool is_circular_shift(string stringOne, string stringTwo);

int main(int argc, char *argv[]) {
  cout << "Give two strings to test if they are circular shifts of each other: " << endl;
  string stringOne, stringTwo;

  cin >> stringOne >> stringTwo;

  if(is_circular_shift(stringOne, stringTwo)) {
    cout << stringOne << " and " << stringTwo << " are circular shifts of each other." << endl;
  } else {
    cout << stringOne << " is not a circular shift of " << stringTwo << endl;
  }

  return 0;
}

bool is_circular_shift(string stringOne, string stringTwo) {
  return stringOne.size() == stringTwo.size() && (stringOne + stringOne).find(stringTwo)
    != string::npos;
  /*if(stringOne.size() != stringTwo.size()) {
    cout << "The two strings do not have the same length." << endl;
    return false;
  } else {
    stringOne = stringOne + stringOne;
    if(stringOne.find(stringTwo) != string::npos) {
      return true;
    } else {
      return false;
    }
  }*/
}
