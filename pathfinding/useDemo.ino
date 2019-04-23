
//We might have to change backwards depending on how the h bridge works

//Constants:
int moveSpeed = 175; //units?? Change to m/sec please
int k = 1.25;//"magical constant" no clue what this does
int turnvelocity = moveSpeed*k;

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
