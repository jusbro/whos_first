#include <SPI.h>
#include "RF24.h"
#include <Bounce2.h>

// Arduino Uno CE 8, CSN 10
// Arduino Nano CE 7, CSN 8
#define CE_PIN 7
#define CSN_PIN 8

// Instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);
//Bounce debouncer = Bounce();

// Create this remote's unique ID.
// This is temporarily A, B, C, etc. but may be changed to any character in the future
// May also create a "neg_payload" ID in the future that sends an "off" command to the whose first tower
char payload[] = "A";
char neg_payload[] = "A";

int buttonPin = 2;
int buttonState = 0;

// A variable used to only send the transmission once per button press
// Goes 1 when the message is sent, goes 0 when the button is low
int messageState = 0;

int prevButtonState = HIGH;  // Variable to store the previous button state

void setup() {
  // Start Serial for debug purposes. This can be removed in the final product
  Serial.begin(9600);
  
  // Set up the debouncer with a debounce time of 50ms
  //debouncer.attach(buttonPin, INPUT_PULLUP);
  //debouncer.interval(50);

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
  // Update the debouncer
  //debouncer.update();

  // Get the updated button state
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && prevButtonState == HIGH) {
    if (messageState == 1) {
      Serial.print("Button Pressed ");
      if (radio.write(&payload, sizeof(payload))) {
        Serial.print(payload);
        Serial.println(" Successfully Sent");
        delay(200);  // Add a longer delay after a successful transmission
      } else { // If transmission was not successful..
        Serial.println("Payload Send failed");
      }
      messageState = 0;
    }
  } else if (buttonState == HIGH && prevButtonState == LOW) {
    messageState = 1;
    Serial.print("Button Depressed ");
    if (radio.write(&neg_payload, sizeof(neg_payload))) {
      Serial.print(neg_payload);
      Serial.println(" Successfully Sent");
      delay(200);  // Add a longer delay after a successful transmission
    } else { // If transmission was not successful..
      Serial.println("Payload Send failed");
    }
  }

  // Update the previous button state
  prevButtonState = buttonState;

  // Temporary delay for debug purposes
  delay(100);
}
