#include <iostream>

using namespace std;

int main() {
  
  char array[80];
  cout << "Enter your first and last name: " << endl;
  cin.getline(array, 80);

  cout << array << endl;

  return 0;
}
