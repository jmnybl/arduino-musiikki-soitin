/*
 Audio part from http://arduino.cc/en/Tutorial/SimpleAudioPlayer
*/


#include "display.h"
#include "timer.h"
#include "step_motor.h"

#include <SD.h>
#include <SPI.h>
#include <Audio.h>

#define knobA 6 // pins for timer/track knob
#define knobB 7
#define push 8

int numbers[]={31,32,33,34}; // four different digits in display
int order[]={22,23,24,25,26,27,28,29}; // pins to form numbers A-G,DP
Display d(numbers,order);
Timer t(0,0);
StepMotor motor(513,36,37,38,39,-1); // stepper motor, pins 36-39, no indicator LED

void setup() {
  
  // DISPLAY AND BUTTON
  
  t.set_time(4,10); // 4 min, 10 secs
  d.clear_display();
  
  pinMode(knobA, INPUT_PULLUP); // pull-up resistors
  digitalWrite(knobA, HIGH);
  pinMode(knobB,INPUT_PULLUP);
  digitalWrite(knobB, HIGH);
  pinMode(push,INPUT_PULLUP);
  
  attachInterrupt(knobA, isr, CHANGE);
  attachInterrupt(knobB, isr, CHANGE);
  
  //  MUSIC PART
  
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

int track_counter = 0;
int increment = 0;
boolean confirmed=false;

void isr() {
  int a=digitalRead(knobA);
  int b=digitalRead(knobB);
  if (a==HIGH && b==HIGH) {
    if (confirmed) {
      // we have confirmed reading, and see HH first time (otherwise confirmed would be false)
      // --> it's okay to update the counter
      if (digitalRead(push)==LOW) {
        track_counter+=increment;
      }
      else {
        t.increment(increment,0);
      }
      confirmed=false;  
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
    }
  }
}


boolean sleep=false;
int tracks=2; // number of tracks we have in the SD card
int playing;
char* name_b = "track00";
char* name_e = ".wav";
char track_name[12];

void loop() {

  track_counter+=1;
  if (track_counter>tracks) {
    track_counter=1;
  }
  playing=track_counter;
  
  char numstr[1];
  
  sprintf(numstr, "%d", track_counter-1);
  strcpy(track_name, name_b);
  strcat(track_name, numstr);
  strcat(track_name, name_e);
  
  // open wave file from sdcard
  Serial.print("Playing ");
  Serial.println(track_name);
  File myFile = SD.open(track_name);
  if (!myFile) {
    // if the file didn't open, print an error and stop
    Serial.println("error opening .wav");
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
    
    // isr increments the counter, here just make sure it's not smaller than zero
    if (track_counter<1) {
      track_counter=1;  
    }
  
    // timer
    t.update();
  
    // display
    if (digitalRead(push)==LOW) {
      if (d.first_num!=track_counter) {
        d.update_number(track_counter);
      }
    }
    else {
      if (t.minutes()>0) {
        if (d.first_num!=t.minutes()) {
          d.update_number(t.minutes());
        }
      }
      else {
        if (d.first_num!=t.seconds()) {
          d.update_number(t.seconds());
        }
      }
    }
    d.show_next();
    
    // motor
    motor.singleStep(true);
    
    
    if (t.minutes()==0 && t.seconds()==0) { // out of time
      sleep=true;
      break;
    }
    
    if (playing!=track_counter) { // track must be changed, stop playing this one
      track_counter--; // in the beginning of the next loop, we will increment this by one so this makes sure we will play the track user really wants
      break;
    }

    
  }
  myFile.close();
  Serial.println("End of file. Thank you for listening!");
  
  
  while (sleep) {
    // ...do nothing
  }
  
  
}
