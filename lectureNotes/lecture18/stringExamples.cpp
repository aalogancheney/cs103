#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  // int length;

  // Initializes two strings, string1 and string2, using two different
  // methods.
  string string1("CS 103");
  string string2 = "fun";

  // We can change the contents in the variable string2 using the 
  // assignment operator
  string2 = "really fun";

  // The cout object knows how to handle string objects.
  cout << string1 << " is " << string2 << endl;
  // We can use the + operator to concatenate strings together.
  string2 = string2 + "!!!";
  cout << string2 << endl;

  // We can initialize a string to another string.
  string string3(string1);
  
  // We can compare strings.
  if(string1 == string3) {
    cout << string1 << " is the same as " << string3;
    cout << endl;
  }

  // We can use bracket notation to access elements of a string.
  cout << "First letter is " << string1[0];
  cout << endl;

  return 0;
}
