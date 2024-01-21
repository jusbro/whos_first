/*
REMOTE-SIDE WIRELESS TRANSMITTER

This code runs on all of the six wireless remotes. The remotes transmit data to a "whose first" tower. Each remote is given a unique identifier.
The whose first tower registers remotes that send their identifier and list them in order of acceptance

TO DO LIST:
1) Add button that will be pressed to send the payload
  a) Ensure only one transmission of payload per button push
2) Determine what the final payload will be for each remote
3) Test on external power
4) Test without serial connection
5) Test on Nano Every board (final deployment hardware)
6) Design and build PCB
7) Determine if anti-ID is needed in final design of whose first 
*/
#include <SPI.h>
#include "RF24.h"

//Arduino Uno CE 8, CSN 10
//Arduino Nano CE 7, CSN 8
#define CE_PIN 7
#define CSN_PIN 8

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

//Create this remote's unique ID.
//This is temporarily A, B, C, etc. but may be changed to any character in the future
//May also create an "anti-character" ID in the future that sends an "off" command to the whose first tower
char payload[] = "A";


void setup() {
  //Start Serial for debug purposes. This can be removed in final product
  Serial.begin(9600);
  //Test to see if the radio device is connected properly and has started
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // If not, hold in infinite loop
  }
  //Assign an address to the receiver. MUST MATCH THE TOWER(receiver)
  radio.openWritingPipe(0xDEADBEEF);  

  //Make sure this device is not listening for broacastes
  radio.stopListening();

  //Set the power of the transmitter
  //Settings too high will not work in close prox. to the receiver
  radio.setPALevel(RF24_PA_LOW);

  //Declare end of startup over serial
  Serial.println("Radio Started");
}

void loop() {
  //Send the payload, and verify that it was sent
  if (radio.writeFast(&payload, sizeof(payload))) {
    Serial.print(payload);
    Serial.println(" Payload Successfully Sent");
} else { //If transmission was not successful..
    Serial.println("Payload Send failed");
}

  //temporary delay for debug purposes
  delay(1000);
}
