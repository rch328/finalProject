/This is the file with the code to read temperatures

//Author : Rachel Harris

//Sensor reads a temperature in degrees C
//Function turns fan on if temperature is above 20 degrees

#include "ClosedCube_STS35.h"
#define STS35_I2C_ADDRESS 0x4B //no clue what this line does...
ClosedCube::Sensor::STS35 sts35; //instantiates an object for the temperature sensor?

void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT); //pin temp sensor is attached to -- not actually used
  pinMode(5, OUTPUT); //pin fan is attached to

	sts35.address(STS35_I2C_ADDRESS);
}

void loop(){
	//declare variables
		bool fanStatus=false;//status bool of fan
		int tempVal = 0;//temperature inputed

	//read in temperature from sensor
		fanStatus = sts35.readTemperature();

	//if fan is off, call function
  /*
		if(digitalRead(5)==LOW){
			fanStatus = temp(tempVal);
		}
*/
Serial.print(fanStatus);
}

//Function to read the temperature
//Input: temperature
//Action: turn fan on if temperature is >20 degrees Celcius
//Output: true if fan is on, false if fan is off

bool temp(int tmp){
	if(tmp>20){//temperature is greater than room temperature
		//turn fan on
		digitalWrite(5,HIGH);
		delay(5000);
		return true;
	}
	return false;
}
