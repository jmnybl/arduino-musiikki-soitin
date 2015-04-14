#ifndef _timer_h_
#define _timer_h_

#include <Arduino.h>

class Timer {
  public:
    int secs;
    int last_update;
    
    Timer(int minutes, int seconds);
    void set_time(int minutes, int seconds);
    void increment(int minutes, int seconds);
    void update();
    int minutes();
    int seconds();
};
    
#endif
