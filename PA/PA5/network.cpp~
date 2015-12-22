#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <deque>
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
// 5th prompts available. The output is well-formatted so that every time
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

// Below this point, the functions that are added are for PA5

// This function will find the shortest path between two user ids given as the
// arguments for the function. The function returns a vector, which will 
// contain the path between the two users. If there is no path, the return
// vector will be empty. 
vector<int> Network::shortest_path(int from, int to) {
  // Creates the vector that will be returned from this function.
  vector<int> path;
  // Creates the breadth-first-search deque object. A deque is used so that
  // items can be pulled from the front of the deque on order O(1).
  deque<int> BFS;
  
  // This if-else construction checks that the useres are valid. 
  if(from == -1 && to == -1) {
    cout << "Neither user exists." << endl;
    return path;
  } else if(from == -1) {
    cout << "The first user entered doesn't exist." << endl;
    return path;
  } else if(to == -1) {
    cout << "The second user entered doesn't exist." << endl;
    return path;
  }
  
  // Sets the depth of the from target to 0, the from target is set as his own
  // predecessor, and the from target is added to BFS. This means that the
  // BFS is non-empty when starting. 
  _users[from]->set_depth(0);
  _users[from]->set_predecessor(from);
  BFS.push_back(from);
  
  // This while loop construction will run through each of the users placed
  // into the BFS object, and will continue while there are still users to
  // process.
  while(!BFS.empty()) {
    // This for loop will iterate over all of the friends of the user that is
    // placed in the front of the BFS object. 
    for(unsigned int i = 0; i < _users[BFS.front()]->get_friends()->size(); i++)
    {
      // This if statement is used to check if the friend of the user in the 
      // front of the BFS object has already been found by checking the depth.
      // If the user has not yet been found, his depth is set as one more than
      // the person doing the searching, his predecessor is set to the person
      // doing the searching, and they are added to the back of the BFS object.
      if(_users[_users[BFS.front()]->get_friends()[0][i]]->get_depth() == -1) {
        
        _users[_users[BFS.front()]->get_friends()[0][i]]->set_depth(
          _users[BFS.front()]->get_depth() + 1);
        
        _users[_users[BFS.front()]->get_friends()[0][i]]->set_predecessor(
          BFS.front());
        
        BFS.push_back(_users[BFS.front()]->get_friends()[0][i]);
      }
    }
    // Once the front user in the BFS object has been processed, he is removed
    // so that the next person can be processed.
    BFS.pop_front();
  }
  
  // This if-else branch checks that the two users are connected. If the depth
  // of the to target was not set, then the two users are not connected.
  // Otherwise, the path vector is set with the path back to the from target,
  // and the path vector is returned. 
  if(_users[to]->get_depth() == -1) {
    cout << _users[from]->get_name() << " and " << _users[to]->get_name()
         << " are not connected through friends." << endl;
    return path;
  } else {
    path.push_back(to);
    while(path.back() != from) {
      path.push_back(_users[path.back()]->get_predecessor());
    }
    vector<int> newPath(path.size());
    for(unsigned int i = 0; i < path.size(); i++) {
      newPath[i] = path[path.size() - i - 1];
    }
    return newPath;
  }
}

// This function returns a vector that contains vector<int> for each value, so
// each element in the vector is another vector. This will help to separate
// the sets. The function will create sets of users that are each disjoint
// from the other sets. 
vector< vector<int> > Network::groups() {
  // Initializes the number of sets to 0.
  int numSets = 0;
  
  // This for loop will go through each user in the network.
  for(unsigned int i = 0; i < _users.size(); i++) {
    // If the user in the network does not have a set, then this if statement
    // will execute. 
    if(_users[i]->get_set() == -1) {
      // The user is given a set, and a new deque is created to do a BFS over
      // the connections from the user. 
      _users[i]->set_set(numSets);
      deque<int> BFS;
      BFS.push_back(_users[i]->get_id());
      // This while loop construction is similar to the while loop in the
      // function above, but it will just give all connections the same set
      // as the user that started the search, and continue while there are
      // users to process.
      while(!BFS.empty()) {
        for(unsigned int j = 0; j < _users[BFS.front()]->get_friends()->size(); 
          j++) {
          if(_users[_users[BFS.front()]->get_friends()[0][j]]->get_set() == -1){
            _users[_users[BFS.front()]->get_friends()[0][j]]->set_set(numSets);
            BFS.push_back(_users[_users[BFS.front()]->get_friends()[0][j]]
              ->get_id());
          }
        }
        // As users are removed from the front, more users are added to the
        // BFS deque.
        BFS.pop_front();
      }
      // The number of sets is incremented now, since the user and all of 
      // their connections have been set. 
      numSets++;
    }
  }
  
  // Creates the vector sets with the number of elements equal to the number
  // of sets. Then the for loop assigns user ids to the appropriate
  // vector in sets. 
  vector< vector<int> > sets(numSets);
  for(unsigned int i = 0; i < _users.size(); i++) {
    sets[_users[i]->get_set()].push_back(_users[i]->get_id());
  }
  
  return sets;
}

// This last function returns a vector that contains friend suggestions based
// on the number of common friends between users that are at distance 2 from
// each other. 
vector<int> Network::suggest_friends(int who, int& score) {
  // Creates a vector called suggestions, which is initially empty, and the 
  // score is also set to -1 at the beginning. 
  vector<int> suggestions;
  score = -1;
  
  // If the entered user does not have any friends, then there is no reason
  // to keep searching and the program exits, otherwise it will search through
  // the users to find any possible suggestions.
  if(_users[who]->get_friends()->empty()) {
    cout << _users[who]->get_name() << " does not have any friends." << endl;
    return suggestions;
  } else {
    // This vector temp is unused, the only reason it exists is so that the
    // shortest_path() function can be called. Note that the shortest_path()
    // function will work, since there is at least one friend, and the
    // shortest_path() function will go through all users in the set of the 
    // user, thus computing the distance for anyone connected to the user. 
    vector<int> temp = 
      shortest_path(who, _users[_users[who]->get_friends()[0][0]]->get_id());
    
    // Loops through all users in the network.
    for(unsigned int i = 0; i < _users.size(); i++) {
      // Checks if the depth of the users is 2, which is the required distance
      // for a friend suggestion. 
      if(_users[i]->get_depth() == 2) {
        // This counter is used to score how well each potential suggestion
        // is connected to the other friends of the user. 
        int counter = 0;
        // This for loop will check how many friends are in common that have
        // a depth 1, meaning that they are connected to the source user, and
        // the counter is incremented for each potential common friend 
        // connection. 
        for(unsigned int j = 0; j < _users[i]->get_friends()->size(); j++) {
          if(_users[_users[i]->get_friends()[0][j]]->get_depth() == 1) {
            counter++;
          }
        }
        // The score of the user is set to the counter. 
        _users[i]->set_score(counter);
        
        // This if-else construct will make sure that the vector suggestions
        // will only contain the users who have the highest score. If the
        // score of the most recent processed user is greater than the score
        // in the score variable, then the score is set to the higher value,
        // the suggestions vector is emptied of all current occupants, and the
        // user that has the high score is added to the vector. The else 
        // branch is used if there is a user that has the same score, and they
        // are added to the suggestions vector as well. If the computed score
        // is less than the current value of score, then nothing is done since
        // there is another user that is more well connected. 
        if(counter > score) {
          score = counter;
          while(!suggestions.empty()) {
            suggestions.pop_back();
          }
          suggestions.push_back(_users[i]->get_id());
        } else if(counter == score) {
          suggestions.push_back(_users[i]->get_id());
        } 
      }
    }
    
    // If the suggestions vector is empty, this means there are no 
    // secondary connections, since we have already checked that the user
    // does indeed have friends. At this point the score is still at the 
    // correct value of -1, and the suggestions vector is empty.
    if(suggestions.empty()) {
      cout << "The user entered does not have any second connections." << endl;
    }
    
    // At this point, it is safe to return the suggestions vector -- it will
    // either be empty or it will contain friend suggestions. 
    return suggestions;
  }
}
