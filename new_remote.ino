
#include <SPI.h>
#include "RF24.h"

#define CE_PIN 7
#define CSN_PIN 8
#define SIZE 32             // this is the maximum for this example. (minimum is 1)

RF24 radio(CE_PIN, CSN_PIN);

void setup() {
  Serial.begin(115200);
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} 
  }
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.stopListening();  // put radio in TX mode
} 

void loop() {
  Serial.println("Transmitting A");
  radio.writeFast("A", SIZE);
  delay(100);  // slow transmissions down by 1 second
  Serial.println("Transmitting B");
  radio.writeFast("B", SIZE);
  delay(100);
  

} 

