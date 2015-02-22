#include <Arduino.h>
#include "display.h"

#define order_size 8
#define numbers_size 4

byte Display::digits[]={0b11111100,0b01100000,0b11011010,0b11110010,0b01100110,0b10110110,0b10111110,0b11100000,0b11111110,0b11110110};

Display::Display(int *numbers, int *order) {
  
  this->order=order;
  this->numbers=numbers;
  this->del=10;
  
  for (int i=0;i<order_size;i++) {
    pinMode(order[i],OUTPUT);
    digitalWrite(order[i],LOW);
  }
  for (int i=0;i<numbers_size;i++) {
    pinMode(numbers[i],OUTPUT);
    digitalWrite(numbers[i],HIGH);
  }
  
  
}

/*
Show single digit in the display
*/
void Display::show_digit(int place, int num){
  clear_display();
  prepare_digit(num);
  digitalWrite(numbers[place-1],LOW);
}

/*
calculates HIGH and LOW pins in order to show one digit
*/
void Display::prepare_digit(int num) {
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


/*
Clear the LEDs (write LOW everywhere), do I need this??
*/
void Display::clear_LEDs() {
  clear_LEDs();
  for (int i=0;i<order_size;i++) {
    digitalWrite(order[i],LOW);
  }
}


/*
Clear the display
*/
void Display::clear_display() {
  for (int i=0;i<numbers_size;i++) {
    digitalWrite(numbers[i],HIGH);
  }
  
}

/*
Show the whole number (between 0-9999) in the LED display
time: for how long...?
*/
void Display::show_number(int number, int seconds) {
  
  int start_digit=0; // digits needed to show the number
  
  if (number<10) {
    start_digit=3;
  }
  else if (number<100) {
    start_digit=2;
  }
  else if (number<1000) {
    start_digit=1;
  }
  
  int digits[4];
  digits[3]=number%10; //units
  digits[2]=(number%100)/10; //tens
  digits[1]=(number%1000)/100; //hundreds
  digits[0]=(number%10000)/1000; //thousands
  
  clear_display(); 
  unsigned long start_time=millis();
  
  while (millis()-start_time<seconds*1000) {
    for (int j=start_digit;j<4;j++) {
      show_digit(j+1,digits[j]);
      delayMicroseconds(del);
    }
  }
  clear_display();
  
}

