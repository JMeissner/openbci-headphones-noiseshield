#include "Arduino.h"
#include <SoftSerial.h>
#include <TinyPinChange.h>
#include "DFRobotDFPlayerMini.h"


const int buttonPin = 0;
const int potiPin = 3;

const int numberOfFolder = 3; //Number of Folders on the SD Card

SoftSerial mySoftwareSerial(1, 2); // RX, TX for DFPlayer
DFRobotDFPlayerMini myDFPlayer;

int DelayTime = 1000;
int currentFolder = 0;

void setup()
{
  pinMode(buttonPin, INPUT); 
  pinMode(potiPin, INPUT); 
  
  mySoftwareSerial.begin(9600);  
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.volume(5);  //Set volume value. From 0 to 30
}

 void loop()
 {
   //set volume through poti
   int poti = analogRead(potiPin);
   int volume = map(poti, 0, 1023, 0, 30); //Map analogRead range to DFPlayer volume range
   myDFPlayer.volume(volume);

   //Switch Folder if button is pressed
   if(digitalRead(buttonPin) == HIGH){
    currentFolder = (currentFolder + 1) % numberOfFolder;
    myDFPlayer.loopFolder((currentFolder + 1));
   }
   delay(100);
 }
