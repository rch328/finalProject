//Motor test using the h-bridge

const int switchPin = 2;    // switch input
const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int m1 = 5;
const int m2=6;

//const int enablePin = 9;    // H-bridge enable pin

void setup() {
    // set the switch as an input:
    //pinMode(switchPin, INPUT); 
 
    // set all the other pins you're using as outputs:
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    //pinMode(enablePin, OUTPUT);
 
    // set enablePin 175 so that motor can turn on:
    //analogWrite(enablePin, 175);
  }

void loop() {
    // if the switch is 175, motor will turn on one direction:
      analogWrite(motor1Pin, 0);   // set leg 1 of the H-bridge 0
      analogWrite(motor2Pin, 175);  // set leg 2 of the H-bridge 175

      analogWrite(m1, 0);
      analogWrite(m2,175);

   delay(1750);
      analogWrite(motor1Pin, 175);  // set leg 1 of the H-bridge 175
      analogWrite(motor2Pin, 0);   // set leg 2 of the H-bridge 0
      analogWrite(m1, 175);
      analogWrite(m2, 0);
      delay(1750);
  }
  
