#ifndef DELIST_H
#define DELIST_H

// This structure holds information for a doubly-linked list. The structure
// contains two pointers, each of which points to either the next or previous
// item in the list, and it also holds the value.
struct DEItem {
  int val;
  DEItem* prev;
  DEItem* next;
};

// This class performs all the actions we need on a doubly-linked list. These
// are the same things we can do with a singly-linked list, but with the
// added pop_front() and push_front() functions. 
class DEList {
  public:
    DEList();
    ~DEList();
    bool empty();
    int size();
    int front();
    int back();
    void push_front(int new_val);
    void push_back(int new_val);
    void pop_front();
    void pop_back();

  private:
    DEItem *head;   
    DEItem *tail;
};

#endif
