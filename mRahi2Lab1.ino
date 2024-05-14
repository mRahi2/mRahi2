//Minahil Rahimullah, 660853122, mRahi2
//Lab 01 - Three Blinking Lights
//Description: Program will allow three lights to go of in intervals of one second in order of board, red LED, and green LED, looping infinitly. 
//Assumptions: Expected all wires and parts to work, Expected the program to fully take care of the on board light as it is assigned to pin 13.
//Refrences: Circuit Basics Diagram
//TA name: Kaz, 1/22/2023 11:00 am.

int pinBoard = 13;
int pinRed = 12;
int pinGreen = 11;
unsigned long prev = 0;
int interval = 1000;
int on = 0;

void setup() {

  pinMode(pinBoard, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);

}

void loop() {
  unsigned long curr = millis();
  if (curr - prev >= interval) {
   prev = curr;
   if(on == 0) {
     on = 1;
     digitalWrite(pinGreen, LOW); //If the Green is on before board, turn it off
     digitalWrite(pinBoard, HIGH); //Turns on board light 
   } else if (on == 1) {
     on = 2;
     digitalWrite(pinBoard, LOW);//Turns off board light
     digitalWrite(pinRed, HIGH); //Turns on Red LED
   } else {
     on = 0;
     digitalWrite(pinRed, LOW); //Turns off red LED
     digitalWrite(pinGreen, HIGH); //Turns on Green LED
   }
}
}
