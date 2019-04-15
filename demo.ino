//Main for 23 April 2019 demonstration

//Goal: Start from side of room. Drive 3.048 m, turn right, drive 7.62 m, turn right, drive until you hit the wall.
//When wall is hit, stop and raise elevator.

//Arduino ports:
int leftMotors = 8;
int rightMotors = 9;
int eleMotor = 7;

//Constants:
int moveSpeed = 50; //units?? Change to ft/sec please
int k = 1.25;//"magical constant" no clue what this does
int turnvelocity = moveSpeed*k;

void setup() {
  Serial.begin(9600);
  //declare motor pins
  pinMode(leftMotors, OUTPUT);
  pinMode(rightMotors, OUTPUT);
  pinMode(eleMotor, OUTPUT);

  //declare distance sensor
  pinMode(2, INPUT);
  pinMode(5, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  moveRobot("backward", moveSpeed);
  delay(3048/moveSpeed);//t=d/v
  moveRobot("left", moveSpeed);
  moveRobot("forward", moveSpeed);
  delay(7620/moveSpeed);
  moveRobot("right", moveSpeed);
  moveRobot("forward", moveSpeed/2);
  //Stop when distance sensor detects bumping into walls
 /* if(){
    moveRobot("stahp", 0);
    //raise elevator
    movElevator("up");
  }*/
  
}
//Elevator Move function
void movElevator(const String movement){
  int d=1117; //vertical distance to move (millimeters) **SUBTRACT MOUNTING HEIGHT!!**
  int v=1; //velocity: we want the elevator to be kind of slow, doesn't need variable speed (m/s)
  int t=(d/v)*1000; //time to go distance (calculated) (milliseconds)

  analogWrite(eleMotor, 0);
  delay(100);

  if(movement == "up"){
    analogWrite(eleMotor, v);
    delay(t);
    analogWrite(eleMotor, 0);
  }else if(movement == "down"){
    analogWrite(eleMotor, -v);
    delay(t);
    analogWrite(eleMotor, 0);
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
  else if(movement == "stahp"){
      //This will definitely have to change, analog write doesn't take negative values, we change the polarity of the signal through the motors with the h bridge
      analogWrite(leftMotors, 0);
      analogWrite(rightMotors, 0);
  }
}
