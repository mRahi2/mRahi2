//Minahil Rahimullah, 660853122, mRahi2
//Lab 03 - Scrolling Output
//Description: Program will have a infinatly scrolling message at the top of the lcd, and a stationary label of the participants name at the bottom
//Assumptions: Expected all wires and parts to work, expected the Lcd to work as needed and expected the wiring to not break during testing.
//Refrences: Lab Slides/links + help from Ta's. 
//TA name: Seyri, AmirHossein, Online office hours 11:50 pm. 

#include <LiquidCrystal.h>

// initialize the library with assicating the pins
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String firstText = "Ponte las Pilas, Omar!                "; // Scrolling text, extra spaces for smooth scrolling off-screen
String secondText = "Minahil"; // stationary text
int position = 0; 

void setup() {
  // Set up the LCD's number of columns and rows (16 X 2):
  lcd.begin(16, 2);
  
  // Center text on the second row
  lcd.setCursor(4, 1);
  lcd.print(secondText);
}

void loop() {
  //set the etxt at the frist col/row of the lcd
  lcd.setCursor(0, 0);
  // Scroll the first row text
  for (int i = 0; i < 16; i++) {
    int newPos = (i + position) % firstText.length(); // find new position of the desired char
    lcd.print(firstText[newPos]); // Print the char for scrolling effect
  }
  position = (position + 1) % firstText.length(); // update postion to keep the scrolling affect
  delay(300); // Adjust scrolling speed for easy readability
}