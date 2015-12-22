#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;

// A class designed to hold information about a user in a social network. It
// keeps track of an id, name, birthyear, zipcode, and friend list. 
//
// The actions that can be performed on the user only includes adding a friend,
// deleting a friend, and getting the information about the user with the 
// appropriate return types. On its own, this class is simple, but the 
// Network class defined in the network.h file provides a much larger 
// functionality with users. 
class User {
  public:
    User(int id, string name, int birthyear, int zipcode);
    void add_friend(int id);
    void delete_friend(int id);
    int get_id();
    string get_name();
    int get_birthYear();
    int get_zipCode();
    vector<int> *get_friends();
  private:
    int _id;
    string _name;
    int _birthYear;
    int _zipCode;
    vector<int> _friends;
};

#endif
