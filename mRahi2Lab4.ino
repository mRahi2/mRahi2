//Minahil Rahimullah, 660853122, mRahi2
//Lab 04 - Analog Inout
//Description: Lab will detect and project on the display the amount of light shined on the photo-resistor, with atimer present that resets after every change in the display
//Assumptions: Expected all wires and parts to work, expected the Lcd to work as needed and expected the wiring to not break during testing.
//Refrences: Lab Slides/links + help from Ta's. 
//TA name: Anshauman Misra 3 pm

#include <LiquidCrystal.h>

// Initialize the library with the pins used
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String newLight = "";
String oldLight = "";
unsigned long lightChangeMillis = 0; // Stores the new millis() when the light value changes on lcd
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 1000;  // interval at which to blink (milliseconds)

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    // reads the input on pin A0
    int lightValue = analogRead(A0);

    // Use the value from the photoresistors to determine the word on lcd
    if (lightValue < 50) {
      newLight = "Dark";
    } else if (lightValue < 200) {
      newLight = "Partially dark";
    } else if (lightValue < 500) {
      newLight = "Medium";
    } else if (lightValue < 800) {
      newLight = "Fully lit";
    } else {
      newLight = "Brightly lit";
    }

    // Update the light level description only if it has changed
    if (newLight != oldLight) {
      lcd.clear(); // Clear the LCD screen so the old phrase is not there
      lcd.setCursor(0, 0); //set where the phrase will appear
      lcd.print(newLight);
      oldLight = newLight; // Update to the new value
    }

    // Calculate the time since the light description was last updated
    unsigned long elapsed = (millis() - lightChangeMillis) / 1000;

    // Display the time
    lcd.setCursor(0, 1);
    lcd.print(elapsed);
    lcd.print("            "); // Clear any remaining characters from previous number
  }
}
