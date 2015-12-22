#include <cstdlib>
#include "timer.h"

Timer::Timer()
{
  total_ = 0;
}

void Timer::start()
{
  gettimeofday(&start_, NULL);
}

void Timer::stop()
{
  gettimeofday(&finish_, NULL);
  unsigned long long usecs;
  usecs = finish_.tv_sec*1000*1000 + finish_.tv_usec;
  usecs -= (start_.tv_sec*1000*1000 + start_.tv_usec);
  total_ += usecs;
}

void Timer::reset()
{
  total_ = 0;
}

double Timer::elapsed_ms()
{
  return static_cast<double>(total_) / 1000;
}

double Timer::elapsed_us()
{
  return static_cast<double>(total_);
}
