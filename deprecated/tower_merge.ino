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
#include <SPI.h>
#include <RF24.h>

//Arduino Uno CE 8, CSN 10
//Arduino Nano CE 7, CSN 8
#define CE_PIN 8
#define CSN_PIN 10

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

char receivedPayload[32];  

//Light Declarations
//Six 9Volt lights are to be connected
//Arduino Pins 3 to 7
const int numLights = 6;
//int lights[] = {7,8,9,10,11,12};
int lights[] = {2,3,4,5,6,7};

int tonePin = A5;

int testLightDelay = 100;
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
  Serial.begin(9600);
  Serial.println("In Setup Loop");
  delay(50);
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!!");
    while (1) {}  // If not, hold in infinite loop
  }else{
    Serial.println("Radio Started");
  }

  //for (int i = 0; i < numLights; i++) {
  //   pinMode(lights[i], OUTPUT); // Set each pin in the lights[] array as an output
  //  }
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.println("Lights Created");

  radio.openReadingPipe(1, 0x12341234);  
  radio.setPALevel(RF24_PA_LOW);
  //Start listening for transmissions
  radio.startListening();


  //Declare end of startup over Serial
  Serial.println(F("All Radio Calls Complete"));
  delay(100);

  pinMode(tonePin, OUTPUT);
  //lightTest();
  //winTone();
  delay(10);
  lightTest();
  Serial.println("Setup Complete");
  delay(100);

}

void loop() {

  if (radio.available()) {
    Serial.println("Data Coming In");
    radio.read(&receivedPayload, sizeof(receivedPayload));
    Serial.print(F("Received Payload: "));
    String remote = String(receivedPayload);
    Serial.println(receivedPayload);
    if(remote == "A"){
      digitalWrite(2, HIGH);
      delay(10);
      Serial.println("Turning on '2' LED");
      delay(10);
    }else if(remote == "B"){
      digitalWrite(2, LOW);
      delay(10);
      Serial.println("Turning off '2' LED");
    } else if(remote == "C"){
      digitalWrite(3, HIGH);
      delay(10);
      Serial.println("Turning off '3' LED");
    } else if(remote == "D"){
      digitalWrite(3, LOW);
      delay(10);
      Serial.println("Turning off '3' LED");
    }
  }
  //digitalWrite(6, HIGH);
  //Temporary delay to debug more easily. Will be minimized in final code 
  delay(10);
  //digitalWrite(6, LOW);  
  //delay(100);
}
