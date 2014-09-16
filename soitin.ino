#include "display.h"


int numbers[]={2,3,4,5};
int order[]={13,12,9,7,8,11,10,6};
Display d(numbers,order);
void setup() {
  
}



void loop() {
  for (int i=0;i<10;i++) {
    d.assign_order(i);
    d.show(2);
    delay(1000);
  }
    
}
