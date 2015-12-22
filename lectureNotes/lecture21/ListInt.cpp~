#include <iostream>
#include "ListInt.h"

using namespace std;

  // Initialize an empty list
ListInt::ListInt()
{
  // This cout statement will show the user when this constructor function
  // gets called. 
  cout << "***Creating ListInt object" << endl;
  head = NULL;
}

// Destructor (free all memory for each item). Recall that this happens when
// the created object goes out of scope. 
ListInt::~ListInt()
{
  // Again, we use the cout statement to show when the destructor function
  // gets called. 
  cout << "***Deleteing ListInt object" << endl;
  IntItem *tmp;
  // Add your code here to delete all IntItem structures in the list

}

// Returns true if the list is empty
bool ListInt::is_empty()
{
  return (head == NULL);
}

// Returns the number of items in the list 
int ListInt::size()
{
  IntItem *temp = head;
  int counter = 0;
  while(temp != NULL) {
    counter++;
    temp = temp->next;
  }
  return counter;
}

// Prints each integer item in the list (separated by a space)
void ListInt::print_list()
{
  IntItem *temp = head;
  while(temp != NULL) {
    cout << temp->val << " ";
    temp = temp->next;
  }
  cout << endl;
}

// Add a new integer, new_val, to the back of the list
void ListInt::push_back(int new_val)
{
  IntItem *new_item = new IntItem;
  new_item->val = new_val;
  new_item->next = NULL;
  
  if(head == NULL) {
    head = new_item;
  } else {
    IntItem *temp = head;
    while(temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new_item;
  }
}

// Add a new integer, new_val, to the front of the list
// pushing every other item back one
void ListInt::push_front(int new_val)
{
  IntItem *new_item = new IntItem;
  new_item->val = new_val;
  new_item->next = head;
  head = new_item;
}

// Remove the front item it there is one, returning its value
// and deleting it from the list
int ListInt::pop_front()
{
  if(head != NULL) {
    IntItem *temp = head;
    head = head->next;
    int val = temp->val;
    delete temp;
    return val;
  } else {
    return -1;
  }
}

// Return the item value at the front of the list
int ListInt::front()
{
  if(head != NULL) {
    return head->val;
  } else {
    return -1;
  }
}


// IntItem *ListInt::find(int find_val)
// {

// }

// bool ListInt::remove(int del_val)
// {

// }

// ListInt &ListInt::operator+(const ListInt &rhs)
// {

// } 


