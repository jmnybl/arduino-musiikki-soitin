#ifndef _display_h_
#define _display_h_

#include <Arduino.h>

class Display {
  public:
    static byte digits[10];
    int *order;
    int *numbers;
    
    Display(int *numbers, int *order);
    void show(int num);
    void assign_order(int num);
};
    
#endif
