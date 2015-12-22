#include <iostream>
#include <cstring>

using namespace std;

void f1(int *ptr);

int main(int argc, char *argv[]) {
  
  int x = 0;    // Declares an integer x and initializes it to 0.
  int *p;       // 1. Declares a pointer to an integer p and does not initialize it.
  p = &x;       // 2. Makes p point at the location of x.
  f1(p);        // 3. Calls the function f1() by passing p directly, since the function
                // f1() takes type int * as its argument. 
  p = new int;  // 5. Makes p point to a dynamically allocated integer. Recall that the
                // return type from new gives a pointer to the type declared, in this
                // case an int *. 

  // cout << "new p = " << p << " " << *p << endl;
  
  double *q = new double[10];   // 6. Declares a pointer to a double q and initializes it
                                // to a dynamically allocated array of doubles. Again,
                                // recall that the return from new gives a pointer to
                                // the type used, regardless of array or not, so in this
                                // case we get a double *. 
  *(q + 4) = 0;                 // 7. Makes the 5th element in the array pointed to by 
                                // q equal to 0.
  
  // cout << "*(q + 4) = " << *(q + 4) << endl;
  
  int **r = new int *[5]; // 8. Declares a pointer, r, that points to a dynamically 
                          // allocated array of 5 integers.
  *r = new int[8];        // 9. Makes the 0th pointer in r point to a dynamically allocated
                          // array of 8 integers. Again, recall that the new command will
                          // return a type int * here, and if we look at *r we can see 
                          // that it is indeed an int *. The types match.
  *(r + 1) = p;           // 10. Makes the 1st pointer in r point to the same integer that
                          // p is pointing toward. 

  // cout << "*(r + 1) " << *(r + 1) << endl; 

  char *s[6];               // 11. Declares an array, s, of 6 pointers to char.
  s[5] = new char[11];      // 12. Makes the last element of s point toward a dynamically
                            // allocated array of char of size 11.
  char t[] = "CS103 Yea!";  // 13. Statically declares an array, t, with the string.
  strcpy(*(s + 5), t);      // 14. Uses the function strcpy() to copy the string in t to the
                            // last array pointed to by s. Recall that the strcpy() function
                            // uses two pointers as formal arguments, and in this case the
                            // variable name t is the address of the array, and 
                            // dereferencing the value (s + 5) gives us a character array
                            // and thus the name of an array, i.e. the address.
  
  // cout << "*(s + 5) = " << *(s + 5) << endl;

  delete [] *(s + 5);       // 15. Deletes specifically the information in the last array
                            // pointed to by s. 

  // cout << "*(s + 5) = " << *(s + 5) << endl;
  
  // Contains all of the delete statements for the other dynamically allocated memory. 
  delete p;
  delete [] q;
  delete [] r;
  return 0;
}

void f1(int *ptr) {
  cout << "Made it!" << endl;
  cout << "ptr = " << ptr << ", *ptr = " << *ptr << endl;
  *ptr = 7;   // 4. Changes the value pointed to by ptr to 7.
  cout << "ptr = " << ptr << ", *ptr = " << *ptr << endl;

  return;
}
