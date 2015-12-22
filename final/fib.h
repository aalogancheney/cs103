#ifndef FIB_H
#define FIB_H

#include <vector>

using namespace std;

class Fibonacci {
  public:
    Fibonacci();
    int get_next();
  private:
    vector<int> fib;
};

#endif
