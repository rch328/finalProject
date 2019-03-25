/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

//We can use the width to calculate how fast the motors have to turn
int width;
int leftMotors = 8;
int rightMotors = 9;
//This is a global variable, delete later
int movespeed = 50;
//Magicalconstant is when I figure out the math for the turning arc for the wheels
//It will be something like radius of turn plus the width of the robot between 
int magicalconstant = 1.25;
//This is whatever equation i think that we convert to linear velocity I think
int turnvelocity = movespeed * magicalconstant;

/*
int frontLeftMotor = 6;
int frontRightMotor = 7;
int rearLeftMotor = 8;
int rearRightMotor = 9;
*/

//void moveRobot(string direction, int speed);

void setup() {
  Serial.begin(9600);
  pinMode(leftMotors, OUTPUT);
  pinMode(rightMotors, OUTPUT);
}

void loop() {
  String command;
  if(Serial.available()){
    command = Serial.readStringUntil('\n');
    moveRobot(command, movespeed);
  }  
}

//In case we need the CS 130 lab delay function, idk if we do though
void myDelay(int ms){
  int start_ms = millis();
  int current_ms;
  while(true){
    current_ms = millis();
    //Do stuff
    if(current_ms >= (start_ms+ms)){
      break;
    }
  }
}

//We might have to change backwards depending on how the h bridge works
void moveRobot(String movement, int velocity){
  analogWrite(leftMotors, 0);
  analogWrite(rightMotors, 0);
  delay(100);
  

  if(movement == "forward"){
      analogWrite(leftMotors, velocity);
      analogWrite(rightMotors, velocity);
  }
  else if(movement == "backward"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, -velocity);
      analogWrite(rightMotors, -velocity);
  }
  else if(movement == "left"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, velocity);
      analogWrite(rightMotors, turnvelocity);
  }
  else if(movement == "right"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, turnvelocity);
      analogWrite(rightMotors, velocity);
  }
  else if(movement == "hardleft"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, velocity);
      analogWrite(rightMotors, -velocity);
  }
  else if(movement == "hardright"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, -velocity);
      analogWrite(rightMotors, velocity);
  }
  else if(movement == "stop"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, 0);
      analogWrite(rightMotors, 0);
  }
}

