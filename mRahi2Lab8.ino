//Minahil Rahimullah, 660853122, mRahi2
//Lab 08 - Scrolling Output
//Description: Program will print a starting message on the lcd that tells the user how many seconds have passed since start-up. If button one is pressed, and interupt erro will pop up. If button two is pressed the timer will reset and the starting screen will come back up.
//Assumptions: Expected all wires and parts to work, expected the Lcd to work as needed and expected the wiring to not break during testing.
//Refrences: Lab Slides/links + help from Ta's. 
//TA name: Tala Shraim 3/15/2024 5:31 pm.
#include <LiquidCrystal.h>

// Initialize the LCD
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// Define button pins
const int buttonPinOne = 3;
const int buttonPinTwo = 2;

// Global variables
volatile bool interruptReceived = false;
unsigned long runningTime = 0;
unsigned long inturuptTime = 0;
int scrollIndexLine1 = 0; // Variable to track the index of scrolling for line 1
int scrollIndexLine2 = 0; // Variable to track the index of scrolling for line 2
int prev = 0; // keeps track if user is returning from inturupt or not

// Define initial messages for scrolling
String scrollTextLine1 = "Interrupt received!       ";
String scrollTextLine2 = "Press button2 to continue ";

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Set button pins as input and enable pull-up resistors
  pinMode(buttonPinOne, INPUT_PULLUP);
  pinMode(buttonPinTwo, INPUT_PULLUP);

  // Attach interrupt functions to the buttons
  attachInterrupt(digitalPinToInterrupt(buttonPinOne), buttonOneInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPinTwo), buttonTwoInterrupt, FALLING);

  // Initialize the LCD with the initial message
  lcd.setCursor(0, 0);
  lcd.print("System has been");
  lcd.setCursor(0, 1);
  lcd.print("running for 0s");

  Serial.begin(9600);  
}

// Button 1 ISR
void buttonOneInterrupt() {
  interruptReceived = true;
  inturuptTime = millis(); // Record the time of interrupt
  prev = 1;
}

// Button 2 ISR
void buttonTwoInterrupt() {
  if (interruptReceived) {
    interruptReceived = false;
    // Reset the timer
    runningTime = 0;
  }
}

void loop() {
  if (!interruptReceived) {
    unsigned long currentTime = millis();
    runningTime = currentTime - inturuptTime; // Calculate elapsed time since interrupt
    if (currentTime - runningTime >= 1000) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("System has been");
      lcd.setCursor(0, 1);
      lcd.print("running for ");
      lcd.print(runningTime / 1000);
      lcd.print("s");
    }
  }

  if (interruptReceived) {
    lcd.setCursor(0, 0);
    lcd.print(scrollTextLine1.substring(scrollIndexLine1, scrollIndexLine1 + 16));
    scrollIndexLine1++;
    if (scrollIndexLine1 >= scrollTextLine1.length()) {
      scrollIndexLine1 = 0;
    }
    
    lcd.setCursor(0, 1);
    lcd.print(scrollTextLine2.substring(scrollIndexLine2, scrollIndexLine2 + 16));
    scrollIndexLine2++;
    if (scrollIndexLine2 >= scrollTextLine2.length()) {
      scrollIndexLine2 = 0;
    }

    delay(500);
    
    runningTime = 0;
    prev = 1;
  }
}
