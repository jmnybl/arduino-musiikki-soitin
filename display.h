#ifndef _display_h_
#define _display_h_

#include <Arduino.h>

class Display {
  public:
    static byte digits[10];
    int *order;
    int *numbers;
    int del;
    
    int first_num;
    int current;
    int start_digit;
    int current_digits[4];
    
    Display(int *numbers, int *order);
    void show_digit(int place, int num);
    void prepare_digit(int num);
    void clear_LEDs();
    void clear_display();
    void show_number(int number, int time);
    void update_number(int number);
    void show_next();
};
    
#endif
