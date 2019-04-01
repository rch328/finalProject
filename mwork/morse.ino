int prevState;
unsigned long prevtime;
unsigned long currtime;
bool dash = false;
bool benchmarked = false;
int buttonState;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // LED's
  pinMode(13, OUTPUT);
  // Buttons
  pinMode(3, INPUT);
  //pinMode(A1, INPUT);
}

// LOW = ON
// HIGH = OFF
void loop() {
  // put your main code here, to run repeatedly:
  // pinMode(13, LOW);
  // delay(10000);

  /*while (!digitalRead(3)) {
    if(!benchmarked) {
      prevtime = millis();
      benchmarked = true;
    }
    //Serial.print("pressed\n");

    if (digitalRead(3)) {
      //Serial.print("released\n");
      if ((millis() - prevtime) > 1000) Serial.print("dash\n");
      else Serial.print("dot\n");
      benchmarked = false;
    }
    }*/



  /*
    buttonState = digitalRead(3);
    benchmarked = false;

    if (buttonState == LOW) { // being pressed
      pinMode(13, LOW);

      while (!digitalRead(3)) {
        if (!benchmarked) {
          prevtime = millis();
          benchmarked = true;
        }
      }

    }
    else {
      pinMode(13, HIGH);
    }
  */
  //*************************************************

  prevState = 1;
  benchmarked = false;
  while (!digitalRead(3)) {
    if (!benchmarked) {
      prevtime = millis();
      benchmarked = true;
    }

    // Serial.print("hi");
    // dash = false;
    if ((millis() - prevtime) > 1000 && !dash) {
      Serial.print("dash");
      Serial.print("\n");
      dash = true;
      break;
    }
    prevState = 0;
  }
  if (digitalRead(3) && prevState == 0) {
    if (!dash) {
      Serial.print("dot");
      Serial.print("\n");
    }
    dash = false;
    prevState = 1;
  }


} // end loop



