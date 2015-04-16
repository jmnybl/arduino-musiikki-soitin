#ifndef _mytimer_h_
#define _mytimer_h_

#include <Arduino.h>

class MyTimer {
  public:
    int secs;
    long last_update;
    
    MyTimer(int minutes, int seconds);
    void set_time(int minutes, int seconds);
    void increment(int minutes, int seconds);
    void update();
    int minutes();
    int seconds();
};
    
#endif
