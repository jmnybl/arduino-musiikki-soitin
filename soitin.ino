
#include "display.h"


int numbers[]={2,3,4,5}; // four different digits in display
int order[]={13,12,9,7,8,11,10,6}; // pins to form numbers
Display d(numbers,order);
void setup() {
  //Serial.begin(9600);
}



void loop() {
  d.show_number(2,5);
  delay(1000);
  d.show_number(1113,5);
  delay(1000);
  d.show_number(316,2);
  delay(1000);
  d.clear_display();
  delay(1000);
  
  
}


/*

 Demonstrates the use of the Audio library for the Arduino Due

 Hardware required :
 *Arduino shield with a SD card on CS 4 (the Ethernet sheild will work)
 *Speaker attched to ground and DAC0

 Original by Massimo Banzi September 20, 2012
 Modified by Scott Fitzgerald October 19, 2012

*/
/*
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
