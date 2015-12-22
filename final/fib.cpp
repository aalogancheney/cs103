#include "fib.h"
#include <vector>

using namespace std;

Fibonacci::Fibonacci () {
  
}

int Fibonacci::get_next() {
  if(fib.size() == 0) {
    fib.push_back(1);
    return fib.back();
  } else if(fib.size() == 1) {
    fib.push_back(1);
    return fib.back();
  } else {
    fib.push_back(fib.back() + fib[fib.size() - 2]);
    return fib.back();
  }
}
