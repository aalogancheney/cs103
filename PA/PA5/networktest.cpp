#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include "network.h"
#include "user.h"

using namespace std;

void menu();
void header();
void add_user(Network *network);
void show_users(Network *network);
void add_connection(Network *network);
void show_friends(Network *network);
void remove_connection(Network *network);
void write_friends(Network *network);

int main(int argc, char *argv[]) {
  Network newNetwork;
  
  if(argc < 2) {
    cout << "Usage: ./networktest filename" << endl;
    return -1;
  } else {
    int success = newNetwork.read_friends(argv[1]);
    if(success == -1) {
      cout << "Could not read file " << argv[1] << endl;
      cout << "You still have an empty network." << endl;
    }
  }

  menu();
  int menuSelection;
  while(cin >> menuSelection) {
    if(menuSelection == 1) {
      add_user(&newNetwork);
      menu();
    } else if(menuSelection == 2) {
      add_connection(&newNetwork);
      menu();
    } else if(menuSelection == 3) {
      remove_connection(&newNetwork);
      menu();
    } else if(menuSelection == 4) {
      show_users(&newNetwork);
      menu();
    } else if(menuSelection == 5) {
      show_friends(&newNetwork);
      menu();
    } else if(menuSelection == 6) {
      write_friends(&newNetwork);
      menu();
    } else {
      break;
    }
  }
  
  // newNetwork.add_user(0, "Aaron Cheney", 1990, 91780);
  
  // int name = newNetwork.get_users().front()->get_birthYear();
  // cout << name << endl;
  
  return 0;
}

void menu() {
  cout << endl;
  cout << "Please select from the following options: " << endl;
  cout << "1: Add a user (enter the user information on the same line)" << endl;
  cout << "2: Add a connection between users (Enter the names on the same line)"
       << endl;
  cout << "3: Remove connection between users (Enter the names on the same line)"
       << endl;
  cout << "4: Print users (only enter the number 4)" << endl;
  cout << "5: Show friends (enter the name of the person on the same line)" 
       << endl;
  cout << "6: Write user contents to a file (enter file name on same line)"
       << endl;
}

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

void show_users(Network *network) {
  header();
  for(unsigned int i = 0; i < network->get_users().size(); i++) {
    network->print_user(network->get_users()[i]->get_id());
    /*cout << users[i]->get_id() << " " 
         << users[i]->get_name() << " "
         << users[i]->get_birthYear() << " "
         << users[i]->get_zipCode() << " ";
    /*for(unsigned int j = 0; j < users[i]->get_friends()->size(); j++) {
      cout << users[i]->get_friends()[0][j] << " ";
    }*/
    cout << endl;
  }
}

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
  int temp = network->add_connection(nameOne, nameTwo); 
  if(temp == -1) {
    cout << "Could not perform that action." << endl;
    return;
  }
}

void remove_connection(Network *network) { 
  string firstNameOne;
  string lastNameOne;
  string firstNameTwo;
  string lastNameTwo;
  cin >> firstNameOne >> lastNameOne >> firstNameTwo >> lastNameTwo;
  string nameOne = firstNameOne + " " + lastNameOne;
  string nameTwo = firstNameTwo + " " + lastNameTwo;
  int temp = network->remove_connection(nameOne, nameTwo); 
  if(temp == -1) {
    cout << "Could not perform that action." << endl;
  }
}

void show_friends(Network *network) {
  string firstName;
  string lastName;
  cin >> firstName >> lastName;
  string name = firstName + " " + lastName;
  int id = -1;
  for(unsigned int i = 0; i < network->get_users().size(); i++) {
    if(network->get_users()[i]->get_name() == name) {
      id = i;
    }
  }
  
  vector<int> friends;
  if(id == -1) {
    cout << "The user " << name << " doesn't exist." << endl;
  } else {
    for(unsigned int i = 0; i < network->get_users()[id]->get_friends()->size(); i++) {
      friends.push_back(network->get_users()[id]->get_friends()[0][i]);
    }
    if(friends.empty()) {
      cout << "The user " << name << " doesn't have any friends." << endl;
    } else {
      header();
      for(unsigned int i = 0; i < friends.size(); i++) {
        network->print_user(friends[i]);
        cout << endl;
      }
    }
  }
}

void header() {
  cout << "ID" << setw(4) << " "
       << "Name" << setw(20) << " "
       << "Year" << setw(6) << " "
       << "Zip" << setw(7) << " " << endl;
  cout << "=============================================" << endl;
}

void write_friends(Network *network) {
  string outFile;
  cin >> outFile;
  char *outputFile = new char[outFile.length() + 1];
  strcpy(outputFile, outFile.c_str());
  network->write_friends(outputFile);
}
