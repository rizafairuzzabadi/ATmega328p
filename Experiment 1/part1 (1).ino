
void setup()
{
	DDRD |= B11111111;		
}

void loop()
{
    for(int i=0; i < 256; i++){
      PORTD = i;
      delay(500);
    }
    PORTD = 0;
}