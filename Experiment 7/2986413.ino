const int flexPin1 = A0;	//Flex Sensor&Voltage divider pins
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

  OCR1A = 12499;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode active
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); 
  sei();  // enable all interrupts// enable timer compare interrupt
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);
  Serial.begin(9600);
}
ISR(TIMER1_COMPA_vect){

  	int ADCflex1 = analogRead(flexPin1);	//reading and storing ADC Values
  	int ADCflex2 = analogRead(flexPin2);	
  	int ADCflex3 = analogRead(flexPin3);
  	int ADCflex4 = analogRead(flexPin4);
  
  	float Vflex1 = calc_Vflex(ADCflex1);	//calculating voltage
  	float Rflex1 = calc_Rflex(Vflex1);		//calculating resistance
  	float angle_flex1 = linear_resistance(Rflex1,flatResistance,bendResistance,0,180);	// Use the calculated resistance to estimate the sensor's bend angle
    int i_angle_flex1 = angle_flex1;
  
    float Vflex2 = calc_Vflex(ADCflex2);
  	float Rflex2 = calc_Rflex(Vflex2);
  	float angle_flex2 = linear_resistance(Rflex2,flatResistance,bendResistance,0,180);
  	int i_angle_flex2 = angle_flex2;
  
    float Vflex3 = calc_Vflex(ADCflex3);
  	float Rflex3 = calc_Rflex(Vflex3);
  	float angle_flex3 = linear_resistance(Rflex3,flatResistance,bendResistance,0,180);
  	int i_angle_flex3 = angle_flex3;
  
    float Vflex4 = calc_Vflex(ADCflex4);
  	float Rflex4 = calc_Rflex(Vflex4);
  	float angle_flex4 = linear_resistance(Rflex4,flatResistance,bendResistance,0,180);
	int i_angle_flex4 = angle_flex4;

  	
	Serial.print("!0;" + String(ADCflex1) +";" + String(Rflex1) + ";");	//printing the angle values according to the pattern
  	Serial.print(i_angle_flex1);
 	Serial.println("#");
  
  	Serial.print("!1;" + String(ADCflex2) +";" + String(Rflex2) + ";");
  	Serial.print(i_angle_flex2);
 	Serial.println("#");
  
  	Serial.print("!2;" + String(ADCflex3) +";" + String(Rflex3) + ";");
  	Serial.print(i_angle_flex3);
 	Serial.println("#");
  
  	Serial.print("!3;" + String(ADCflex4) +";" + String(Rflex4) + ";");
  	Serial.print(i_angle_flex4);
 	Serial.println("#");


}
float calc_Vflex(int ADCflex){
  
	float Vflex = ADCflex * VCC / 1023.0;	//calculating voltage from adc value
	return Vflex;
}
float calc_Rflex(float Vflex){				//calculating resistance

    float Rflex = R_DIV * (VCC / (VCC - Vflex)) - R_DIV;
    return Rflex;
}

long linear_resistance(long x, long in_min, long in_max, long out_min, long out_max) {	//map() normalization
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop()
{

}
