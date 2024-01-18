/*
Whose First Arduino Retrofit
Creators: Justin Brown and Greg King
Origin Date: 1/8/2024

The goal of this program is to retrofit an Arduino into a "Who's First device to allow future support"

Version: 0.1
Date: 1/8/2024
Contributor: Justin Brown
Notes: Created file, laid out framework, added transistor controls


This program controls six 9 volt lights (denoted by L#(0-5) EX: L1) via NPN transistors
*/

//IMPORTS
//#include <SPH.h>
#include <RF24.h>

//Light Declarations
//Six 9Volt lights are to be connected
//Arduino Pins 7, 8, 9, 10, 11, and 12
const int numLights = 6;
int lights[] = {7,8,9,10,11,12};

int tonePin = A5;

int testLightDelay = 250;
int testLightDelayShort = 10;

void winTone(){
  static int freq = 2150;
  static int del = 40;
  tone(tonePin, freq);
  delay(del);
  noTone(tonePin);
  delay(del);
  tone(tonePin, freq);
  delay(del);
  noTone(tonePin);
}

void lightTest(){
  //This functions tests the bulbs
  //It cycles on at the beginning of powerup
  //It should cycle lights from the bottom of the tower to the top, then return back down
  for (int i = 0; i<numLights; i++){
    digitalWrite(lights[i], HIGH);
    delay(testLightDelay);
    digitalWrite(lights[i], LOW);
    delay(testLightDelayShort);
  }  for (int i = numLights; i>-1; i--){
    digitalWrite(lights[i], HIGH);
    delay(testLightDelay);
    digitalWrite(lights[i], LOW);
    delay(testLightDelayShort);
  }

}



void setup() {

//Setup all light pins as outputs
for (int i = 0; i < numLights; i++) {
    pinMode(lights[i], OUTPUT); // Set each pin in the lights[] array as an output
  }
pinMode(tonePin, OUTPUT);
lightTest();
winTone();
}

void loop() {
lightTest();

}
