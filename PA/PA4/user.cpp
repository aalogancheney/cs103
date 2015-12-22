#include <string>
#include <vector>
#include "user.h"
using namespace std;

// The constructor is used to initialize a user with a given id, name, 
// birthyear, and zipcode. 
User::User(int id, string name, int birthyear, int zipcode) {
  _id = id;
  _name = name;
  _birthYear = birthyear;
  _zipCode = zipcode;
}

// Used the push_back() function to add a friend to the _friends vector. 
void User::add_friend(int id) {
  _friends.push_back(id);
}

// Removes a connection between friends, provided there is a connection. 
void User::delete_friend(int id) {
  for(unsigned int i = 0; i < _friends.size(); i++) {
    if(_friends[i] == id) {
      _friends.erase(_friends.begin() + i);
    }
  }
}

// These last functions are accessor functions used to get the inforamtion
// from a user. 
int User::get_id() {
  return _id;
}

string User::get_name() {
  return _name;
}

int User::get_birthYear() {
  return _birthYear;
}

int User::get_zipCode() {
  return _zipCode;
}

vector<int> *User::get_friends() {
  return &_friends;
}
