//Constants:
int moveSpeed = 175; //units?? Change to m/sec please
int k = 1.25;//"magical constant" no clue what this does
int turnvelocity = moveSpeed*k*1.2;
int timeDelay = 787;

//Moves the robot based off of a given movement command and velocity
void moveRobot(String movement, int velocity){
  analogWrite(leftMotorBow, 0);
  analogWrite(rightMotorBow, 0);
  analogWrite(leftMotorAft, 0);
  analogWrite(rightMotorAft, 0);
  delay(100);

  //We needed the constant because the robot wasn't dribing straight and erring to the right  
  int rvelocity = velocity *1.35;
  
  if(movement == "forward"){
      analogWrite(leftMotorBow, velocity);
      analogWrite(rightMotorBow, rvelocity);
  }
  else if(movement == "backward"){
      analogWrite(leftMotorAft, velocity);
      analogWrite(rightMotorAft, rvelocity);
  }//We need a way to make the robot turn 90 degrees and then stop, not just by timing how long it takes to make a 90 degree turn.
  else if(movement == "right"){
      analogWrite(leftMotorBow, velocity);
      analogWrite(rightMotorBow, turnvelocity);
  }
  else if(movement == "left"){
      analogWrite(leftMotorBow, turnvelocity);
      analogWrite(rightMotorBow, velocity);
  }
  else if(movement == "180"){ //Turns 180 backwards
    analogWrite(leftMotorBow, velocity);
    analogWrite(rightMotorAft, velocity);
    delay(timeDelay*2.5);
  }
  else if(movement == "hardRight"){//Turns 90 degrees right
      analogWrite(leftMotorBow, velocity);
      analogWrite(rightMotorAft, velocity);
      delay(timeDelay*1.25);
  }
  else if(movement == "hardLeft"){//Turns 90 degrees left
      analogWrite(leftMotorAft, velocity);
      analogWrite(rightMotorBow, velocity);
      delay(timeDelay*1.25);
  }
  else if(movement == "stahp"){
      analogWrite(leftMotorBow, 0);
      analogWrite(leftMotorAft, 0);
      analogWrite(rightMotorBow, 0);
      analogWrite(rightMotorAft, 0);
  }
}

//This reads in the sensor data and 
void realign(int R, int L){//R and L are distance in inches
  //takes data from distance sensors
  //if R and L are same, exit
  if(R==L){
    exit(0);
  }
  //if R is greated than L, move slightly right
  if(R > L){
    //move distance R-L to the right.
      //to do this, drive with slightly greater velocity in left wheel -- test for values

      analogWrite(leftMotorBow, 175+2*R);
      analogWrite(rightMotorBow, 175+2*L);
      if(R == L){
      //moveRobot("forward", 0);
      }
  }else {//else move slightly left
     //move distance L-R to the left.
      //to do this, drive with slightly greater velocity in right wheel -- test for values
      analogWrite(leftMotorBow, 175+2*L);
      analogWrite(rightMotorBow, 175+2*R);
      if(R == L){
        //moveRobot("forward", 0);
      }
  }
}
