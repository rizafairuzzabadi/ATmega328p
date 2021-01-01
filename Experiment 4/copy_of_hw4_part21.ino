int POT = A0; // potentiometer wiper is A0 port. we declare it as POT

int ones_digit=0; // declare current_digit
int value; // value that will store the analog inputs value

int a = 6; // pin 6 as denoted by a
int b = 5; // pin 5 as denoted by b
int c = 4; // pin 4 as denoted by c
int d = 3; // pin 3 as denoted by d
int e = 2; // pin 2 as denoted by e
int f = 1; // pin 1 as denoted by f
int g = 0; // pin 0 as denoted by g
int pnp = 8; // pin 8 as denoted by pnp


// array stores the values between 0-9 according to seven segment's assigned ports
// i.e : (number_patterns[6] gives a pattern that will show 6 on seven segment)
byte number_patterns[] = {B0000001,B1001111,B0010010,B0000110,B1001100,B0100100,B0100000,B0001111,B0000000,B0000100};

void setup()
{
  	// we can use also DDRD register, but in order to make a difference with previous experiments, we use pinMode functioın
	pinMode(a,OUTPUT); // pin a as output because we use its value to show on seven segment 
    pinMode(b,OUTPUT); // pin b as output because we use its value to show on seven segment
  	pinMode(c,OUTPUT); // pin c as output because we use its value to show on seven segment
  	pinMode(d,OUTPUT); // pin d as output because we use its value to show on seven segment
  	pinMode(e,OUTPUT); // pin e as output because we use its value to show on seven segment
  	pinMode(f,OUTPUT); // pin f as output because we use its value to show on seven segment
  	pinMode(g,OUTPUT); // pin g as output because we use its value to show on seven segment
  	pinMode(pnp,OUTPUT); // pin pnp as output because we use its value to show on seven segment
  	
}

void loop()
{
  	value = analogRead(POT); // reading potentiometers value from analogRead and store its value in value
  	ones_digit = value % 10; // we evaulate ones_digit which equals remainder of value / 10
  	PORTB = B000000; // BJT's Base should be low in order to showing results on seven segment
  
  	PORTD = number_patterns[ones_digit]; //according to ones_digit we return a value in number_patterns and show it on seven segment
  	millis(); // delay

}
