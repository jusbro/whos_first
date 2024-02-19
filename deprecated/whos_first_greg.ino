
//Initialize variables for all input pins used
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int button5Pin = 6;
const int button6Pin = 7;
const int resetPin = 8;

//Initialize variables for all output pins used
const int led1Pin = 14;
const int led2Pin = 15;
const int led3Pin = 16;
const int led4Pin = 17;
const int led5Pin = 18;
const int led6Pin = 19;

//Initialize variables for all states
int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int button6State = 0;
int resetState = 0;

//Initialize variables for all boolean operators
bool firstPushed = false;
bool secondPushed = false;
bool button1Pushed = false;
bool button2Pushed = false;
bool button3Pushed = false;
bool button4Pushed = false;
bool button5Pushed = false;
bool button6Pushed = false;


void setup() {
  Serial.begin(9600); //Start serial for debugging

//Set all output pin modes
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);

//Set all input pin modes (NOTE:  Currently set to use internal pullup resistor - for changing to external pulldown (or another system) change these to "INPUT" and all occurances of digitalRead() LOW to HIGH and vice versa)
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);

//Check if any buttons are pressed at startup (useful for toggle switches).  If switches are on, their corresponding lights will light until each has been turned off.
  while(digitalRead(button1Pin) == LOW || digitalRead(button2Pin) == LOW || digitalRead(button3Pin) == LOW || digitalRead(button4Pin) == LOW){
    if(digitalRead(button1Pin) == LOW){
      digitalWrite(led1Pin, HIGH);
    }else if (digitalRead(button2Pin) == LOW){
      digitalWrite(led2Pin, HIGH);
    }else if (digitalRead(button3Pin) == LOW){
      digitalWrite(led3Pin, HIGH);
    }else if (digitalRead(button4Pin) == LOW){
      digitalWrite(led4Pin, HIGH);
    }
  }

  //Turn off all LEDs when all buttons are off.
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  digitalWrite(led4Pin, LOW);

}

void loop() {
  //Set all states to the corresponding input from digitalRead()
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  button4State = digitalRead(button4Pin);
  resetState = digitalRead(resetPin);


  if (button1State == LOW && button1Pushed == false) { //If the first button is pressed AND hasn't been pressed before, do stuff (this prevents repeat presses - essentially a brute force debounce)

    if (firstPushed == false) {  //If this is the first button that has bee pressed, turn on the corresponding LED steady and set the appropriate variables.  All buttons work this way.
      digitalWrite(led1Pin, HIGH);
      firstPushed = true;
      button1Pushed = true;
    } else if (secondPushed == false) {// If this is the second button pressed, enter a loop to flash it until the reset button is pressed.
      secondPushed = true;
      button1Pushed = true;
      while (resetState == HIGH) {
        digitalWrite(led1Pin, HIGH);
        delay(500);
        digitalWrite(led1Pin, LOW);
        delay(500);
        resetState = digitalRead(resetPin); //Check at the end of each loop if the reset button is pressed.

      }
    }

  } else if (button2State == LOW && button2Pushed == false) {
    
    if (firstPushed == false) {
      digitalWrite(led2Pin, HIGH);
      firstPushed = true;
      button2Pushed = true;
    } else if (secondPushed == false) {
      secondPushed = true;
      button2Pushed = true;
      while (resetState == HIGH) {
        digitalWrite(led2Pin, HIGH);
        delay(500);
        digitalWrite(led2Pin, LOW);
        delay(500);
        resetState = digitalRead(resetPin);        
      }
    }
  } else if (button3State == LOW && button3Pushed == false) {
    
    if (firstPushed == false) {
      digitalWrite(led3Pin, HIGH);
      firstPushed = true;
      button3Pushed = true;
    } else if (secondPushed == false) {
      secondPushed = true;
      button3Pushed = true;
      while (resetState == HIGH) {
        digitalWrite(led3Pin, HIGH);
        delay(500);
        digitalWrite(led3Pin, LOW);
        delay(500);
        resetState = digitalRead(resetPin);

      }
    }
  } else if (button4State == LOW && button4Pushed == false) {
    
    if (firstPushed == false) {
      digitalWrite(led4Pin, HIGH);
      firstPushed = true;
      button4Pushed = true;
    } else if (secondPushed == false) {
      secondPushed = true;
      button4Pushed = true;
      while (resetState == HIGH) {
        digitalWrite(led4Pin, HIGH);
        delay(500);
        digitalWrite(led4Pin, LOW);
        delay(500);
        resetState = digitalRead(resetPin);
      }
    }
  } else if (resetState == LOW) { //If reset button is pressed, turn all LEDs off and reset all variables to default.
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
    firstPushed = false;
    secondPushed = false;
    button1Pushed = false;
    button2Pushed = false;
    button3Pushed = false;
    button4Pushed = false;
  }
}
