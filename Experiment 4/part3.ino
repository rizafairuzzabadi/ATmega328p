int val;	//to store potentiometer value
int digit;	//for digit shifting
byte array[] = {B0000001,B1001111,B0010010,B0000110,B1001100,B0100100,B0100000,B0001111,B0000000,B0000100};
//bytes for 7-Segment Display ports
void setup()
{
	pinMode(0, OUTPUT);	//setting output pins - 0 for 7-segment
  	pinMode(1, OUTPUT);	//1 - value used for 7-segment display
	pinMode(2, OUTPUT);	//2 - value used for 7-segment display
	pinMode(3, OUTPUT);	//3 - value used for 7-segment display
  	pinMode(4, OUTPUT);	//4 - value used for 7-segment display
  	pinMode(5, OUTPUT);	//5 - value used for 7-segment display
  	pinMode(6, OUTPUT);	//6 - value used for 7-segment display
  
    pinMode(11, OUTPUT); //11 - value used for 7-segment display
  	pinMode(10, OUTPUT); //10 - value used for 7-segment display
	pinMode(9, OUTPUT);  //9  - value used for 7-segment display
  	pinMode(8, OUTPUT);  //8  - value used for 7-segment display
}

void loop()
{
	val = analogRead(A0);	//Read potentiometer value, to val
    PORTB = B0001111;		//set to HIGH before 7-segment values to display are set
  	if(digit == 1){
    	PORTD = array[val/1000];//port D bits set according to MSB value in array 
      	PORTB = B0000111;//BJT low to show result on 1th digit
    }if(digit == 2){
    	PORTD = array[(val/100)%10];//port D bits set acc. to hundreth value in array
      	PORTB = B0001011;//hundreth digit
    }if(digit == 3){
        PORTD = array[(val/10)%10];//port D bits set acc. to 10th value in array
      	PORTB = B0001101;//tenth digit
    }if(digit == 4){
        PORTD = array[val%10];//port D bits set acc. to LSB value in array
      	PORTB = B0011110;//oneth digit
    }
  	digit = (digit % 4) + 1;//for gradual setting of digits 1-4
}