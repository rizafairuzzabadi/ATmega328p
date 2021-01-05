#include <Servo.h> 

int first_angle;	//for storing angle values 
int second_angle;
int third_angle;
int fourth_angle;

int flag = 1;	//for error checking purposes
int error = 0;	//set to 1 whenever there is error to be found


Servo servo1;	//initialize a servo objects for the connected servos
Servo servo2;
Servo servo3;
Servo servo4;


void setup()
{
    Serial.begin(9600);
    servo1.attach(3);	//Attach each Servo variable to pins it's connected to
    servo2.attach(5);
    servo3.attach(6);
    servo4.attach(9);
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
}

void ErrorChecker(String temp)	//for checking errors
{
  	String check;
  	int value = temp.toInt();	//getting temp value as integer
  	if(value > 180){
  		Serial.println("Error! Angle value must be less than 180");
      	error = 1;
    	return;
    }
  	int strlength = temp.length(); //for getting length of temp String
  	if(strlength == 0){				//to check if temp String is emptyblank
      	Serial.println("Error! All parameter must be filled");
      	error = 1;
    	return;
    }
  	int i;
  	for(i = 0; i < strlength; i++){
  		if(isAlpha(temp.charAt(i))){ //to check there is a char in the temp String
    		Serial.println("Error! Invalid Input.");
          	error = 1;
    		return;
		}
      	if(temp.charAt(i) == '!'){	//to check if the ending char is ! instead of #
          	Serial.println("Error! There is no end char.");
      		error = 1;
      		return;
        }
      	if(temp.charAt(i) == ';'){	//to check if there is another angle value after the 4th. 
          	Serial.println("Error! There is extra input input");
      		error = 1;
      		return;
        }
    }
}


void loop()
{
  if (Serial.available() > 0 ) {
    
    char first_char = Serial.read();
    //Serial.print(first_char);

    if (first_char == '!'){
      	String temp =  Serial.readStringUntil(';');	//read the data only until the particular char is seen
        ErrorChecker(temp);
      	first_angle = temp.toInt();
      	temp = Serial.readStringUntil(';');
        ErrorChecker(temp);
    	second_angle = temp.toInt();
      	temp = Serial.readStringUntil(';');
      	ErrorChecker(temp);
        third_angle = temp.toInt();
        temp = Serial.readStringUntil('#');
      	if(temp.length() == 0){			//check if the last angle is empty
        	Serial.println("Error! There is not enough input.");
          	error = 1;
          	return;
        }
        else
      		ErrorChecker(temp);
		fourth_angle = temp.toInt();
        

      	if(error == 0){
			servo1.write(first_angle);	//writes values to servos
        	servo2.write(second_angle);
        	servo3.write(third_angle);
        	servo4.write(fourth_angle);
          	Serial.print("S0:");	//prints the angle values according to the output pattern
          	Serial.print(first_angle);
          	Serial.print("; S1:");
     		Serial.print(second_angle);
          	Serial.print("; S2:");
      		Serial.print(third_angle);
          	Serial.print("; S3:");
      		Serial.print(fourth_angle);
          	Serial.print("\n");
        }
      	error = 0;
      	
    }
    else{
      	if(flag == 1){		//checks if the data pattern doesn't begin correctly 
          	Serial.println("Error! There is no start char.");
      		flag = 0;
          	Serial.flush();
      	}
        return;
    }
  }
}
