#include <iostream>
#include <vector>

using namespace std;

int fib(int n, vector<int>& memory);

int main(int argc, char *argv[]) {
  vector<int> memory(8, 0);
  
  cout << fib(3, memory) << endl;
  cout << fib(6, memory) << endl;

  return 0;
}

int fib(int n, vector<int>& memory) {
  if(memory[n] != 0) {
    return memory[n];
  }
  
  if(n == 1 || n == 2) {
    memory[n] = 1;
  } else {
    memory[n] = fib(n - 1, memory) + fib(n - 2, memory);
  }
  return memory[n];
}
