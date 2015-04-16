#include <Arduino.h>
#include "mytimer.h"


MyTimer::MyTimer(int minutes, int seconds) {

  this->secs=seconds;
  this->last_update=millis();
  
}


void MyTimer::set_time(int minutes, int seconds) {
  this->secs=minutes*60+seconds;
}

void MyTimer::increment(int minutes, int seconds) {
  update();
  this->secs+=minutes*60+seconds;
  if (this->secs<0) {
    this->secs=0;  
  }
}

void MyTimer::update() {
  long current=millis();
  int t=(int)(current-last_update)/1000; // ...seconds
  if (t>0) {
    this->secs-=t;
    if (this->secs<0) {
      this->secs=0;  
    }
    this->last_update=current;
  }
}

int MyTimer::minutes() {
  return this->secs/60;  
}

int MyTimer::seconds() {
  return this->secs%60;  
}
