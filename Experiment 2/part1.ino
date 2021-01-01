

void setup()
{
	DDRD = B11111111;
  	DDRB |= (0<<DDB3); // pin 11 is input mode
  	DDRB |= (0<<DDB2); // pin 10 is input mode
  	
}

void loop()
{
  	
	if((PINB & B00001000) == 8 || (PINB & B00000100) == 0) 
    {
     	 PORTD -= 1;
      	 delay(2000);
    }
  	else 
  	{
    	 PORTD += 1;
         delay(2000);
  	}
}