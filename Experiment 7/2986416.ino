#include <Wire.h>

#define DEVICE_ID 1 // defining device ID for future communication

/*void setup() {
	
	Serial.begin(9600);
  	Wire.begin(DEVICE_ID);
	Wire.onRequest(requestEvent);
}

void loop(){

}

void requestEvent() {
  String data = "abcde";
  Serial.println(data);
  
  Wire.write(data.c_str());
}*/

String output = "";
							// values that holds analog pins for future usage
const int flexPin1 = A0;
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A3;

const float VCC = 5;			// voltage at Ardunio 5V line
const float R_DIV = 100000.0;	// resistor used to create a voltage divider
const float flatResistance = 29987.28;	// resistance when flat
const float bendResistance = 162982.00;	// resistance at 90 deg


void setup()
{
 cli();        // disable all interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 12499;            // compare match register 16MHz/256/5Hz

  TCCR1B |= (1 << WGM12);   // CTC mode active
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); 
  sei();  // enable all interrupts// enable timer compare interrupt
  pinMode(flexPin1, INPUT); // defining flex pins as inputs
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);
  Serial.begin(9600);
  
  Wire.begin(DEVICE_ID); // this is slave. Hence device id is specified for begin function
  Wire.onRequest(requestEvent); // master request data to this arduino. When this operaiton occur, requestEvent function get invoked.
}
ISR(TIMER1_COMPA_vect){ // sampling frequency 5 hz, timer interrupt

  										// reading analog values via analogRead and store that information in variables	
  	int ADCflex1 = analogRead(flexPin1); 
  	int ADCflex2 = analogRead(flexPin2);
  	int ADCflex3 = analogRead(flexPin3);
  	int ADCflex4 = analogRead(flexPin4);
  										// transforming resistance value and angle value for ADCflex1
  	float Vflex1 = calc_Vflex(ADCflex1);
  	float Rflex1 = calc_Rflex(Vflex1);
  	float angle_flex1 = linear_resistance(Rflex1,flatResistance,bendResistance,0,180); // normalization angle function. we cannot use map()
    int i_angle_flex1 = angle_flex1;
  										// transforming resistance value and angle value for ADCflex2
    float Vflex2 = calc_Vflex(ADCflex2);
  	float Rflex2 = calc_Rflex(Vflex2);
  	float angle_flex2 = linear_resistance(Rflex2,flatResistance,bendResistance,0,180);
  	int i_angle_flex2 = angle_flex2;
  										// transforming resistance value and angle value for ADCflex3
    float Vflex3 = calc_Vflex(ADCflex3);
  	float Rflex3 = calc_Rflex(Vflex3);
  	float angle_flex3 = linear_resistance(Rflex3,flatResistance,bendResistance,0,180);// normalization angle function. we cannot use map()
  	int i_angle_flex3 = angle_flex3;
  										// transforming resistance value and angle value for ADCflex4
    float Vflex4 = calc_Vflex(ADCflex4);
  	float Rflex4 = calc_Rflex(Vflex4);
  	float angle_flex4 = linear_resistance(Rflex4,flatResistance,bendResistance,0,180);// normalization angle function. we cannot use map()
	int i_angle_flex4 = angle_flex4;
  	
  	// debug purpose code lines
	Serial.print("1: ");	
  	Serial.println(i_angle_flex1);
  	Serial.print("2: ");
  	Serial.println(i_angle_flex2);
  	Serial.print("3: ");
  	Serial.println(i_angle_flex3);
  	Serial.print("4: ");
  	Serial.println(i_angle_flex4);

  	output = String(i_angle_flex1) + "_" + String(i_angle_flex2) + "_" + String(i_angle_flex3) + "_" + String(i_angle_flex4) + ":";
	Serial.print("OUTPUT: ");
  	Serial.println(output);

}

float calc_Vflex(int ADCflex){ // 
  
	float Vflex = ADCflex * VCC / 1023.0;
	return Vflex;
}

float calc_Rflex(float Vflex){

    float Rflex = R_DIV * (VCC / (VCC - Vflex)) - R_DIV;
    return Rflex;
}

long linear_resistance(long x, long in_min, long in_max, long out_min, long out_max) { // normalization
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; // we know flat and bend resistance values and angle values should be on
  																		 	// [0-180] interval, we normalize linearly to obtain angle values for send thing this inofrmation
}

void loop()
{

}

void requestEvent() { // master request an even t from this slave
 // Serial.println("Request event ***");
 // Serial.println(output);
  
  Wire.write(output.c_str()); // writing output information to wire using i2c.
}
