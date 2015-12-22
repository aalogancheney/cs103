#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

class Timer {
public:
  Timer();

  /// Starts the timer from the current elapsed time
  void start();

  /// Stops the timer and updates the elapsed time
  void stop();

  /// Resets the elapsed time to 0
  void reset(); 

  /// Returns the total elapsed time in milliseconds 
  ///  Precondition: Must have stopped the watch already
  double elapsed_ms();

  /// Returns the total elapsed time in microseconds 
  ///  Precondition: Must have stopped the watch already
  double elapsed_us();

private:
  unsigned long long total_;
  struct timeval start_;
  struct timeval finish_;
};

#endif
