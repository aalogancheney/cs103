#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include <vector>
#include <string>

using namespace std;

// A class designed to create a network of users (defined in the user.h file).
// The network will keep track of the users as well as the largest id of the 
// users in the network.
//
// The actions that can be performed on the network include adding a new user,
// reading information from a file, printing inforamtion to a file, adding
// a friend connection, removing a friend connection, printing the friends of
// a particular user, as well as other functions used to make this process
// easier. 
class Network {
  public:
    Network();
    ~Network();
    int read_friends(char *fileNameIn);
    int write_friends(char *fileNameOut);
    void add_user(string name, int birthyear, int zipcode);
    int add_connection(int idOne, int idTwo);
    int remove_connection(int idOne, int idTwo);
    int get_id(string name);
    vector<User *> get_users();
    void print_user(int id);
  private:
    vector<User *> _users;  // Each user is dynamically allocated
    int largestID;  // This keeps track of the largest id in the network
                    // and is used for assigning new ids. 
};

#endif
