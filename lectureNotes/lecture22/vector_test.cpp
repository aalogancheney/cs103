#include <iostream>
#include <vector>

using namespace std;

void print_list(vector<int> &myvec)
{
  unsigned int i;
  // complete the for loop and its body
  for(i = 0; i < myvec.size(); i++) {
    cout << myvec[i] << " ";
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  // int temp;
  vector<int> l1;

  cout << "Added 1, 2, 3, and 9 to list 1" << endl;
  // add code to put 1, 2, 3, and 9 into the vector in that order
  l1.push_back(1); l1.push_back(2); l1.push_back(3); l1.push_back(9);

  print_list( l1 );

  // print out the number of items (list size) in the list
  cout << "The number of items in the list is " << l1.size() << endl;

  // print out the front item
  cout << "The front item of list l1 is " << l1.front() << endl;

  // delete the item at index 1 in the lines of code after the cout
  cout << "Removing second item (i.e. at index 1): " << endl;
  l1.erase(l1.begin() + 1);
  
  // will print the resulting list
  print_list( l1 );

  // add code to put 120, 121, 122 onto the front of the list 
  //  use the insert() method after the cout line below
  cout << "Adding 120, 121, 122" << endl;

  // The following three lines add the values in ascending order. 
  l1.insert(l1.begin(), 120);
  l1.insert(l1.begin() + 1, 121);
  l1.insert(l1.begin() + 2, 122);

  print_list( l1 );
  return 0;
}
