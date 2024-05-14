//Minahil Rahimullah, 660853122, mRahi2
//Lab 07 - Communication between arduino
//Description: Two ardunio communicate together, telling each other when the others button is pressed and lighting their LED accordingly. 
//Assumptions: Expected all wires and parts to work, expected the switches to not move around and expected the buttons to stablize after 10 ms. 
//Refrences: Lab Slides/links
//TA name: Shraim, Tala, Friday 9:00 a.m. 3/8/2024 

const int buttonPin = 10; // Pin for the button
const int ledPin = 7;     // Pin for the LED
char status;
 
// checks for switch press and if pressed fully
int buttonState;
int buttonNewUp;
int buttonNewUp2; 
int buttonOldUp = 1; 

// holds the state of the led and represents if off or on. Starts as off
int ledOne = 0; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // input for read button
  pinMode(ledPin, OUTPUT);         // output for LED
  Serial.begin(9600);            // for communication
}
 
void loop() {
  // for sending messages 
  buttonNewUp = digitalRead(buttonPin); // Brooklyn Debounce code implementation
  delay(20);
  buttonNewUp2 = digitalRead(buttonPin);
  if (buttonNewUp == buttonNewUp2){
    if (buttonNewUp != buttonOldUp){
      if (buttonOldUp == 0 && buttonNewUp == 1){
        Serial.write('1');
      }
    }

    buttonOldUp = buttonNewUp;
  }

  delay(20); // waiting message send

  // for receiving messages
  if(Serial.available()) //if there is a message sent
  {
    status = Serial.read();
    if(status == '1' && ledOne == 0) //if LED off, then turn on
    {
      digitalWrite(ledPin, HIGH);
      ledOne = 1; 
    }
    else if(status == '1' && ledOne == 1)  // if LED on, then turn off
    {
      digitalWrite(ledPin, LOW);
      ledOne = 0;
    }
  }
}


 
