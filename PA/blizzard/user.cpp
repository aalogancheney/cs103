#include <string>
#include <vector>
#include "user.h"
using namespace std;

// The constructor is used to initialize a user with a given id, name, 
// birthyear, and zipcode. For PA5, the two new data members _depth and
// _predecessor are automatically set to -1 so there is never any confusion.
User::User(int id, string name, int birthyear, int zipcode) {
  _id = id;
  _name = name;
  _birthYear = birthyear;
  _zipCode = zipcode;
  _depth = -1;
  _predecessor = -1;
  _set = -1;
  _score = -1;
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

// Below are the functions added for PA5. There are two accessor and mutator
// functions, each to handle the two new data members _depth and _predecessor.
// These values are going to be changing after each User is declared, since
// the depth and predecessor values can change based on who we use to run
// our search algorithms. 
int User::get_depth() {
  return _depth;
}

int User::get_predecessor() {
  return _predecessor;
}

int User::get_set() {
  return _set;
} 

int User::get_score() {
  return _score;
}

void User::set_depth(int depth) {
  _depth = depth;
}

void User::set_predecessor(int predecessor) {
  _predecessor = predecessor;
}

void User::set_set(int set) {
  _set = set;
}

void User::set_score(int score) {
  _score = score;
}
