#include <Wire.h>

#define DEVICE_ID_1 1
#define DEVICE_ID_2 2

int display_time = 0;
int mili = 200;

#define DEVICE_1_SIZE 16


int k=0;
int first_angle;
int second_angle;
int third_angle;
int fourth_angle;

String output_1 = "";


void setup()
{

  Serial.begin(9600);
  output_1 = "";
  Wire.begin();
  
}



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


void loop()
{
  if (millis() >= (display_time + mili))
  {
    readSensorMC();
  	sendtoServoMC();
    display_time += mili;
  }

  	
}
void readSensorMC(){

	output_1 = "";
    Wire.requestFrom(DEVICE_ID_1, DEVICE_1_SIZE);    
  	while (Wire.available()) { 
    	char c = Wire.read(); 
    	output_1 += c;         
  	}
  

}
void sendtoServoMC(){
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(output_1.c_str());        // sends five bytes
  Wire.endTransmission();    // stop transmitting
}
