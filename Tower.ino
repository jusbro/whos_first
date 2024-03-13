/*Arduino Uno REV3 Server (tower) Control for Who's First Device
This software is designed to run on a Uno REV 3. Its purpose is to act as a server that receives transmissions from up to six student remotes

Version 0.91
Last updated 2/19/2024
*/

//IMPORTS
#include <SPI.h>
#include <RF24.h>


//Pins used for the RF Module vary based on board used
//Arduino Uno CE 8, CSN 10
//Arduino Nano CE 7, CSN 8
#define CE_PIN 8
#define CSN_PIN 10

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

//Create the payload vessel
char receivedPayload[32];  

//Create Strings to store first and second place remotes
String firstRemote = "";
String secondRemote = "";

//Light Declarations
  //Six 9Volt lights are to be connected
  //Arduino Pins 2 to 7
const int numLights = 6;
//Create an array of light pins for easy access
int lights[] = {2,3,4,5,6,7};

//Pin that the speaker in the tower is connected to
int tonePin = A5;

//Delays used in program
int testLightDelay = 100;
int testLightDelayShort = 10;

void firstLight(String remote){
  //This function runs after the first remote sends its payload
  //It turns on the light that matches that remote and keeps it on solid
  //If a second remote sends its payload, secondLight() is called
  if (remote == "A"){
    digitalWrite(2, HIGH);
  } else if (remote == "C"){
    digitalWrite(3, HIGH);
  }
  winTone();
}
void secondLight(String firstRemote, String secondRemote){
  //This function is called when a second remote sends its payload
  //It indicates which remote was first by changing that light to a flashing pattern.
  //The second remote's light will turn on as solid
  if (secondRemote == "A"){
    digitalWrite(2, HIGH);
  }else if (secondRemote == "B"){
    digitalWrite(3, HIGH);
  } else if (secondRemote == "C"){
    digitalWrite(4, HIGH);
  } else if (secondRemote == "D"){
    digitalWrite(5, HIGH);
  }else if (secondRemote == "E"){
    digitalWrite(6, HIGH);
  }else if (secondRemote == "F"){
    digitalWrite(7, HIGH);
  }
  if (firstRemote == "A"){
    while (1){
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2,LOW);
      delay(500);
    }
  } else if(firstRemote == "B"){
    while (1){
      digitalWrite(3, HIGH);
      delay(500);
      digitalWrite(3,LOW);
      delay(500);
    }
  }else if(firstRemote == "C"){
    while (1){
      digitalWrite(4, HIGH);
      delay(500);
      digitalWrite(4,LOW);
      delay(500);
    }
  }else if(firstRemote == "D"){
    while (1){
      digitalWrite(5, HIGH);
      delay(500);
      digitalWrite(5, LOW);
      delay(500);
    }
  }else if(firstRemote == "E"){
    while (1){
      digitalWrite(6, HIGH);
      delay(500);
      digitalWrite(6, LOW);
      delay(500);
    }
  }else if(firstRemote == "F"){
    while (1){
      digitalWrite(7, HIGH);
      delay(500);
      digitalWrite(7,LOW);
      delay(500);
    }
  }
}

void winTone(){
  //This function plays a tone over the tone pin when called
  //Typical cases could include error notification, remote data received, etc.
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

void radioErrorFlashLEDs(){
//This fuction is called when there is an error starting up the radio module
//Due to the final product not having serial connection, LEDs will be used for error detection

  for (int i = 0; i<10; i++){
    //Flash the LEDs 10 times
    for (int i = 0; i<numLights; i++){
      digitalWrite(lights[i], HIGH);
    }
    delay(300);
    for (int i = 0; i<numLights; i++){
      digitalWrite(lights[i], LOW);
    }
    delay(300);
  }
}

void setup() {
  //Check to see if radio can start
  Serial.begin(9600);
  
  if (!radio.begin()) {
    //If the radio cannot connect, go to the error notification function
    radioErrorFlashLEDs();
    while (1) {}  
  }


  //Setup all light pins as outputs
  for (int i = 0; i < numLights; i++) {
    pinMode(lights[i], OUTPUT); // Set each pin in the lights[] array as an output
  }

  //Assign an address, must match remotes
  radio.openReadingPipe(1, 0x12341234);
  //Set radio power level. MAX may not work when radios are close together  
  radio.setPALevel(RF24_PA_LOW);
  //Start listening for transmissions
  radio.startListening();
  //Small delay seems necessary to start radio
  delay(100);
  //Set tone pin as an output
  pinMode(tonePin, OUTPUT);
  //Test Lights
  lightTest();

  Serial.println("Ready");
  delay(100);

}

void loop() {
  //If data is received from a remote: 
  if (radio.available()) {
    //Set the received data into the payload
    radio.read(&receivedPayload, sizeof(receivedPayload));
    //Convert it to a string
    String remote = String(receivedPayload);
    Serial.println("Got Data: " + remote);
    //Determine if this is the first remote to respond
    if (firstRemote ==""){
      //if so, store this remote's payload as the firstRemote
      firstRemote = remote;
      Serial.println("First Place:"+ firstRemote);
      firstLight(remote);
    }else if (secondRemote == ""){
      secondRemote = remote;
      Serial.println("Second Place:"+ secondRemote);
      secondLight(firstRemote, secondRemote);
    }


    //Temporary delay to debug more easily. Will be minimized in final code 
    delay(10);
  }

}
