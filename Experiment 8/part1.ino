int Sn;
int Sn1 = 3; // first two numbers initialization
int Sn2 = 4;
int sum;
//Array for 7 segment signal hexadecimal encodings in D and B pins
byte arrayD[] = {B11000000, B10000000, B11000000, B11000000, B10000000, B01000000, B01000000, B11000000, B11000000, B11000000, B11000000, B00000000, B01000000, B10000000, B01000000, B01000000};
byte arrayB[] = {B001111, B000001, B010110, B010011, B011001, B011011, B011111, B000001, B011111, B011001, B011101, B011111, B001110, B010111, B011110, B011100};

void setup()
{
      DDRD = 0b11000000; // sets Arduino pins 6 to 7 as outputs, pin 0 to 5 as inputs
      DDRB |= 0b011111;	 // sets Arduino pins 8 to 12 as outputs, pin 13 as input	
      attachInterrupt(digitalPinToInterrupt(3), generate, RISING); // trigger generate func. when the pin (3) goes from low to high -by the button
}

void generate()
{		//Lagged Fibonacci generator
      sum = Sn1 + Sn2;		//recurrence relation
      Sn = sum % 16;	
      PORTD = arrayD[Sn];	//sets D pins high or low according to the 7 segment encoding
      PORTB = arrayB[Sn];   //sets B pins high or low according to the 7 segment encoding
      Sn2 = Sn1;
      Sn1 = Sn;
}

void loop()
{
}
