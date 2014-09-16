#include <Arduino.h>
#include "display.h"

#define order_size 8
#define numbers_size 4

byte Display::digits[]={0b11111100,0b01100000,0b11011010,0b11110010,0b01100110,0b10110110,0b10111110,0b11100000,0b11111110,0b11110110};

Display::Display(int *numbers, int *order) {
  
  this->order=order;
  this->numbers=numbers;
  
  for (int i=0;i<order_size;i++) {
    pinMode(order[i],OUTPUT);
    digitalWrite(order[i],LOW);
  }
  for (int i=0;i<numbers_size;i++) {
    pinMode(numbers[i],OUTPUT);
    digitalWrite(numbers[i],HIGH);
  }
  
  
}


void Display::show(int num){
  for (int i=0;i<numbers_size;i++) {
    if (i+1==num) {
      digitalWrite(numbers[i],LOW);
    }
    else {
      digitalWrite(numbers[i],HIGH);
    }
  }
}

void Display::assign_order(int num) {
  byte number=digits[num];
  for (int i=0;i<order_size;i++) {
    if ((0b10000000 >> i) & number) {
      digitalWrite(order[i],HIGH);
    }
    else {
      digitalWrite(order[i],LOW);
    }
  }
}

