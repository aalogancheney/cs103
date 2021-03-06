#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include "network.h"
#include "user.h"
using namespace std;

// The constructor only sets the largest ID to 0, since there are no users when
// the network is first instantiated. 
Network::Network() {
  largestID = 0;
}

// The destructor runs through all of the users and deletes the pointer to 
// those users, deallocating the memory. 
Network::~Network() {
  for(unsigned int i = 0; i < _users.size(); i++) {
    delete _users[i];
  }
}

// This function adds a user to the network. It does not require an id since
// new users are added based on largestID. Each user is dynamically allocated
// and the push_back() function adds them to the vector in the network. 
void Network::add_user(string name, int birthyear, int zipcode) {
  User *newUser = new User(largestID, name, birthyear, zipcode);
  _users.push_back(newUser);
  largestID++;
}

// Simply returns the users in the network. 
vector<User *> Network::get_users() {
  return _users;
}

// Adds a connection between two users based on their id's. The return value
// is used to determine if the action was successful or not. Ultimately, the 
// add_friend() member function is called. 
int Network::add_connection(int idOne, int idTwo) {
  // This if-else branch checks that the user id's are valid based on the 
  // names of the people given at the prompt. This can happen if the names
  // provided at the prompt are not part of the network. This protects against
  // typos and clever people. 
  if(idOne == -1 && idTwo == -1) {
    cout << "Neither user exists." << endl;
    return -1;
  } else if(idOne == -1) {
    cout << "The first user entered doesn't exist." << endl;
    return -1;
  } else if(idTwo == -1) {
    cout << "The second user entered doesn't exist." << endl;
    return -1;
  }

  string nameOne; // Names for the people associated with the id's.
  string nameTwo;
  int idOneLocation = -1; // Their location is initially "unfound".
  int idTwoLocation = -1;
  bool notFriends = true; // Used to check if they are already friends. 
  
  // Initializes the location of the two users in the network and gets their
  // names. 
  for(unsigned int i = 0; i < _users.size(); i++) {
    if(_users[i]->get_id() == idOne) {
      idOneLocation = i;
      nameOne = _users[idOneLocation]->get_name();
    }
    if(_users[i]->get_id() == idTwo) {
      idTwoLocation = i;
      nameTwo = _users[idTwoLocation]->get_name();
    }
  }
  
  // Checks if the two users are friends already.
  for(unsigned int i = 0; i < _users[idOneLocation]->get_friends()->size(); 
      i++) {
    if(_users[idOneLocation]->get_friends()[0][i] == idTwo) {
      notFriends = false;
    }
  }
  
  // So long as the two users are not friends, and they exist, then the function
  // will add each user to the others list of friends. Otherwise, the function
  // will output that the users are already friends. Ultimately, the
  // add_friend() member function is called. 
  if(notFriends) {
    _users[idOneLocation]->add_friend(idTwo);
    _users[idTwoLocation]->add_friend(idOne);
    return 0;
  } else {
    cout << nameOne << " is already friends with " << nameTwo << "." << endl;
    return -1;
  }
}

// This function performs the reverse actions in the function above, but for 
// removing the connection between two users. The functionality and methodology
// inside is virtually the same as above. Ultimately, the delete_friend() 
// member function is called. 
int Network::remove_connection(int idOne, int idTwo) {
  if(idOne == -1 && idTwo == -1) {
    cout << "Neither user exists." << endl;
    return -1;
  } else if(idOne == -1) {
    cout << "The first user entered doesn't exist." << endl;
    return -1;
  } else if(idTwo == -1) {
    cout << "The second user entered doesn't exist." << endl;
    return -1;
  }
    
  string nameOne;
  string nameTwo;
  int idOneLocation = -1;
  int idTwoLocation = -1;
  bool areFriends = false;
  
  for(unsigned int i = 0; i < _users.size(); i++) {
    if(_users[i]->get_id() == idOne) {
      idOneLocation = i;
      nameOne = _users[idOneLocation]->get_name();
    }
    if(_users[i]->get_id() == idTwo) {
      idTwoLocation = i;
      nameTwo = _users[idTwoLocation]->get_name();
    }
  }
  
  for(unsigned int i = 0; i < _users[idOneLocation]->get_friends()->size(); 
      i++) {
    if(_users[idOneLocation]->get_friends()[0][i] == idTwo) {
      areFriends = true;
    }
  }
  
  if(areFriends) {
    _users[idOneLocation]->delete_friend(idTwo);
    _users[idTwoLocation]->delete_friend(idOne);
    return 0;
  } else {
    cout << nameOne << " is not friends with " << nameTwo << "." << endl;
    return -1;
  }
}

// Returns the id of a user based on their name. 
int Network::get_id(string name) {
  // Assums the user is not in the network, and then uses the for loop below
  // to check if they are, and set the id variable accordingly. 
  int id = -1;  
  for(unsigned int i = 0; i < _users.size(); i++) {
    if(_users[i]->get_name() == name) {
      id = _users[i]->get_id();
    }
  }
  return id;
}

// This is a function I defined outside of the parameters of the assignment, 
// which is useful when printing users to the screen, as with the 4th and 
// 5th prompts available. The output is formatted well so that every time
// something is printed to the screen it is uniform.
void Network::print_user(int id) {
  for(unsigned int i = 0; i < _users.size(); i++) {
    if(_users[i]->get_id() == id) {
      cout << _users[i]->get_id() << setw(5) << " "
           << _users[i]->get_name() << setw(28 - _users[i]->get_name().size())
           << _users[i]->get_birthYear() << setw(6) << " "
           << _users[i]->get_zipCode() << setw(7) << " ";
    }
  }
}

// This function reads information from a file and puts it into the network. A
// long and tedious function, but the stringstream variable requires the extra
// effort. 
int Network::read_friends(char *fileName) {
  ifstream inFile(fileName);  // Associated inFile with the provided file.
  // First, we check that the file was opened properly; if not, the function
  // exits in an error state; if it does, the appropriate actions are performed.
  if(inFile.fail()) {
    return -1;
  } else {
    string users;               // Uses the first piece of information from
    getline(inFile, users);     // the file to set-up how many users are going
    stringstream ssOne(users);  // to be read from the file. For consistency
    int numberOfUsers;          // purposes, stringstream is used here. 
    ssOne >> numberOfUsers;
    
    // This for loop runs over the number of users in the file. 
    for(int i = 0; i < numberOfUsers; i++) {
      // These 5 variables correspond to the 5 lines of information in the file
      // per user. 
      string idString;
      string nameString;
      string birthYearString;
      string zipCodeString;
      string friendsString;
      
      // These getline() function calls are used to get the information from
      // the file.
      getline(inFile, idString);
      getline(inFile, nameString);
      getline(inFile, birthYearString);
      getline(inFile, zipCodeString);
      getline(inFile, friendsString);
      
      // These stringstream variables are used to parse each string 
      stringstream idStream(idString);
      stringstream nameStream(nameString);
      stringstream birthYearStream(birthYearString);
      stringstream zipCodeStream(zipCodeString);
      stringstream friendsStream(friendsString);
      
      // These are the variables that will be used to create a new user. 
      int id;
      string firstName;
      string lastName;
      int birthYear;
      int zipCode;
      
      // These lines of code show the extraction of the information from the 
      // stringstreams into the variables. 
      idStream >> id;
      nameStream >> firstName >> lastName;
      birthYearStream >> birthYear;
      zipCodeStream >> zipCode;
      string name = firstName + " " + lastName;
      
      // Creates a new user. 
      add_user(name, birthYear, zipCode);
      
      // Continually reads information from the friendsStream, since this
      // stringstream does not have a definite size (a user can have any number
      // of friends, including the possibility that they don't have friends).
      int temp;
      while(friendsStream >> temp) {
        _users[i]->add_friend(temp);
      }
    }
  }
  
  inFile.close();
  
  return 0;
}

// This function writes the information in the network to a file, provided
// as an argument. 
int Network::write_friends(char *fileName) {
  // Associates the fileName with the outFile ofstream object.
  ofstream outFile(fileName);
  // Checks that the file was successfully opened. 
  if(outFile.fail()) {
    return -1;
  } else {
    // A mixture of newline and tab characters are used here to achieve the 
    // right format in the output file. The format is the same as the format
    // for files that are read, which means that any file outputed can then 
    // be read in to create a new network. 
    outFile << _users.size() << '\n';
    for(unsigned int i = 0; i < _users.size(); i++) {
      outFile << _users[i]->get_id() << '\n';
      outFile << '\t' << _users[i]->get_name() << '\n';
      outFile << '\t' << _users[i]->get_birthYear() << '\n';
      outFile << '\t' << _users[i]->get_zipCode() << '\n';
      outFile << '\t';
      for(unsigned int j = 0; j < _users[i]->get_friends()->size(); j++) {
        outFile << _users[i]->get_friends()[0][j] << " ";
      }
      outFile << '\n';
    }
  }
  
  outFile.close();
  
  return 0;
}
