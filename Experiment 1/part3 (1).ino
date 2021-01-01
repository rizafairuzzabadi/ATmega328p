volatile uint8_t* port;

void setup()
{
	DDRD |= B11111111;
	port = &PORTD;
} 

void loop()
{
 	PORTD = B01100001;
  	delay(2000);
  
  	PORTD = B01101011;
	delay(2000);
  
  	PORTD = B01110010;	
  	delay(2000);
}