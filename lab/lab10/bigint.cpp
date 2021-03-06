#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "bigint.h"

// This is the constructor for the BigInt class. It takes a string s and 
// converts it to a series of integers, which are then placed into a vector
// of integers. 
BigInt::BigInt(string s) {
  // The stringstream ss is used to convert one character at a time.
  stringstream ss;
  // The char temp variable is used to hold one character from the string. 
  char temp;
  // This for loop iterates over the size of the string that is given to the 
  // constructor. Notice that we have to cast s.size() to an integer, since the
  // return type from the size() member function is an unsigned integer. An 
  // unsigned integer will not allow for 0, and therefore we could not access
  // the first element of the vector vInt.
  for(int i = (int) s.size() - 1; i >= 0; i--) {
    ss << s[i]; // Outputs the last character of s to the ss stringstream.
    ss >> temp; // Gets that character back into the temp variable.
    int tempInt = (int) temp - 48;  // Uses a simple conversion to get the
                                    // actual decimal number
    vInt.push_back(tempInt);  // Adds the converted integer to the vector.
    // Notice in the line above that the first integer placed into the vector
    // is actually the one's digit. The number is placed into the vector
    // BACKWARDS, which will make the add() function easier to write. 
  }
}

// This function prints a BigInt to a user. Notice that to show the correct
// output to the user we have to walk from the back of the vector to the front,
// since we put the digits in backwards. We also have to typecast out counter
// variable to make sure that we can access the 0th element. 
void BigInt::println() {
  for(int i = (int) vInt.size() - 1; i >= 0; i--) {
    cout << vInt[i];
  }
  cout << endl; // Each number will be displayed on a newline. 
}

// This function adds BigInt b to the BigInt that calls this function.
void BigInt::add(BigInt c) {
  // This iteration variable is used throughout the function, based on the size
  // of the integers that are being added, and the order in which they are 
  // being added.
  int iteration;
  // This if-else construction is used to determine which number is "bigger" in
  // the number of digits it has. From there, the appropriate iteration number
  // is set, and the numbers are padded with 0's as necessary to make the 
  //numbers line up after addition.
  if(c.vInt.size() > vInt.size()) {
    iteration = (int) c.vInt.size() + 1;
    c.vInt.push_back(0);
    int temp = (int) vInt.size();
    for(int i = 0; i < iteration - temp; i++) {
      vInt.push_back(0);
    }
  } else {
    iteration = (int) vInt.size() + 1;
    vInt.push_back(0);
    int temp = (int) c.vInt.size();
    for(int i = 0; i < iteration - temp; i++) {
      c.vInt.push_back(0);
    }
  }
  
  // The carry is set to 0 initially, since there is no carry for the first
  // column of addition.
  int carry = 0;
  
  // This for loop iterates over the appropriate powers of 10 and adds the 
  // columns together, taking the carry forward as necessary. 
  for(int i = 0; i < iteration; i++) {
    vInt[i] = vInt[i] + c.vInt[i] + carry;
    if(carry == 1) {
      carry = 0;
    }
    if(vInt[i] > 9) {
      vInt[i] = vInt[i] % 10;
      carry = 1;
    }
  }
  
  // This final if statement checks to see if the leading digit is 0, which
  // happens when there is no carry for the final digit, and it deletes that
  // leading 0. 
  if(vInt[iteration - 1] == 0) {
    vInt.pop_back();
  }
}

BigInt::BigInt(string s, int b) {
  stringstream ss;
  char temp;
  for(int i = (int) s.size() - 1; i >= 0; i--) {
    ss << s[i]; 
    ss >> temp; 
    int tempInt = (int) temp - 48;
    if(tempInt > 9) {
      tempInt -= 6;
    }  
    vInt.push_back(tempInt);   
  }
  base = b; 
}

void BigInt::addBase(BigInt d) {
  if(base != d.base) {
    cerr << "The bases do not match" << endl;
    return;
  } else {
    // This iteration variable is used throughout the function, based on the size
    // of the integers that are being added, and the order in which they are 
    // being added.
    int iteration;
    // This if-else construction is used to determine which number is "bigger" in
    // the number of digits it has. From there, the appropriate iteration number
    // is set, and the numbers are padded with 0's as necessary to make the 
    //numbers line up after addition.
    if(d.vInt.size() > vInt.size()) {
      iteration = (int) d.vInt.size() + 1;
      d.vInt.push_back(0);
      int temp = (int) vInt.size();
      for(int i = 0; i < iteration - temp; i++) {
        vInt.push_back(0);
      }
    } else {
      iteration = (int) vInt.size() + 1;
      vInt.push_back(0);
      int temp = (int) d.vInt.size();
      for(int i = 0; i < iteration - temp; i++) {
        d.vInt.push_back(0);
      }
    }
    
    // The carry is set to 0 initially, since there is no carry for the first
    // column of addition.
    int carry = 0;
    
    // This for loop iterates over the appropriate powers of 10 and adds the 
    // columns together, taking the carry forward as necessary. 
    for(int i = 0; i < iteration; i++) {
      vInt[i] = vInt[i] + d.vInt[i] + carry;
      if(carry == 1) {
        carry = 0;
      }
      if(vInt[i] > base - 1) {
        vInt[i] = vInt[i] % (base);
        carry = 1;
      }
    }
    
    // This final if statement checks to see if the leading digit is 0, which
    // happens when there is no carry for the final digit, and it deletes that
    // leading 0. 
    if(vInt[iteration - 1] == 0) {
      vInt.pop_back();
    }
  }
}

void BigInt::printlnBase() {
  for(int i = (int) vInt.size() - 1; i >= 0; i--) {
    if(vInt[i] < 10) {
      cout << vInt[i];
    } else {
      cout << (char) (vInt[i] + 54);
    }
  }
  cout << endl; // Each number will be displayed on a newline.
}
