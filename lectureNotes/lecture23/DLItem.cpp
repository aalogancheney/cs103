class DLItem {
  private:
    DLItem *head;
    DLItem *previous;
    DLItem *next;
    int val;
}

// These lines of code add a new item to the front of a doubly-linked list
DLItem *temp = item to be inserted

temp->previous = NULL;
temp->next = head;
head->previous = temp;
head = temp;


// These lines of code delete an item from the middle of a doubly-linked list
DLItem *temp = item to be deleted

temp->previous->next = temp->next;
temp->next->previous = temp->previous;
delete temp;


