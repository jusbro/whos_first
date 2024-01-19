/*
This program runs on the six remotes.
The remotes are designed with a button. When that button is pressed, the remote's number is broadcast for the main server to pick up
*/

//The following line of code needs to be adjust for each remote that is programmed because each remote needs a unique number (1 to 6)

#define remote_ID 1

#include <SPI.h>

//This library is part of "RadioHead" by Mike McCauley
#include <RH_NRF24.h>

// Create the radio object
RH_NRF24 nrf24;

//attach the remote's button to pin 2
const int buttonPin = 2;

//set the button to a default state of 0
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  //The following conditions were found through tutorials. I have not yet played with options within them
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop(){
  //read the state of the button
  buttonState = digitalRead(buttonPin);
  //if the button is pressed, process and send the remote's ID
  if (buttonState == HIGH){

    Serial.println("Sending remote ID to server");
    // Send a message to nrf24_server
    uint8_t data[] = "1";
    nrf24.send(data, sizeof(data));
    nrf24.waitPacketSent();
  }
  nrf24.waitPacketSent();
  delay(10);
}
