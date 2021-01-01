volatile uint8_t* port;

void setup()
{
	DDRD |= B11111111;
    port  = &PORTD;
} 

void loop()
{							  
  for(int i = B00000001; i < B10000000; i = i*2)
  {
    PORTD = i;
	delay(1000);
  }
  for(int i = B10000000; i > B0000001; i = i/2)
  {
  	PORTD = i;
	delay(1000);
  }
  
}