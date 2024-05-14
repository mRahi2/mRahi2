//Minahil Rahimullah, 660853122, mRahi2
//Lab 6: LCD Screen and Time Display
//Description: Program will take in user input of a certain format and print out a clock that starts at the inputted date and time.
//Assumptions: Expected all wires and parts to work, expected the Lcd to work as needed and expected the wiring to not break during testing.
//Refrences: Lab Slides/links + help from Ta's. 
//TA name: Misra, Anshuman 2/28/2024 2:30 pm.  


#include <LiquidCrystal.h>
#include <TimeLib.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char start[] = "Enter a date and time "; // Starting message
char format [] = "mm/dd/yyyy hh:mm:ss    "; // format of the userInput
char restart[] = "Invalid, please enter a date and time "; // error message
int validTime = 0; 
int rePrompt = 0;
int i = 0; // counter for when quote should restart


void setup() {
  
  lcd.begin(16, 2);// set up the LCD's number of columns and rows

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.println("Enter a date and time");

}

void loop() {
  lcd.clear(); // clears for the new values
  if (validTime == 0 && rePrompt == 0){    //print out the starting message
    setTime(12, 45, 30, 10, 5, 2000);
    lcd.setCursor(0, 0);
    lcd.print("Date: " + String(month()) + "/" + day() + "/" + year() + "   "); // prints date

    lcd.setCursor(0, 1);
    lcd.print("Time: " + String(hour()) + ":" + minute() + ":" + second() + "   "); // prints time
    
  } else if ((validTime == 0)&& (rePrompt == 1)){  //prints out the error message if wrong
    Serial.println("Invalid, please enter a date and time ");
  } else{     // valid time and date
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Date: " + String(month()) + "/" + day() + "/" + year() + "   "); // prints date

    lcd.setCursor(0, 1);
    lcd.print("Time: " + String(hour()) + ":" + minute() + ":" + second() + "   "); // prints time
    Serial.println("The date and time updated successfully");
  }

  if (Serial.available() > 0){
    int month, day, year, hour, minute, second;
    char userInput[20];
    i = 0;

    int inputLength = Serial.readBytesUntil('\n', userInput, sizeof(userInput));
    userInput[inputLength] = '\0';
    
    sscanf(userInput, "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second); // stpres values into the variables

    rePrompt = 1;
    validTime = 0;

    if (month <= 12 && day <= 31 && hour <= 23 && minute <= 59 && second <= 59){ //check if all the values entered are valid
      if ((year%4 == 0) && (year%100 != 0 || year%400 == 0)){ // check if its a leap year

        if ((month == 2) && day <= 29){ // include 29 due to leap year
          validTime = 1;
        } else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day <= 30)){ // check if a 30 day month
          validTime = 1;
        } else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day <= 31)){ 
          validTime = 1;

        }
        
      } else{
        if ((month == 2) && (day <= 28)){ //if not leap year, then days needs to be less than or equal to 28
          validTime = 1;
        } else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day <= 30)){ // checks if a 30 day month
          validTime = 1;
        } else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day <= 31)){
          validTime = 1;
        }
      }

      if (validTime == 1){ // if passed one of the cases, it's a valid time
        rePrompt = 0;
        setTime(hour, minute, second, day, month, year); // set the time  
      }
    }
  }
}
