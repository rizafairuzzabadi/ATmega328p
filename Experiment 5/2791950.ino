int disp_val = 0;
int mode = 1;
int second = 1000;
unsigned long time = 0;

void reset()// display value = 0, reset operation
{
	disp_val = 0;
    display();
}
void switch_mode() // switch mode according to button's state
{
	mode *= -1;
}

void display()
{
    int val_ones = disp_val % 10; //ones digit
    int val_tens = disp_val / 10; //tens digit
    
    PORTC = val_tens; // first seven segment shows tens digit
    PORTB = val_ones; // second seven segment shows ones digit
}


void setup()
{
	// using DDR registers pins determined as input or output 
 	DDRB |= 0b111111; 
  	DDRC |= 0b111111;
  	DDRD |= 0b00000000;
  	PORTB = 0b000000;
  	PORTC = 0b000000;
  	attachInterrupt(digitalPinToInterrupt(3), reset, RISING); //according to pin 3 (first button) is pressed, RISING state we call reset function 
    attachInterrupt(digitalPinToInterrupt(2), switch_mode, RISING); //according to pin 2 (second button) is pressed, RISING state we call switch_mode function 
	
}

void loop()
{
  
  if( millis() >= (time + second) ) // the code runs if millis exceeds current time + 1 second
  {
    
  	time = millis();    
    if (mode == 1)
  	{    
   	  disp_val++; // countup
  	}
  	else
  	{
  		disp_val--;//countdown
  	}
	display();
  }
  
  if(mode == 1 && disp_val == 99) // corner cases
  {
  	disp_val = -1; 
  }
  if(mode == -1 && disp_val == 0) // corner cases
  {
  	disp_val = 100;
  }


}


