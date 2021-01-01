byte arrayD[] = {B00010000,B11110000,B00100000,B01100000,B11000000, B01000000,B00000000, B11110000, B00000000,B01000000, B10000000, B00000000, B00010000, B00100000, B00000000, B10000000};
byte arrayB[] = {B000000,B000100,B000001,B000000, B000100, B000010,B000010, B000000, B000000, B000000, B000000, B000110,B000011, B000100, B000011, B000011};

// this keeps track of switching displays, it is used with millis
// keeps track of leftmost display incrementing every second
int screen_selector = 0; // this selects which display is on at the moment, it switches rapidy to give the ilusion of all of them being on at the same time
int counter = 0;
int ones_digit = counter % 10;
int tens_digit = (counter % 100) /10;
int hundreds_digit = (counter % 1000) / 100;
int thousands_digit = counter / 1000;
int begin = -1;
int lap_timer = 0;
int lap_count = 1;

int dela = 2;
int time = 0;

void print_lap() // print the lab information and reset lab timer.
{
  	 Serial.print("Lap number: ");
  	 Serial.println(lap_count);
  	 lap_count++;
	 Serial.print("Lap time: ");
  	 Serial.println(lap_timer);
	 lap_timer = 0;
  	 Serial.print("Total time: ");
  	 Serial.println(counter);
}


void start()
{ 
	begin *= -1;	
}

void setup()
{

  DDRD |= 0b11110000; // setup required inputs and outputs
  DDRC |= 0b111111;
  DDRB |= 0b011111;

  cli();        // disable all interrupts

  TCCR1A = 0; 
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 624;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode active
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  
  /*
  TCCR0A = 0;	// reset used registers
  TCCR0B = 0;	//
  TCNT0 = 0;	//
  OCR0A = 124;	// 16Mhz  * 10^6 / 10^3* ( prescscaler) compare value = 124 -> 2ms
  TCCR0A  |= (1 << WGM01); // CTC active
  TCCR0B |= (1 << CS01)| (1 << CS00);	// prescaler  = 64
  TIMSK0 |= (1 << OCIE0A) ;
  */
  
  
  attachInterrupt(digitalPinToInterrupt(2), start, RISING); // when first button is clicked select_first function run 
  attachInterrupt(digitalPinToInterrupt(3), print_lap, RISING);
  sei();  // enable all interrupts
  Serial.begin(9600);
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

ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{	
  
  if(begin == 1){ // if first button is clicked.
	counter += 1; // counter increases every centi second
    lap_timer += 1;
	ones_digit = counter % 10;
	tens_digit = (counter % 100) /10;
	hundreds_digit = (counter % 1000) / 100;
	thousands_digit = counter / 1000;
  }
  if((PINB & B100000) == B100000){ // reset button
    lap_count = 1;
	lap_timer = 0;
    counter = 0;
  }
}

/*
ISR(TIMER0_COMPA_vect)
{
  	 // turns on a certain display every 2 milliseconds, it switches rapidy to give the ilusion of all of them being on at the same time
      // display the matching value on a screen
      if(screen_selector == 0)
      	Display(thousands_digit, screen_selector+1);
      else if(screen_selector == 1)
        Display(hundreds_digit, screen_selector+1);
      else if(screen_selector == 2)
        Display(tens_digit, screen_selector + 1);
      else
        Display(ones_digit, screen_selector + 1);
        
      screen_selector++; // screen selector is increased by 1 to go to next screen
      screen_selector = screen_selector % 4; // modulus to periodize throgh 0-1-2-3
}
*/

void loop() // display was handled outside of loop() using timer0 interrrupt and commented
{			// if loop() prohibited those comments can be used;
  if(millis() >= time)// display handled inside loop
  {
  	time += dela;
      
    if(screen_selector == 0)      	
      Display(thousands_digit, screen_selector+1);      
    else if(screen_selector == 1)    
      Display(hundreds_digit, screen_selector+1);   
    else if(screen_selector == 2)
      Display(tens_digit, screen_selector + 1);
    else
      Display(ones_digit, screen_selector + 1);
        
      screen_selector++; // screen selector is increased by 1 to go to next screen
      screen_selector = screen_selector % 4; // modulus to periodize throgh 0-1-2-3
    
  }
}


