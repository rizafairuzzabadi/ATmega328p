int first_half_pattern1 = 0b0001;
int second_half_pattern1 = 0b1000;
int first_half_pattern2= 0b1;
int second_half_pattern2 = 0b0000001;
int mode = 0;
int mode_0_direction = 0;
int counter = 1;
int setter = 0;
byte result;

void switch_mode() // this function switches patterns to display
{
	if(mode == 0)
    {
    	mode = 1; // switch mode
        second_half_pattern1 = 0b1000; //when mode switches we start from beginning of pattern
      	first_half_pattern1 = 0b0001;
    }
  	else
    {
    	mode = 0; // switch mode
      	first_half_pattern2= 0b1; //when mode switches we start from beginning of pattern
		second_half_pattern2 = 0b0000001;
    }
}

void setup()
{
  cli();//stop interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  OCR1A = 15624; // 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
  DDRB = B111111;
  DDRD = B11000000;
  attachInterrupt(digitalPinToInterrupt(3), switch_mode, RISING); // switch_mode function invokes when button is RISING
}

ISR(TIMER1_COMPA_vect){

	if(mode == 0 && mode_0_direction == 0) // first pattern , iterating left
    {
    	result = (first_half_pattern1 << 4) | second_half_pattern1; 
    	byte x = result & 0b00000011;
    	byte y = x << 6; // taking least significant 2 bits from x and write to y
    	PORTD = y; // portd => rightmost 2 leds 
    	PORTB = result >> 2 ; // in order to get proper 6 bits result shifting right 2
      	if(result != B10000001)
        {
    	first_half_pattern1 = first_half_pattern1 << 1; // left part of pattern shift to left
    	second_half_pattern1 = second_half_pattern1 >> 1;// right part of pattern shift to right
        }
    }
  	
  	if(mode == 0 && mode_0_direction == 1) //first pattern, iterating right
    {
        result = (first_half_pattern1 << 4) | second_half_pattern1; 
        byte x = result & 0b00000011;
        byte y = x << 6;
        PORTD = y;
        PORTB = result >> 2 ;
      	if(result != B00011000)
        {
        first_half_pattern1 = first_half_pattern1 >> 1;
        second_half_pattern1 = second_half_pattern1 << 1;
        }
    }
  
  if(mode == 0 && mode_0_direction == 0 && result == B10000001){ // these condititons are checked after so
      mode_0_direction = 1;										 // so if mode direction switched from 0 to 1, direction 1 waits for  the clock tick to start.
  }
  if(mode == 0 && mode_0_direction == 1 && result == B00011000){
      mode_0_direction = 0;
  }
  if(mode == 1){
  		result = (first_half_pattern2 << 7) | second_half_pattern2; // mode = 1 means 2.pattern
    	byte x = result & 0b00000011; 
    	byte y = x << 6; // taking least significant 2 bits from x and write to y
    	PORTD = y; // portd => rightmost 2 leds
    	PORTB = result >> 2 ; // in order to get proper 6 bits result shifting right 2
  		if(counter%2 == 0)
    		first_half_pattern2 = 1; // when counter is 2k leftmost led is ON
  		else 
      		first_half_pattern2 = 0; // else OFF
  		counter++;
  		if(setter == 0) // we make shift operations for evaluating asked patterns shift to left
  			second_half_pattern2 = second_half_pattern2 << 1; 
  		if(setter == 1)
      		second_half_pattern2 = second_half_pattern2 >> 1;
  		if(second_half_pattern2 == 0b0000001)
    		setter = 0;
  		if(second_half_pattern2 == 0b10000000)
      		setter = 1;
  }

}

void loop()
{

}