

void setup()
{
	DDRB = B000000;
  	DDRD = B11111111;
}

void loop()
{
	if((PINB & B000011) == 0)
    {
      for(int i = B00000001; i < B10000000; i = i << 1)
      {
        PORTD = i;
      	delay(100);
      }
      for(int i = B10000000; i > B0000001; i = i >> 1)
      {
     	 PORTD = i;
         delay(100);
      }
    }
  
  	if( ( PINB & B000011) == 1)
    {
    	for(int i = B10000000; i > B0000000; i = i >> 1)
        {
            PORTD = i;
	        delay(100);
        }      
    }
  	
  	if( ( PINB & B000011) == 2)
    {
      	PORTD = B10000000;
      	delay(500);
      	int counter = 0;
    	for(int i = 6; i >= 0; i = i - 2)
        {
        	if(counter % 2 == 0)
            {
              PORTD = PORTD >> i;
            }          
          	else
            {
              PORTD = PORTD << i;
            }     
          delay(500);
          counter++;
        }
      
      	for(int j = 2; j <=6; j = j+2)
        {
        	if(counter % 2 == 1)
            {
              PORTD = PORTD >> j;
            }          
          	else
            {
              PORTD = PORTD << j;
            }     
          delay(500);
          counter++;        	
        }
    }
  	
  	if((PINB & B000011) == 3)
    {
   		for(int i = B00000001; i < B00001000; i = i << 1)
        {
          PORTD = i;
          delay(250);
        }
        for(int i = B00001000; i >= B00000001; i = i >> 1)
        {
          PORTD = i;
          delay(250);
        }
        for(int i = B10000000; i > B00010000; i = i >> 1)
        {
          PORTD = i;
          delay(250);
        }
        for(int i = B00010000; i <= B10000000; i = i << 1)
        {
          PORTD = i;
          delay(250);
        }
    }
}