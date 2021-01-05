#include <Wire.h>
#include <Servo.h> 

#define DEVICE_ID 4 // in order to communica device needs an id,
String output_1 = "";
String first = "";
String second ="";
String third = "";
String fourth = "";
int flag = 0;
String a = "23";

// servo engines initilization
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;



void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for outpu 
  servo1.attach(3);				// using attach function from servo.h library, pin3 attached to servo according to given design
  servo2.attach(5);				// using attach function from servo.h library, pin5 attached to servo according to given design
  servo3.attach(6);				// using attach function from servo.h library, pin6 attached to servo according to given design
  servo4.attach(9);				// using attach function from servo.h library, pin9 attached to servo according to given design
}


void loop()
{

}

void receiveEvent(int howMany)
{
  while(0 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character, reading char by char
            
    output_1 += c; // at the end of this loop, output_1 should store received information
  }
  parse(); // parsing the received information in order to obtain servo engine controlling angles
  output_1 = "";
  // get integer values of string
  int i_first = get_int(first.c_str());
  int i_second = get_int(second.c_str());
  int i_third = get_int(third.c_str());
  int i_fourth = get_int(fourth.c_str());
  
  servo1.write(i_first); // write corresponding angle value to servo1
  servo2.write(i_second);// write corresponding angle value to servo2
  servo3.write(i_third); // write corresponding angle value to servo3
  servo4.write(i_fourth); // write corresponding angle value to servo4
}
int get_int(String angle){ // string to integer function, we explain this in masterMC's code
  	//Serial.print("Inside:");
  	//Serial.println(angle);
    int i = 0;
    int total1 = 0;
  while (angle[i] != '\0') {
    i++;
  }
  int k = i;
  for(k=i;k>0;k--){
   int temp = angle[k-1] - '0';
   int mult = (pow(10,i-k) + 0.5);
   int mult2 = mult * temp;
   total1 += mult2;
  }
  if( total1 > 180){ // problem with tinkercad, when casting in to string.
  	total1 = 180;
  }
  //Serial.println(total1);
  return total1;
}

void parse() { // parsing the information to obtain meaningful(ready to use) data

first = "";
second = "";
 third = "";
 fourth = "";


  if(output_1[0] == '0' || flag == 1){ // we check if received information is valid by flag and first servos value(it may not be 0, hence we use flag)
	//Serial.println("asd");
  flag = 1;
  int i = 0;
  int j = 0;
  while(output_1[i] != '_') // reads output until reach '_' charachter which is a delimeter for first angle value  according to our output style
  {
   // Serial.print("output:");
    //Serial.println(output_1);
    first += output_1[i];
    i++;
    j++;
   // Serial.print("first :");
    //Serial.println(first);
  }

  i++;
  j = 0;
  while(output_1[i] != '_')// reads output until reach '_' charachter which is a delimeter for second angle value according to our output style
  {
    second += output_1[i];
    i++;
    j++;
  }

  i++;
  j = 0;
  while(output_1[i] != '_') // reads output until reach '_' charachter which is a delimeter for third angle value according to our output style
  {
    third += output_1[i];
    i++;
    j++;
  }

  i++;
  j = 0;
  while(output_1[i] != ':') // reads output until reach ':' charachter which is a delimeter for fourth angle value according to our output style
  {
    fourth += output_1[i];
      i++;
    j++;
  }
    //print();
  }
 
}
/*
void print() {
	Serial.println("print***");
  	Serial.println(output_1);
	Serial.println(first);
  	Serial.println(second);
  	Serial.println(third);
  	Serial.println(fourth);
}
*/
/*#include <Servo.h> 

#define DEVICE_ID 2

int first_angle;
int second_angle;
int third_angle;
int fourth_angle;

int flag2 = 0;
String output_2 ="";

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


void setup()
{
    Serial.begin(9600);
  	Wire.begin(DEVICE_ID);
  	Wire.onReceive(receiveEvents);
    
}

void receiveEvents(){
	output_2 = "";
  	  	while (Wire.available()) { 
    	char c = Wire.read(); 
    	output_2 += c;         
  	}
  Serial.println(output2.c_str());

}

void loop()
{

}

*/


/*int first_angle;
int second_angle;
int third_angle;
int fourth_angle;



int get_int(String angle){
    int i = 0;
    int total1 = 0;
  while (angle[i] != '\0') {
    i++;
  }
  int k = i;
  for(k=i;k>0;k--){
   int temp = angle[k-1] - '0';
   int mult = (pow(10,i-k) + 0.5);
   int mult2 = mult * temp;
   total1 += mult2;
  }
  return total1;
}


void setup()
{
  Serial.begin(9600);
}


void loop()
{
  if (Serial.available() > 0 ) {
    int flag = 0;
    char first_char = Serial.read();
    //Serial.print(first_char);

    if (first_char == '!'){
        String temp =  Serial.readStringUntil(';');
        first_angle = get_int(temp);
        Serial.println(first_angle);
      	temp =  Serial.readStringUntil(';');
		second_angle = get_int(temp);
        Serial.println(second_angle);
      	String temp2 = Serial.readStringUntil(';');
        third_angle = get_int(temp2);
        Serial.println(third_angle);

    }
    else{
          Serial.println("Error! There is no start char.");
        return;
    }
  }
}


*/


/*char first_angle[4];
char second_angle[4];
char third_angle[4];
char fourth_angle[4];

int arr[4];
int i=0;

void setup() {
  Serial.begin(9600);
}
void print() {
  for (int i = 0;i < 4;i++) {
  	Serial.println()
  } 
}
void loop()
{
    if (Serial.available() > 0)
    { 
    	int flag = 0;
    	char first_char = Serial.read();
      
      if (first_char == '!'){
     	
        char temp;
        temp = Serial.read();
        
        
        
      }
      else {
        
        Serial.println('Error! There is no start char.');
      	
      }
              
    }
  	print();
}*/