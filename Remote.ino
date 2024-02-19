/*Arduino Nano Every Remote Control for Who's First Device
This software is designed to run on a Nano Every. Its purpose is to act as a remote (one of up to six) that students use to buzz in on a Who's First device
This software can be used and has been tested on Arduino Nano Every and Arduino Uno REV3

Version 0.91
Last updated 2/19/2024
*/

//IMPORTS
#include <SPI.h>
#include "RF24.h"
#include <Bounce2.h>

//Declare the Chip Enable (CE) and Chip Select (CSN) pins
// Arduino Uno CE 8, CSN 10
// Arduino Nano CE 7, CSN 8
#define CE_PIN 7
#define CSN_PIN 8

// Instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

/*Create this remote's unique ID.
This is temporarily A, B, C, etc. but may be changed to any character in the future
May also create a "neg_payload" ID in the future that sends an "off" command to the whose first tower
The following convention will be used:
Pink = A / G
Green = B / H
Yellow = C / I
Orange = D / J
Blue = E / K
Red = F / L
*/

//This remote's unique ID as defined above
char payload[] = "A";

//This remote's unique neg_payload (If Using One)
//char neg_payload[] = "";

//Create a button and a button tracking state
int buttonPin = 2;
int buttonState = 0;

// A variable used to only send the transmission once per button press
// Goes 1 when the message is sent, goes 0 when the button is low
int messageState = 0;

int prevButtonState = HIGH;  // Variable to store the previous button state

void setup() {
  // Start Serial for debug purposes. This can be removed in the final product
  Serial.begin(9600);
  
  // Test to see if the radio device is connected properly and has started
  if (!radio.begin()) {
    Serial.println(F("Radio hardware is not responding!!"));
    while (1) {}  // If not, hold in an infinite loop
  }

  // Assign an address to the receiver. MUST MATCH THE TOWER(receiver)
  radio.openWritingPipe(0x12341234);

  // Make sure this device is not listening for broadcasts
  radio.stopListening();

  // Set the power of the transmitter
  // Settings too high will not work in close proximity to the receiver
  radio.setPALevel(RF24_PA_MAX);

  // Declare the end of startup over serial
  Serial.println("Radio Started");
}

void loop() {

  // Get the updated button state
  int buttonState = digitalRead(buttonPin);

  // If the button were pressed, send the payload ID
  if (buttonState == LOW && prevButtonState == HIGH) {
    if (messageState == 1) {
      Serial.print("Button Pressed ");
      if (radio.write(&payload, sizeof(payload))) {
        Serial.print(payload);
        Serial.println(" Successfully Sent");
        delay(200);  // Add a delay after a successful transmission
      } else { // If transmission was not successful..
        Serial.println("Payload Send failed");
      }
      messageState = 0;
    }
  } else if (buttonState == HIGH && prevButtonState == LOW) {
    messageState = 1;
    Serial.print("Button Depressed ");
    if (radio.write(&neg_payload, sizeof(neg_payload))) {
      Serial.print(payload);
      Serial.println(" Successfully Sent");
      delay(200);  // Add a delay after a successful transmission
    } else { // If transmission was not successful..
      Serial.println("Payload Send failed");
    }
  }

  // Update the previous button state
  prevButtonState = buttonState;

  // Temporary delay for debug purposes
  delay(100);
}
