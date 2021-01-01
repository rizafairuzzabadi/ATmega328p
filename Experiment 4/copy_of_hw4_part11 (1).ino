//Part #1

int R = 6; //pin for red LED
int G = 3; //pin for green LED
int B = 5; //pin for blue LED

int potencioGreen= A2; // input pins of potenciometers 
int potencioBlue= A1; 
int potencioRed= A0;  



void setup() {
	pinMode(R,OUTPUT); //setting 3 5 6 pins as output
    pinMode(G,OUTPUT);
    pinMode(B,OUTPUT);
    pinMode(potencioGreen,INPUT); // setting A0 A1 A2 pins as input
    pinMode(potencioBlue,INPUT);
    pinMode(potencioRed,INPUT);
  	//Serial.begin(115200);
}
void loop() {
  	
  	int r = analogRead(potencioRed); // reading from potenciometers
    int g = analogRead(potencioGreen);
    int b = analogRead(potencioBlue);
  	//Serial.println(g);
  	//r = r / 4; if map function is not allowed, this is a way to preprocess.
	//g = g / 4;
 	//b = b / 4;
  	//Serial.println(g);
  	r = map(r, 0, 1023, 0, 255); // mapping from analogRead to analogWrite
  	g = map(g, 0, 1023, 0, 255);
  	b = map(b, 0, 1023, 0, 255);
  	analogWrite(R, r); // writing the preprocessed values to RGB output pins
 	analogWrite(G, g);
  	analogWrite(B, b);
}


