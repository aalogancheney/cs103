#include <iostream>
#include "clock.h"

using std::cout;
using std::endl;

Clock::Clock() {
  currentHour = 12;
  currentMinute = 0;
  currentSecond = 0;
  alarmHour = 12;
  alarmMinute = 0;
  alarmSecond = 0;
}  

Clock::Clock(int hour, int minute, int second) {
  currentHour = hour;
  currentMinute = minute;
  currentSecond = second;
  alarmHour = 12;
  alarmMinute = 0;
  alarmSecond = 0;
  alarmOn = false;
}

void Clock::SetAlarmTime(int hour, int minute, int second) {
  alarmHour = hour;
  alarmMinute = minute;
  alarmSecond = second;
  
  alarmOn = true;
}

void Clock::TurnAlarmOff() {
  alarmOn = false;
}

void Clock::printTime() {
  cout << currentHour << ":" << currentMinute << ":" << currentSecond << endl;
}

void Clock::tickTock() {
  currentSecond++;
  if(currentSecond == 60) {
    currentSecond = 0;
    currentMinute++;
    if (currentMinute == 60) {
      currentMinute = 0;
      currentHour++;
      if(currentHour == 24) {
        currentHour = 0;
      }
    }
  }
  
  if(currentHour == alarmHour && currentMinute == alarmHour && 
     currentSecond == alarmSecond && alarmOn) {
    cout << "Alarm!!" << endl;   
  }
}
