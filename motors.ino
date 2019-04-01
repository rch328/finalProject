//MOTORS - This file doesn't work!

//We can use the width to calculate how fast the motors have to turn
int width;
int leftFor = 3;
int leftBack = 4;
int rightFor = 5;
int rightBack = 6;
//This is a global variable, delete later
//int movespeed = 250;
//Magicalconstant is when I figure out the math for the turning arc for the wheels
//It will be something like radius of turn plus the width of the robot between 
int magicalconstant = 1.25;
//This is whatever equation i think that we convert to linear velocity I think
int movespeed = HIGH;
int turnvelocity = movespeed;// * magicalconstant;

/*
int frontLeftMotor = 6;
int frontRightMotor = 7;
int rearLeftMotor = 8;
int rearRightMotor = 9;
*/

//void moveRobot(string direction, int speed);

void setup() {
  Serial.begin(9600);
  pinMode(leftFor, OUTPUT);
  pinMode(leftBack, OUTPUT);
  pinMode(rightFor, OUTPUT);
  pinMode(rightBack, OUTPUT);
}
//We might have to change backwards depending on how the h bridge works
void moveRobot(String movement, int velocity){
  digitalWrite(leftFor, LOW);
  digitalWrite(leftBack, LOW);
  digitalWrite(rightFor, LOW);
  digitalWrite(rightBack, LOW);
  delay(100);

Serial.print("Moving");
  
movement = "forward";
  if(movement == "forward"){
      digitalWrite(leftFor, velocity);
      digitalWrite(rightFor, velocity);
  }
  else if(movement == "backward"){
      //This will definitely have to change, digital write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      digitalWrite(leftBack, velocity);
      digitalWrite(rightBack, velocity);
  }
  else if(movement == "left"){
      //This will definitely have to change, digital write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      digitalWrite(leftFor, velocity);
      digitalWrite(rightFor, turnvelocity);
  }
  else if(movement == "right"){
      //This will definitely have to change, digital write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      digitalWrite(leftFor, turnvelocity);
      digitalWrite(rightFor, velocity);
  }
  else if(movement == "hardleft"){
      //This will definitely have to change, digital write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      digitalWrite(leftFor, velocity);
      digitalWrite(rightBack, velocity);
  }
  else if(movement == "hardright"){
      //This will definitely have to change, digital write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      digitalWrite(leftBack, velocity);
      digitalWrite(rightFor, velocity);
  }
  else if(movement == "stop"){
      //This will definitely have to change, digital write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      digitalWrite(leftFor, LOW);
      digitalWrite(rightFor, LOW);
      digitalWrite(leftBack, LOW);
      digitalWrite(rightBack, LOW);
  }
}
void loop() {
  Serial.print("In loop");
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
