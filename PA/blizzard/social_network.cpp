#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include "network.h"
#include "user.h"

using namespace std;

// These functions are used to make the main() function as short as possible.
// Often, the functions are simply passing the network information as a pointer
// to another part of the file which then just read information provided by the 
// user, but the interface means that the file is compartmentalized, and the
// main() function is neat and short. 
void menu();
void header();
void add_user(Network *network);
void show_users(Network *network);
void add_connection(Network *network);
void show_friends(Network *network);
void remove_connection(Network *network);
void write_friends(Network *network);
// These functions have been added for PA5. Just like all of the functions 
// above, they have been added to make the interface in main() easier to 
// read. Ultimately, member functions in the Network class are called to 
// perform the correct actions. 
void shortest_path(Network *network);
void reset_search(Network *network);
void disjoint_sets(Network *network);
void suggest_friends(Network *network);

int main(int argc, char *argv[]) {
  // Creates a Network variable, which will then be filled by the user/file.
  // It is the only Network variable throughout the program. 
  Network newNetwork;
  
  // Checks that the right commandline arguments are used, and also checks 
  // to see that the file was successfully read. 
  if(argc < 2) {
    cout << "Usage: ./networktest filename" << endl;
    return 1;
  } else {
    int success = newNetwork.read_friends(argv[1]);
    if(success == -1) {
      cout << "Could not read file " << argv[1] << endl;
      cout << "You still have an empty network." << endl;
    }
  }

  // Shows the menu options to the user, and then starts a series of if-else
  // statements to check what option the user has selected. From there, a 
  // function is called, passing the network by reference, and the menu is 
  // printed again to show the user what operations they can perform. 
  menu();
  int menuSelection;
  while(cin >> menuSelection) {
    if(menuSelection == 1) {
      cout << endl;
      add_user(&newNetwork);
      menu();
    } else if(menuSelection == 2) {
      cout << endl;
      add_connection(&newNetwork);
      menu();
    } else if(menuSelection == 3) {
      cout << endl;
      remove_connection(&newNetwork);
      menu();
    } else if(menuSelection == 4) {
      cout << endl;
      show_users(&newNetwork);
      menu();
    } else if(menuSelection == 5) {
      cout << endl;
      show_friends(&newNetwork);
      menu();
    } else if(menuSelection == 6) {
      cout << endl;
      write_friends(&newNetwork);
      menu();
    } else if(menuSelection == 7) {
      cout << endl;
      shortest_path(&newNetwork);
      reset_search(&newNetwork);
      menu();
    } else if(menuSelection == 8) {
      cout << endl;
      disjoint_sets(&newNetwork);
      reset_search(&newNetwork);
      menu();
    } else if(menuSelection == 9) {
      cout << endl;
      suggest_friends(&newNetwork);
      reset_search(&newNetwork);
      menu();
    } else {
      break;
    }
  }
  
  cout << "Thanks for using my social network!" << endl;
  
  return 0;
}

// Simply a list of the actions a user can perform. This is shown after each
// action to remind the user what they can do. 
void menu() {
  cout << "Please select from the following options: " 
       << endl;
  cout << "1: Add a user (Enter: 1 firstName lastName birthYear zipCode)" 
       << endl;
  cout << "2: Add a connection (Enter: 2 firstName1 lastName1 firstName2 lastName2)"
       << endl;
  cout << "3: Remove connection (Enter: 3 firstName1 lastName1 firstName2 lastName2)"
       << endl;
  cout << "4: Print users (Enter: 4)" 
       << endl;
  cout << "5: Show friends (Enter: 5 firstName lastName)" 
       << endl;
  cout << "6: Write network to a file (Enter: 6 fileName)"
       << endl;
  cout << "7: Shortest path (Enter: 7 firstName1 lastName1 firstName2 lastName2)"
       << endl;
  cout << "8: Disjoint sets (Enter: 8)"
       << endl;
  cout << "9: Suggest friends (Enter: 9 firstName lastName)"
       << endl << endl;
}

// This function adds a user to the network based on the information provided
// by the user. The appropriate variables are gotten from the user using cin,
// placed into variables, and then that information is passed to the actual 
// function that creates a user. 
void add_user(Network *network) {
  string tempFirstName;
  string tempLastName;
  int tempYear;
  int tempZip;
  cin >> tempFirstName;
  cin >> tempLastName;
  cin >> tempYear;
  cin >> tempZip;
  string name = tempFirstName + " " + tempLastName;
  network->add_user(name, tempYear, tempZip);
}

// Shows the users in the network using the print_user() member function of the
// network class. 
void show_users(Network *network) {
  header();
  for(unsigned int i = 0; i < network->get_users().size(); i++) {
    network->print_user(network->get_users()[i]->get_id());
    cout << endl;
  }
}

// Adds a connection between two users. Again, the interface is burried in this
// function to make main() easier to read. The add_connection() member function
// is called to perform the action once the user-entered information is read. 
void add_connection(Network *network) { 
  string firstNameOne;
  string lastNameOne;
  string firstNameTwo;
  string lastNameTwo;
  cin >> firstNameOne >> lastNameOne >> firstNameTwo >> lastNameTwo;
  string nameOne = firstNameOne + " " + lastNameOne;
  string nameTwo = firstNameTwo + " " + lastNameTwo;
  if(nameOne == nameTwo) {
    cout << "You cannot be friends with yourself." << endl;
    return;
  }
  int temp = network->
             add_connection(network->get_id(nameOne), network->get_id(nameTwo)); 
  if(temp == -1) {
    cout << "Could not perform that action." << endl;
    return;
  }
}

// Removes a connection between two users. The interface here will ultimately
// pass information to the network using the remove_connection() member
// function. 
void remove_connection(Network *network) { 
  string firstNameOne;
  string lastNameOne;
  string firstNameTwo;
  string lastNameTwo;
  cin >> firstNameOne >> lastNameOne >> firstNameTwo >> lastNameTwo;
  string nameOne = firstNameOne + " " + lastNameOne;
  string nameTwo = firstNameTwo + " " + lastNameTwo;
  int temp = network->remove_connection(network->get_id(nameOne), 
                                        network->get_id(nameTwo)); 
  if(temp == -1) {
    cout << "Could not perform that action." << endl;
  }
}

// Shows the friends of a given user. 
void show_friends(Network *network) {
  string firstName;
  string lastName;
  cin >> firstName >> lastName;
  string name = firstName + " " + lastName;
  int id = -1;
  // Checks to see if the user exists within the network. 
  for(unsigned int i = 0; i < network->get_users().size(); i++) {
    if(network->get_users()[i]->get_name() == name) {
      id = i;
    }
  }
  
  // This vector is used to store the friends of the user. 
  vector<int> friends;
  // This if-else block will run through the possibilities: either the user
  // doesn't exist in the network, the user doesn't have any friends, 
  // or the user has friends. If the last case is so, then the print_user()
  // member function is used to print each friend. 
  if(id == -1) {
    cout << "The user " << name << " doesn't exist." << endl;
  } else if(network->get_users()[id]->get_friends()->empty()) {
      cout << "The user " << name << " doesn't have any friends." << endl;
  } else {
    header();
    for(unsigned int i = 0; i < network->get_users()[id]->get_friends()->size();
        i++) {
      network->print_user(network->get_users()[id]->get_friends()[0][i]);
      cout << endl;   
    }
  }
}

// A simple function used to provide a header each time information is printed
// to the screen. 
void header() {
  cout << "ID" << setw(4) << " "
       << "Name" << setw(20) << " "
       << "Year" << setw(6) << " "
       << "Zip" << setw(7) << " " << endl;
  cout << "=============================================" << endl;
}

// A function used to write information to a file. Again, the interface will
// ultimately pass the inforamtion to the write_friends() member function. 
void write_friends(Network *network) {
  string outFile;
  cin >> outFile;
  char *outputFile = new char[outFile.length() + 1];
  strcpy(outputFile, outFile.c_str());
  network->write_friends(outputFile);
  delete [] outputFile;
}

// Any function after this point is added for PA5.

// This function is used to find the path between two users entered. Just like
// most of the functions above, this function only serves to simplify the
// code in main(). Ultimately, the shortest_path() member function is called.
void shortest_path(Network *network) {
  // These lines get the names of the two users.
  string firstNameOne;
  string lastNameOne;
  string firstNameTwo;
  string lastNameTwo;
  cin >> firstNameOne >> lastNameOne >> firstNameTwo >> lastNameTwo;
  string nameOne = firstNameOne + " " + lastNameOne;
  string nameTwo = firstNameTwo + " " + lastNameTwo;
  
  // A vector called path is created, since the return value of the member
  // function shortest_path() is a vector.
  vector<int> path = 
  network->shortest_path(network->get_id(nameOne), network->get_id(nameTwo));
  
  // If path is empty, then there was no connection, and the action could
  // not be performed. Otherwise, there was a path found and it is displayed
  // back to the user. 
  if(path.empty()) {
    cout << "Could not perform that action." << endl;
  } else {
    cout << "Distance: " << path.size() - 1 << endl;
    for(unsigned int i = 0; i < path.size(); i++) {
      cout << network->get_users()[path[i]]->get_name();
      if(network->get_users()[path[i]]->get_name() != nameTwo)
      {
        cout << " -> ";
      }
    }
    cout << endl;
  }
}

// This function is used to reset the _depth, _predecessor, and _set values of 
// all of the users in the network after performing a search on the network. 
// This is because in a single run of the program, if a user is found during one
// search, they will be found for all subsequent searches. 
void reset_search(Network *network) {
  for(unsigned int i = 0; i < network->get_users().size(); i++) {
    network->get_users()[i]->set_depth(-1);
    network->get_users()[i]->set_predecessor(-1);
    network->get_users()[i]->set_set(-1);
    network->get_users()[i]->set_score(-1);
  }
}

// This function is used to print the disjoint sets in the network. The 
// groups() member function is called on the network, and the for loop 
// construction below is used to print all users in each set. 
void disjoint_sets(Network *network) {
  vector< vector<int> > groups = network->groups();
  
  for(unsigned int i = 0; i < groups.size(); i++) {
    cout << "Set " << i + 1 << ": ";
    for(unsigned int j = 0; j < groups[i].size(); j++) {
      cout << network->get_users()[groups[i][j]]->get_name();
      if(j != groups[i].size() - 1) {
        cout << ", ";
      }
    }
    cout << endl;
  }
}

// This function is used to suggest friends for a given user. 
void suggest_friends(Network *network) {
  // Gets the name of the user from the prompt. 
  string firstName;
  string lastName;
  cin >> firstName >> lastName;
  string name = firstName + " " + lastName;
  int id = -1;

  // Checks to see that the user exists. 
  for(unsigned int i = 0; i < network->get_users().size(); i++) {
    if(network->get_users()[i]->get_name() == name) {
      id = i;
    }
  }
  
  // If the user does not exist, then no further action is taken and the 
  // function exits. Otherwise, the suggest_friends() member function is called
  // with the given id, and the suggestions are shown at the prompt. 
  if(id == -1) {
    cout << "The user " << name << " doesn't exist." << endl;
  } else {
    int score;
    vector<int> suggestions = network->suggest_friends(id, score);
    
    if(suggestions.empty()) {
      cout << "Could not perform that action." << endl;
    } else {
      cout << "The suggested friend(s) is/are: " << endl;
      for(unsigned int i = 0; i < suggestions.size(); i++) {
        cout << '\t' << network->get_users()[suggestions[i]]->get_name() << " "
             << setw(28-network->get_users()[suggestions[i]]->get_name().size())
             << " Score: " << score << endl;
      }
    }
  }
}
