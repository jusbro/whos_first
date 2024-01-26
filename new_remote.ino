#include <SPI.h>
#include "RF24.h"
#include <Bounce2.h>

// Arduino Uno CE 8, CSN 10
// Arduino Nano CE 7, CSN 8
#define CE_PIN 7
#define CSN_PIN 8

// Instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);
Bounce debouncer = Bounce();

// Create this remote's unique ID.
// This is temporarily A, B, C, etc. but may be changed to any character in the future
// May also create an "anti-character" ID in the future that sends an "off" command to the whose first tower
char payload[] = "A";

int buttonPin = 2;
int buttonState = 0;

// A variable used to only send the transmission once per button press
// Goes 1 when message sent, goes 0 when the button is low
int messageState = 0;

void setup() {
  // Start Serial for debug purposes. This can be removed in the final product
  Serial.begin(9600);
  
  // Set up the debouncer with a debounce time of 50ms
  debouncer.attach(buttonPin, INPUT_PULLUP);
  debouncer.interval(50);

  // Test to see if the radio device is connected properly and has started
  if (!radio.begin()) {
    Serial.println(F("Radio hardware is not responding!!"));
    while (1) {}  // If not, hold in an infinite loop
  }

  // Assign an address to the receiver. MUST MATCH THE TOWER(receiver)
  radio.openWritingPipe(0xDEADBEEF);

  // Make sure this device is not listening for broadcasts
  radio.stopListening();

  // Set the power of the transmitter
  // Settings too high will not work in close proximity to the receiver
  radio.setPALevel(RF24_PA_LOW);

  // Declare the end of startup over serial
  Serial.println("Radio Started");
}

void loop() {
  // Update the debouncer
  debouncer.update();

  // Get the updated button state
  int buttonState = debouncer.read();

  if (buttonState == LOW) {
    if (messageState == 1) {
      Serial.print("Button Pressed");
      if (radio.writeFast(&payload, sizeof(payload))) {
        Serial.print(payload);
        Serial.println(" Payload Successfully Sent");
      } else { // If transmission was not successful..
        Serial.println("Payload Send failed");
      }
      messageState = 0;
    }
  } else {
    messageState = 1;
  }

  // Temporary delay for debug purposes
  delay(100);
}
