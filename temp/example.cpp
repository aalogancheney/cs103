#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
  char *buffer = new char[80];
  strcpy(buffer, "Question");
  strcpy(buffer + 5, "s");
  strcpy(buffer + 10, "test");
  
  cout << buffer + 7 << endl;

  cout << buffer + 10 << endl;

  cout << buffer << endl;

  return 0;
}
