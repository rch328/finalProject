//Main for 23 April 2019 demonstration

//Goal: Start from side of room. Drive 3.048 m, turn right, drive 7.62 m, turn right, drive until you hit the wall.
//When wall is hit, stop and raise elevator.

//Arduino ports:
int width;
int leftMotorBow = 3;//Bow: forward, Aft:back
int leftMotorAft = 4;
int rightMotorBow = 5;
int rightMotorAft = 6;
int eleMotorUp = 7; //elevator motor 
int eleMotorDown = 2;

//Constants:
int moveSpeed = 175; //units?? Change to m/sec please
int k = 1.25;//"magical constant" no clue what this does
int turnvelocity = moveSpeed*k;

void setup() {
  Serial.begin(9600);
  //declare motor pins
  pinMode(leftMotorBow, OUTPUT);
  pinMode(rightMotorBow, OUTPUT);
  pinMode(eleMotorUp, OUTPUT);

  //declare distance sensor: THIS NEEDS WORK
  //pinMode(2, INPUT);
  //pinMode(5, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  moveRobot("backward", moveSpeed);
  delay(3048/*moveSpeed*/);//t=d/v
  moveRobot("hardLeft", moveSpeed);
  delay(500);
  moveRobot("forward", moveSpeed);
  delay(7620/*moveSpeed*/);
  moveRobot("hardRight", moveSpeed);
  delay(500);
  moveRobot("forward", moveSpeed/2);
  //Stop when distance sensor detects bumping into walls
 /* if(){
    moveRobot("stahp", 0);
    //raise elevator
    movElevator("up");
  }*/

  delay(1000);
  moveRobot("stahp", moveSpeed);
  delay(2000);
}
//Elevator Move function
void movElevator(const String movement){
  int d=1117; //vertical distance to move (millimeters) **SUBTRACT MOUNTING HEIGHT!!**
  int v=1; //velocity: we want the elevator to be kind of slow, doesn't need variable speed (m/s)
  int t=(d/v)*1000; //time to go distance (calculated) (milliseconds)

  analogWrite(eleMotorUp, 0);
  delay(100);

  if(movement == "up"){
    analogWrite(eleMotorUp, v);
    delay(t);
    analogWrite(eleMotorUp, 0);
  }else if(movement == "down"){
    analogWrite(eleMotorDown, v);
    delay(t);
    analogWrite(eleMotorDown, 0);
  }
}

//We might have to change backwards depending on how the h bridge works
void moveRobot(String movement, int velocity){
  analogWrite(leftMotorBow, 0);
  analogWrite(rightMotorBow, 0);
  analogWrite(leftMotorAft, 0);
  analogWrite(rightMotorAft, 0);
  delay(100);
  
  if(movement == "forward"){
      analogWrite(leftMotorBow, velocity);
      analogWrite(rightMotorBow, velocity);
  }
  else if(movement == "backward"){
      analogWrite(leftMotorAft, velocity);
      analogWrite(rightMotorAft, velocity);
  }//We need a way to make the robot turn 90 degrees and then stop, not just by timing how long it takes to make a 90 degree turn.
  else if(movement == "right"){
      analogWrite(leftMotorBow, velocity);
      analogWrite(rightMotorBow, turnvelocity);
  }
  else if(movement == "left"){
      analogWrite(leftMotorBow, turnvelocity);
      analogWrite(rightMotorBow, velocity);
  }
  else if(movement == "180"){
    analogWrite(leftMotorBow, velocity);
    analogWrite(rightMotorAft, velocity);
    delay(600*2);
  }
  else if(movement == "hardRight"){//Turns 90 degrees right
      analogWrite(leftMotorBow, velocity);
      analogWrite(rightMotorAft, velocity);
      delay(600);
  }
  else if(movement == "hardLeft"){//Turns 90 degrees left
      analogWrite(leftMotorAft, velocity);
      analogWrite(rightMotorBow, velocity);
      delay(600);
  }
  else if(movement == "stahp"){
      analogWrite(leftMotorBow, 0);
      analogWrite(leftMotorAft, 0);
      analogWrite(rightMotorBow, 0);
      analogWrite(rightMotorAft, 0);
  }
}
