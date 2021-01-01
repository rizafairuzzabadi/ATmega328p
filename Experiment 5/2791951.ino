int disp_values [4] = {0, 0, 0, 0};
int choosen_value = 432; // player tries to guess this number
int screen_selector = 0; // this selects which display is on at the moment, it switches rapidy to give the ilusion of all of them being on at the same time
unsigned long display_time = 0; // this keeps track of switching displays, it is used with millis
unsigned long increment_time = 0; // keeps track of leftmost display incrementing every second
int mili = 5; // used with display time, screens are turned on and of every 5 milliseconds
int second = 1000; // leftmost is updated every second


// theese arrays hold the required values to send to PORTD and PORTB to display the number, for example arrayD[10] is the required binary number to send to PORD to display A.
byte arrayD[] = {B00010000,B11110000,B00100000,B01100000,B11000000, B01000000,B00000000, B11110000, B00000000,B01000000, B10000000, B00000000, B00010000, B00100000, B00000000, B10000000};
byte arrayB[] = {B000000,B000100,B000001,B000000, B000100, B000010,B000010, B000000, B000000, B000000, B000000, B000110,B000011, B000100, B000011, B000011};

void select() // selects and slides display values when button is pushed,
{
    disp_values[3] = disp_values[2]; 
    disp_values[2] = disp_values[1];
    disp_values[1] = disp_values[0];
}

void Display(int x, int y){ // displays x value on y'th screen

    PORTD = arrayD[x];
    PORTB = arrayB[x];

    if(y == 1) // display on first screen
       PORTC = B011100;
    if(y == 2)// display on second screenatching value
       PORTC = B101100;
    if(y == 3) // display on third screen
       PORTC = B110100;
    if(y == 4) // display on fourth screen
       PORTC = B111000;
}

void setup()
{
  DDRD |= 0b11110000; // setup required inputs and outputs
  DDRC |= 0b111111;
  DDRB |= 0b111111;
  attachInterrupt(digitalPinToInterrupt(2), select, RISING); //set the interrupt function
}


void loop()
{

  int current_value = 100*disp_values[1] + 10*disp_values[2] + disp_values[3]; // value guessed is disp_values[1] for hundreds digit, disp_values[2] for tens digit and so on
  if(choosen_value != current_value)
  {
    if (millis() >= (increment_time + second)){ // if is executed once every second
      disp_values[0]++; // 1st screen is incremented once every second
      if(disp_values[0] > 15)	//1st screen value goes back to 0 after F
		disp_values[0] = 0;
      increment_time += second; // time is incremented by 1 second after every second passes
    }


    if (millis() >= (display_time + mili)) { // turns on a certain display every 5 milliseconds, it switches rapidy to give the ilusion of all of them being on at the same time
      Display(disp_values[screen_selector],screen_selector+1); // display the matching value on a screen
      display_time += mili;
      screen_selector++; // screen selector is increased by 1 to go to next screen
      screen_selector = screen_selector % 4; // modulus to periodize throgh 0-1-2-3
    }
  }
}

 
