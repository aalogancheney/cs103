#include <iostream>
#include "clock.h"

using namespace std;

int main(int argc, char* argv[]) {
  Clock clockOne;
  Clock clockTwo(12, 59, 0);
  
  clockTwo.SetAlarmTime(13, 0, 0);
  
  for(int i = 0; i < 65; i++) {
    clockTwo.tickTock();
    clockTwo.printTime();
  }

  return 0;
}
