#include <iostream>
#include "fib.h"

using namespace std;

int main(int argc, char *argv[]) {
  Fibonacci fib;
  for(int i = 0; i < 10; i++) {
    cout << fib.get_next() << endl;
  }

  return 0;
}
