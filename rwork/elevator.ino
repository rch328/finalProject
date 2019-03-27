//Function to lift arm to press elevator buttons

void moveElevator(string movement){

	int d = 20; //distance button presser needs to move (measured) (meters)
	int v = 1;//desired velocity of motor (m/s)
	int t = d/(v*1000);//time it takes to go distance (milliseconds)

	//start with motor off
	analogWrite(motor, 0);
	delay(100);

	//d = vt, use time to find distance, stop after a given distance

	if(movement == "up"){
		analogWrite(motor, v);
		delay(t);
		analogWrite(motor, 0);
	}	
}

//Function to press button

void pressButton(){

}
