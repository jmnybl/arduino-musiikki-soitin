
#include "display.h"
#include "timer.h"

#define knobA 52 // pins for timer/track knob
#define knobB 53
#define push 50

int numbers[]={31,32,33,34}; // four different digits in display
int order[]={22,23,24,25,26,27,28,29,30}; // pins to form numbers A-G,DP
Display d(numbers,order);
Timer t(0,0);

void setup() {
  
  
  t.set_time(1,10); // 1 min, 10 secs
  d.clear_display();
  
  pinMode(knobA, INPUT_PULLUP); // pull-up resistors
  digitalWrite(knobA, HIGH);
  pinMode(knobB,INPUT_PULLUP);
  digitalWrite(knobB, HIGH);
  pinMode(push,INPUT_PULLUP);
  
  attachInterrupt(knobA, isr, CHANGE);
  attachInterrupt(knobB, isr, CHANGE);

  // Serial.begin (9600);

}

int track_counter = 0;
int increment = 0;
boolean confirmed=false;
boolean pushed=false;

void isr() {
  int a=digitalRead(knobA);
  int b=digitalRead(knobB);
  if (a==HIGH && b==HIGH) {
    if (confirmed) {
      // we have confirmed reading, and see HH first time (otherwise confirmed would be false)
      // --> it's okay to update the counter
      if (pushed) {
        track_counter+=increment;
      }
      else {
        t.increment(increment,0);
      }
      confirmed=false;
      pushed=false;  
    }
    else {
      // HH and reading not confirmed --> bouncing back to start or new round is not yet started
      return;
    }
  }
  else if (a==LOW && b==LOW) {
    // this confirms that last reading we saw is correct, do not update it after this
    confirmed=true;
  }
  else {
    if (confirmed) {
      // we already confirmed our reading so do not update it anymore, this is
      // just bouncing, or we are waiting the next HH
      return;
    }
    else {
      // decide the increment (clockwise or counter clockwise)
      if (a==HIGH) {
        increment=1;
      }
      else {
        increment=-1;
      }
      // check also the push button and store the value so we know which one to increment
      if (digitalRead(push)==LOW) {
        pushed=true;
      }
    }
  }
}

void loop() {
  
  // isr increments the counters, here just make sure they are not smaller than zero
  if (track_counter<0) {
    track_counter=0;  
  }
  
  t.update();
  
  // display
  if (digitalRead(push)==LOW) {
    d.show_number(track_counter,10);
  }
  else {
    if (t.minutes()>0) {
      d.show_number(t.minutes(),10);
    }
    else {
      d.show_number(t.seconds(),10);
    }
  }
}


/*

 Demonstrates the use of the Audio library for the Arduino Due

 Hardware required :
 *Arduino shield with a SD card on CS 4 (the Ethernet sheild will work)
 *Speaker attched to ground and DAC0

 Original by Massimo Banzi September 20, 2012
 Modified by Scott Fitzgerald October 19, 2012


#include <SD.h>
#include <SPI.h>
#include <Audio.h>

void setup()
{
  // debug output at 9600 baud
  Serial.begin(9600);

  // setup SD-card
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println(" failed!");
    return;
  }
  Serial.println(" done.");
  // hi-speed SPI transfers
  SPI.setClockDivider(4);

  // 44100 Hz stereo => 88200 sample rate
  // 100 mSec of prebuffering.
  Audio.begin(88200, 100);
}

void loop()
{
  int count=0;

  // open wave file from sdcard
  File myFile = SD.open("dl.wav");
  if (!myFile) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening test.wav");
    while (true);
  }

  const int S=1024; // Number of samples to read in block
  short buffer[S];

  Serial.print("Playing");
  // until the file is not finished
  while (myFile.available()) {
    // read from the file into buffer
    myFile.read(buffer, sizeof(buffer));

    // Prepare samples
    int volume = 1023;
    Audio.prepare(buffer, S, volume);
    // Feed samples to audio
    Audio.write(buffer, S);

    // Every 100 block print a '.'
    count++;
    if (count == 100) {
      Serial.print(".");
      count = 0;
    }
  }
  myFile.close();

  Serial.println("End of file. Thank you for listening!");
  while (true) ;
}
*/
