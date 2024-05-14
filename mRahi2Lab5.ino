//Minahil Rahimullah, 660853122, mRahi2
//Lab 05 - Multiple Inputs and Outputs
//Description: Based on light input, the LEDs are going to light up to darkest/more LED. At ther same time, the buzzer will play sound in intervals based on the potentialmetor output. 
//Assumptions: Asssumed that all peices do theri job, all wiring is working, and I Assumed that the values of the potentiometer. 
//Refrences: Lab Slides/links + help from Ta's. 
//TA name: tanuj 2/19/2024 3:25 pm.

int photoresistor = A0;
int potentialMeter = A1;
int readphoto = 0;
int readpotential = 0;
int led1 = 11;
int led2 = 10;
int led3 = 9;
int led4 = 8;
int speaker = 6;
unsigned long previousMillis = 0;

void setup() {
  //tells arduino what pins are for what LED/component
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  pinMode(speaker,OUTPUT);

  Serial.begin(9600);

}

void loop() {

  readphoto = analogRead(photoresistor); //reads in input from photoresistor and is used to deteremine LED output
  readpotential = analogRead(potentialMeter); //reads input from potentialmeter and is used to determine the lenght of sounds output
  
  if (readphoto <= 50) { //Dark setting

    digitalWrite(led1,LOW);  //Turns off
    digitalWrite(led2,LOW);  //Turns off
    digitalWrite(led3,LOW);  //Turns off
    digitalWrite(led4,LOW);  //Turns off

  } else if (readphoto <= 200) { //partically dark setting
    
    digitalWrite(led1,HIGH); //Turns on
    digitalWrite(led2,LOW);  //Turns off
    digitalWrite(led3,LOW);  //Turns off
    digitalWrite(led4,LOW);  //Turns off

  } else if (readphoto <= 500) { //Medium setting

    digitalWrite(led1,HIGH); //Turns on
    digitalWrite(led2,HIGH); //Turns on
    digitalWrite(led3,LOW);  //Turns off
    digitalWrite(led4,LOW);  //Turns off

  } else if (readphoto <= 800) { //Fully lit setting

    digitalWrite(led1,HIGH); //Turns on
    digitalWrite(led2,HIGH); //Turns on
    digitalWrite(led3,HIGH); //Turns on
    digitalWrite(led4,LOW);  //Turns off    

  } else { //Brightly lit setting

    digitalWrite(led1,HIGH); //Turns on
    digitalWrite(led2,HIGH); //Turns on
    digitalWrite(led3,HIGH); //Turns on
    digitalWrite(led4,HIGH); //Turns on
  }

  unsigned long currentMillis = millis();

  if (readpotential <= 146) {
    
    noTone(speaker); // Do not produce any tone
  } 
  else if (readpotential <= 300 && readpotential > 146) {
    if (currentMillis - previousMillis >= 9000) { // Time between tones: 8 seconds
      previousMillis = currentMillis; 
      tone(speaker, 392, 1000);
      //noTone(speaker);
    }
  } 
  else if (readpotential <= 450 && readpotential > 300) {
    if (currentMillis - previousMillis >= 5000) { // Time between tones: 4 seconds
      previousMillis = currentMillis; 
      tone(speaker, 392, 1000);
      //noTone(speaker);
    }
  } 
  else if (readpotential <= 600 && readpotential > 450) {
    if (currentMillis - previousMillis >= 3000) { // Time between tones: 2 seconds
      previousMillis = currentMillis; 
      tone(speaker, 392, 1000);
      //noTone(speaker);
    }
  } else if (readpotential <= 750 && readpotential > 600) {
    if (currentMillis - previousMillis >= 2000) { // Time between tones: 1 second
      previousMillis = currentMillis; 
      tone(speaker, 392, 1000);
      //noTone(speaker);
    }
  } else if (readpotential <= 890 && readpotential > 750) {
    if (currentMillis - previousMillis >= 1500) { // Time between tones: 0.5 seconds
      previousMillis = currentMillis; 
      tone(speaker, 392, 1000);
      //noTone(speaker);
    }
  }

  Serial.println(readpotential);
}
  