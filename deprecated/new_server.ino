
/*
SERVER-SIDE WIRELESS RECEIVER

This code runs in the "whose first" tower. It will eventually be merged with the code controlling the lights on the device
It runs a loop and "listens" for data from any of the six external remotes. Remotes should broadcast a unique character to identify them
In the future, the remotes may also broadcast an "opposite" character indicating the remote has been turned off. This will allow the remotes to "reset" the whose first tower

TO DO LIST:
DONE 1) Add LED verifing correct reception of a remote ID
2) Add code to accept all six remotes
3) Determine a method of resetting tower
4) Merge code with code controlling LEDs in whose first tower
5) Develop and build PCB for whose first tower
6) Verify accuracy of reception
*/


#include <SPI.h>
#include <RF24.h>

//Arduino Uno CE 8, CSN 10
//Arduino Nano CE 7, CSN 8
#define CE_PIN 8
#define CSN_PIN 10

//Create radio object using pins above
RF24 radio(CE_PIN, CSN_PIN);

//Create the payload and set it to a size
char receivedPayload[32];  

//Create two LEDs used to debug
const int ledPin = 4;
const int readyLEDPin = 13;

void setup() {
  //Start Serial for debug purposes. This can be removed in final product
  Serial.begin(9600);

  //Assign the LEDs as an output
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //Test to see if the radio device is connected properly and has started
  if (!radio.begin()) {
    Serial.println(F("Radio hardware is not responding!!"));
    while (1) {}  // If not, hold in infinite loop
  }

  //Assign an address to the receiver. MUST MATCH THE REMOTES
  radio.openReadingPipe(1, 0xDEADBEEF);  

  //Start listening for transmissions
  radio.startListening();

  //Declare end of startup over Serial
  Serial.println(F("Radio Receiver Started"));
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
}

void loop() {
  //If a transmission is received, the following statement is run
  if (radio.available()) {
    radio.read(&receivedPayload, sizeof(receivedPayload));
    Serial.print(F("Received Payload: "));
    String remote = String(receivedPayload);
    Serial.println(receivedPayload);
    if(remote == "A"){
      Serial.println("Turning on 'A' LED");
      digitalWrite(ledPin, HIGH);
    } 

  }
  
  //Temporary delay to debug more easily. Will be minimized in final code 
  delay(1000);  
}
