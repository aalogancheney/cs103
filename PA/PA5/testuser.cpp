#include <iostream>
#include "user.h"
using namespace std;

int main(int argc, char *argv[]) {
  User Aaron(0, "Aaron Cheney", 1990, 91007);
  int id = Aaron.get_id();
  string name = Aaron.get_name();
  int birthYear = Aaron.get_birthYear();
  int zipCode = Aaron.get_zipCode();
  vector<int> *friends = Aaron.get_friends();
  
  //cout << "friends: " << (*friends)[0];
  
  Aaron.add_friend(10);
  Aaron.add_friend(1);
  
  cout << id << " " << name << " " << birthYear << " " << zipCode << endl;
  cout << "friends: " << (*friends)[0] << endl;
  
  Aaron.delete_friend(1);
  cout << "friends: " << (*friends)[0] << endl;

  return 0;
}
