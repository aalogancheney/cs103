#include <iostream>
#include <cstdlib>
#include "timer.h"

using namespace std;

int main()
{
  const int SIZE = 8192;
  static unsigned char image[SIZE][SIZE];
  
  Timer t;   // declares a timer variable
  t.start(); // starts the timer
  for(int i=0; i < SIZE; i++){
    for(int j=0; j < SIZE; j++){
      image[i][j] = rand() % 256;
    }    
  }
  t.stop();  // stops the timer
  double ms = t.elapsed_ms(); // gets the time that elapsed 
                              // between start and stop

  cout << "Nested for loops of size " << SIZE;
  cout << " took " << ms << " millisecond" << endl;

  return 0;
}
