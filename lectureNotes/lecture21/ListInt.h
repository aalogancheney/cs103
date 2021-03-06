// Checks to see if the header-file has already been included from another
// file, and if it has already been defined it will not be included. Check
// the bottom of the file, and there is a #endif statement that means everything
// inbetween the top and bottom will not be included. 
//
// Notice that we have called these things by the name of the class, in all
// capital letters, with an underscore and a capital H. This is common, 
// although we can name it whatever we want. 
#ifndef LISTINT_H
#define LISTINT_H

struct IntItem {
  int val;
  IntItem *next;
};

class ListInt {
 public:
  // Initialize an empty list
  ListInt();

  // Destructor (free all memory for each item) 
 ~ListInt();

  // Returns true if the list is empty
  bool is_empty();

  // Returns the number of items in the list
  int size();

  // Prints each integer item in the list 
  // (separated by a space)
  void print_list();

  // Add a new integer, new_val, to the back of the list
  void push_back(int new_val);

  // Add a new integer, new_val, to the front of the list
  // pushing every other item back one
  void push_front(int new_val);

  // Remove the front item it there is one, returning its value
  // and deleting it from the list
  int pop_front();

  // Return the item value at the front of the list
  int front();

  /*******************************************
   * Uncomment the following 2 prototypes
   *  if you want to implement them
   *******************************************/
  /// Finds the IntItem struct in the list that
  ///  has the value specified by find_val or NULL
  ///  if it doesn't exist in the list
  //IntItem *find(int find_val);

  /// Finds and removes the IntItem struct in the
  /// list with the specified value.  Returns true
  /// if successful and false if the value is not
  /// in the list
  //bool remove(int del_val);


  /*******************************************
   * This function is for more advanced courses
   *  that cover operator overloading
   *******************************************/
  //ListInt& operator+(const ListInt &rhs);

 private:

  IntItem *head;
};

#endif
