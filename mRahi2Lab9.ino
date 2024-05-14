//Minahil Rahimullah, 660853122, mRahi2
//Lab 09 - LED RGB
//Description: Based on the x and y value of our two axis joycon and potientiometer, we will output the values on the red blue and green leds. These will also influmece the rgb led. 
//Assumptions: Asssumed that all peices do their job, all wiring is working, and I assumed that the values of the potentiometer. 
//Refrences: Lab Slides/links + help from Ta's. 
//TA name: Misra, Anshuman 3:00 pm.

//global variables
int potPin = A0; // Pin A0 for potientiometer (Blue value)
int xPin = A1; // Pin A1 for X-axis of joystick (Red value)
int yPin = A2; // Pin A2 for Y-axis of joystick (Green value)
int redLED = 6; // PWM pin for Red LED 
int greenLED = 5; // PWM pin for Green LED 
int blueLED = 3; // PWM pin for Blue LED

void setup() {
  // Set LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  //Set up the input for the rgb LED
  pinMode(11, OUTPUT); // red LED in RGB bulb
  pinMode(10, OUTPUT); // green LED in RGB bulb
  pinMode(9, OUTPUT); // blue LED in RGB bulb
}

void loop() {
  static unsigned long prevMillis = 0; //holds the starting time to keep track of how much time has pass
  unsigned long currMillis = millis();

  if (currMillis - prevMillis >= 10) { //checks if 10 milliseconds has passed
    // Correctly read inputs
    int xVal = analogRead(xPin); // Read X-axis
    int yVal = analogRead(yPin); // Read Y-axis
    int potValue = analogRead(potPin); // Read potentiometer

    // Map 0-1023 to 0-255
    int redValue = map(xVal, 0, 1023, 0, 255);
    int greenValue = map(yVal, 0, 1023, 0, 255);
    int blueValue = map(potValue, 0, 1023, 0, 255);

    // Write mapped values to LEDs
    analogWrite(redLED, redValue);
    analogWrite(greenLED, greenValue);
    analogWrite(blueLED, blueValue);

    analogWrite(11, redValue);
    analogWrite(10, greenValue);
    analogWrite(9, blueValue);

    // Update timing
    previousMillis = currentMillis;
  }
}
