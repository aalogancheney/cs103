#include <iostream>
using namespace std;

int main()
{
  int x = -1;
  cout << "Enter an int: " << endl;
  cin >> x;

  if (cin.fail()) {
    cout << "You did not enter an int!!" << endl;
  } else {
    cout << "Good you entered: " << x << endl;
  }

  cin >> x;

  if (cin.fail()) {
    cout << "You did not enter an int!!" << endl;
  } else {
    cout << "Good you entered: " << x << endl;
  }

  return 0;
}
