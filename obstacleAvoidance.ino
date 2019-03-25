/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <NewPing.h>

//Tell the Arduino where the sensor is hooked up
NewPing sonar(8, 9);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
int inches;

void look(void);

void setup() {
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {

  inches = sonar.ping_in();
  printdata();
  if (inches < 10) {
    look();
  }
  //check();
  digitalWrite(5,HIGH);
  delay(5000);
  digitalWrite(5,LOW);
  delay(5000);



}


void look(void) {

  for (pos = 90; pos <= 160; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    inches = sonar.ping_in();
    check();
    printdata();
    // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }


  for (pos = 160; pos >= 20      ; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    inches = sonar.ping_in();
    printdata();
    check();
    // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(15);

  for (pos = 20; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);
    inches = sonar.ping_in();
    printdata();
    check();
    // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }



  // waits 15ms for the servo to reach the position
}
void printdata() {
  Serial.print(inches);
  Serial.print(" in.");
  Serial.print("\n");


}

void check() {
  /*
    if(inches < 10){
    digitalWrite(5,HIGH);
    }
    else{
    digitalWrite(5,LOW);*/
}
