int Sn; // 
int Sn1 = 1; // random nums.
int Sn2 = 1; // random nums
int flag = 0; // default 0 flag we change it when user gives an input 
String str_m = "";
int m;
int* random_values;


int get_int(String angle){ // string to integer function, we explain this in masterMC's code
  	//Serial.print("Inside:");
  	//Serial.println(angle);
    int i = 0;
    int total1 = 0;
  while (angle[i] != '\0') {
    i++;
  }
  int k = i;
  for(k=i;k>0;k--){
   int temp = angle[k-1] - '0';
   int mult = (pow(10,i-k) + 0.5);
   int mult2 = mult * temp;
   total1 += mult2;
  }
  if( total1 > 180){ // problem with tinkercad, when casting int to string.
  	total1 = 180;
  }
  //Serial.println(total1);
  return total1;
}


void setup()
{
    DDRD = 0b11000000; // setup required inputs and outputs
    DDRB |= 0b011111;
	cli();//stop interrupts
  	TCCR1A = 0;// set entire TCCR1A register to 0
  	TCCR1B = 0;// same for TCCR1B
 	 TCNT1  = 0;//initialize counter value to 0
 	 OCR1A = 15624; // 
 	 // turn on CTC mode
 	 TCCR1B |= (1 << WGM12);
 	 // Set CS11 for 8 prescaler
 	 TCCR1B |= (1 << CS11);
 	 // enable timer compare interrupt
  	TIMSK1 |= (1 << OCIE1A);
  	sei();//allow interrupt
  	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(3), generate_m, RISING); // when button is rising invoke generate_m function
}

void loop()
{
	
}

int generate()
{
	int sum = Sn1 +  Sn2; // randomly generated values
  	Sn = sum % 8; // number's range is given as [0-7] so, mod 8
  	//  Sn'i ekrana ver
  	Sn2 = Sn1; // lagged fibonacci random value generation opeartions
  	Sn1 = Sn;
  	return Sn;
  	
}

ISR(TIMER1_COMPA_vect) // timer interrupt
{
    interrupts(); // in order to read values from Serial monitor, we need to invoke this function
  	if(flag == 0)
    {
      	Serial.println("Please enter m number");
    	flag = 1;
    }
  
	while(Serial.available() > 0)  // waits user input
    {
    	char c  = Serial.read(); // user gives a value and read it char by char
      	str_m += c; // given input stored in str_m as string
    }
    m = str_m.toInt();  // string to int operation that created by us        


}
                       
void generate_m()
{
	random_values = (int*) malloc(sizeof(int) * m); // dynamically allocate according to user input
  	for (int i = 0; i < m; i++)
    {
      random_values[i] = generate(); // get a random value and store it into random_values array
	  random_values[i] = random_values[i]; // bunu silince çalışmıyor
    }
  
  	int count0 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 0 == random_values[i]){
      	count0++; // count number of 0's that we encountered
      }  
    }
    int	count1 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 1 == random_values[i]){
      	count1++; // count number of 1's that we encountered
      }  
    }
    int	count2 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 2 == random_values[i]){
      	count2++; // count number of 2's that we encountered
      }  
    }
  
  	int	count3 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 3 == random_values[i]){
      	count3++; // count number of 3's that we encountered
      }  
    }
  	int	count4 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 4 == random_values[i]){
      	count4++; // count number of 4's that we encountered
      }  
    }
  	int	count5 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 5 == random_values[i]){
      	count5++; // count number of 5's that we encountered
      }  
    }
  	int	count6 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 6 == random_values[i]){
      	count6++; // count number of 6's that we encountered
      }  
    }
  	int	count7 = 0; // 0 times encountered at the beginning
  	for (int i = 0; i < m; i++)
    {      	
      if( 7 == random_values[i]){
      	count7++; // count number of 7's that we encountered
      }  
    }

  int counts[] = { count0, count1, count2, count3, count4, count5, count6, count7}; // stores values of numbers that how many times counted

	for(int i = 0; i < 8; i++) // print to serial monitor
    {
      Serial.print(i);
      Serial.print(" was generated ");
      Serial.print(counts[i]);
      Serial.print(" times \n");
    }

	free(random_values); // delete from memory


}