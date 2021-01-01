int disp_values [4] = {0, 0, 0, 0};
int screen_selector = 0; // this selects which display is on at the moment, it switches rapidy to give the ilusion of all of them being on at the same time
unsigned long display_time = 0; // this keeps track of switching displays, it is used with millis
unsigned long increment_time = 0; // keeps track of leftmost display incrementing every second
int mili = 5; // used with display time, screens are turned on and of every 5 milliseconds
int digit_increase = 200; // digits increase every 200 ms
int players_turn = 1; // which players turn it is
int first_player_value = -1; // initialize with negative values so first player can't cheat by instantly clicking
int second_player_value = -2;
// theese arrays hold the required values to send to PORTD and PORTB to display the number, for example arrayD[10] is the required binary number to send to PORD to display A.
byte arrayD[] = {B00010000,B11110000,B00100000,B01100000,B11000000, B01000000,B00000000, B11110000, B00000000,B01000000, B10000000, B00000000, B00010000, B00100000, B00000000, B10000000};
byte arrayB[] = {B000000,B000100,B000001,B000000, B000100, B000010,B000010, B000000, B000000, B000000, B000000, B000110,B000011, B000100, B000011, B000011};

void select_first() // players value is updated and turn is passed
{
	players_turn = 2;
    first_player_value = 10* disp_values[0] + disp_values[1];
}
void select_second() // players value is updated and turn is passed
{
	players_turn = 1;
    second_player_value = 10* disp_values[2] + disp_values[3];
}


void Display(int x, int y){ // displays x value on y'th screen

    PORTD = arrayD[x];
    PORTB = arrayB[x];

    if(y == 1) // display on first screen
       PORTC = B011100;
    if(y == 2)// display on second screen
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
  attachInterrupt(digitalPinToInterrupt(2), select_first, RISING); // when first button is clicked select_first function runs
  attachInterrupt(digitalPinToInterrupt(3), select_second, RISING);// when second button is clicked select_second function runs
}


void loop()
{

  if(first_player_value != second_player_value) // this is executed as long as players values don't match
  {
    
    if (millis() >= (increment_time + digit_increase) && players_turn == 1) // first players part increments when it is first players turn 
    { 
      disp_values[1]++; // increment the ones digit for player 1
      
      if(disp_values[1] == 10) // if ones digit exceeds 9
      {
      	disp_values[1] = 0; // set 1s digit to 0
        disp_values[0]++; // increment 10s digit
      }
      
      if(disp_values[1] == 1 && disp_values[0] == 2) // if number exceeds 20 (becomes 21)
      {
      	disp_values[1] = 1; // set counter to 01 since game is between 1-20
        disp_values[0] = 0;
      }
      increment_time += digit_increase; // time is incremented by 1 second after every second passes
    }

     if (millis() >= (increment_time + digit_increase) && players_turn == 2){ // second players part increments when it is second players turn
      disp_values[3]++; // increment the ones digit for player 2
      
      if(disp_values[3] == 10) // if ones digit exceeds 9
      {
      	disp_values[3] = 0; // set 1s digit to 0
        disp_values[2]++; // increment 10s digit
      }
       
       if(disp_values[3] == 1 && disp_values[2] == 2) // if number exceeds 20 (becomes 21)
      { 
      	disp_values[2] = 0; // set counter to 01 since game is between 1-20
        disp_values[3] = 1;
      }
       
      increment_time += digit_increase; // time is incremented by 1 second after every second passes
    }
    

    if (millis() >= (display_time + mili)) // turns on a certain display every 5 milliseconds, it switches rapidy to give the ilusion of all of them being on at the same time
    { 
      Display(disp_values[screen_selector],screen_selector+1); // display the matching value on a screen
      display_time += mili;
      screen_selector++; // screen selector is increased by 1 to go to next screen
      screen_selector = screen_selector % 4; // modulus to periodize throgh 0-1-2-3
    }
  }
  
  else if( players_turn == 1) // player 2 won if turn passed to 1
  {
    disp_values [0] = 2;
    disp_values [1] = 2;
    disp_values [2] = 2;
    disp_values [3] = 2;
  	if (millis() >= (display_time + mili)) // turns on a certain display every 5 milliseconds, it switches rapidy to give the ilusion of all of them being on at the same time
    { 
      Display(disp_values[screen_selector],screen_selector+1); // display the matching value on a screen
      display_time += mili;
      screen_selector++; // screen selector is increased by 1 to go to next screen
      screen_selector = screen_selector % 4; // modulus to periodize throgh 0-1-2-3
    }
  }
  
  else // player 1 won if turn passed to 2
  {
    disp_values [0] = 1;
    disp_values [1] = 1;
    disp_values [2] = 1;
    disp_values [3] = 1;
  	if (millis() >= (display_time + mili)) // turns on a certain display every 5 milliseconds, it switches rapidy to give the ilusion of all of them being on at the same time
    { 
      Display(disp_values[screen_selector],screen_selector+1); // display the matching value on a screen
      display_time += mili;
      screen_selector++; // screen selector is increased by 1 to go to next screen
      screen_selector = screen_selector % 4; // modulus to periodize throgh 0-1-2-3
    }
  }
}

 
