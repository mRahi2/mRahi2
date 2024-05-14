//Minahil Rahimullah, 660853122, mRahi2
//Lab 02 - Input and Output
//Description: Program will display binary values form 0-7 with LEDs, inclues two switch buttons for inc and dec.
//Assumptions: Expected all wires and parts to work, expected the switches to not move around and expected the buttons to stablize after 10 ms. 
//Refrences: Lab Slides/links
//TA name: Misra, Anshuman, Online office hours 3:55 pm. 

int buttonINC = 3; //increasing button
int buttonDEC = 2; //decreasing button
int firstLED = 10; //first digit
int secondLED = 11; //second digit
int thirdLED = 12; //third digit

int count = 0; //keeps track of the 0-7
int currentButtonStateINC = 0; //when clicked
int stableButtonStateINC = 0; // after 10 ms 
int currentButtonStateDEC = 0; // when clicked 
int stableButtonStateDEC = 0; // after 10 ms
int buttonStateI = 0; //last button state from before the click
int buttonStateD = 0; //last button state from before the click

void setup() {
  pinMode(buttonINC,INPUT);
  pinMode(buttonDEC, INPUT);
  pinMode(firstLED, OUTPUT);
  pinMode(secondLED, OUTPUT);
  pinMode(thirdLED, OUTPUT);
}

//finds the binary three digit value from the inntegter passed through, and returns it as a string for easy checking
String toBinaryString(int value) {
    String stringB = "";
    for (int i = 2; i >= 0; i--) {
      int bit = (value >> i) & 1;
      stringB += String(bit);
    }
    return stringB;
}

//Sees which LEDS to turn on based on the string passed through
void setLEDs(String binaryStr) {
    digitalWrite(firstLED, binaryStr[0] == '1' ? HIGH : LOW);
    digitalWrite(secondLED, binaryStr[1] == '1' ? HIGH : LOW);
    digitalWrite(thirdLED, binaryStr[2] == '1' ? HIGH : LOW);
}

void loop() {
  currentButtonStateINC = digitalRead(buttonINC); // read the current state of the increment button
  currentButtonStateDEC = digitalRead(buttonDEC); // read the current state of the decrement button

  delay(10); // debounce delay

  stableButtonStateINC = digitalRead(buttonINC); // read the state again for debounce
  stableButtonStateDEC = digitalRead(buttonDEC);

  // Check if the button states are stable (debounced)
  if (currentButtonStateINC == stableButtonStateINC) {
    if (currentButtonStateINC != buttonStateI) {
      if (currentButtonStateINC == HIGH && count < 7) {
        count++;
      }
    }
  }

  buttonStateI = currentButtonStateINC;

  if (currentButtonStateDEC == stableButtonStateDEC) {
    if (currentButtonStateDEC != buttonStateD) { 
      if (currentButtonStateDEC == HIGH && count > 0) {
        count--;
      }
    }
  }

  buttonStateD = currentButtonStateDEC;

  //chages the LEDS based on the value of count
  String binaryStr = toBinaryString(count);
  setLEDs(binaryStr);
}