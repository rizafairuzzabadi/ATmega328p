/*int B=9,C=10,D=11,A=8;
int i = 0;


void setup()
{
	DDRB |= B001111; 
  	DDRC |= 0xFF;
}

void loop()
{
  
  if (PINB & B00010000){
  	PORTB = i % 10;
    PORTC = (i - (i % 10))/10; 
    delay(500);
    i++;
  }
  
  if (PINB & B00100000){
  	  
    PORTB = i % 10;
    PORTC = (i - (i % 10))/10; 
    delay(500);
    i--;
  }

}*/



void setup()
{
  asm(
"		JMP start				\n"
"delay: LDI	 r23,  20			\n"	//Delay 1 sec
"w1:	LDI	 r24,  255 			\n"
"w2:	LDI  r25,  255 			\n"
"w3:	DEC  r25  				\n"
"		BRNE w3					\n"
"		DEC  r24				\n"
"		BRNE w2					\n"
"		DEC  r23				\n"
"       BRNE w1					\n"
"		RET						\n"
";Your Functions Code Begin		\n" //Write your code   
/* 
"updateRegister:				\n"
"		IN	 r16,  0x03			 \n"
"       ANDI r16,  0b00110000   \n"
"		JMP LOOP				\n"
"sub:							\n"
"		IN	 r16,  0x03			 \n"
"       ANDI r16,  0b00110000   \n"
"		RET						\n"

sub Function was supposed to be called in each counting function but it gives compiler error.

*/

    

    
"countUp:						\n"
"       LDI r17,  0b1001        \n" // loading decimal 9 value to r17 register to compare with ones digit
"		CP  r19,  r17	    	\n" // comparing r19-r17(9) ---if the ones digit is 9, after the incrementation tens digit should increment and ones digit becomes zero
"		BREQ countUp2			\n" // if ones digit is 9 branch countUp2 func
"       BRNE countUp1           \n" // else branch countUp1 func 
"countUp1:                      \n"
"       INC  r19                \n" // increment operation
"		OUT  0x05, r19			\n" // PORTB <- r19
"		OUT  0x08, r20			\n" // PORTC <- r20
"		CALL delay				\n"	// calling delay function
"		JMP  LOOP				\n" //
"countUp2:						\n" //since ones digit is 9 we cannot apply previous funtion anymore. so we branching countUp2 funtion
"		LDI	 r19,  0b0000	    \n" // r19 which denotes ones digit assigning to 0
"       INC  r20                \n"	// r20 which denotes tens digit should increment
"		OUT  0x08, r20			\n" // PORTC <- r20 
"		OUT  0x05, r19			\n" // PORTB <- r19
"       CALL delay              \n" // delay
"		JMP  LOOP				\n" // jumping to loop
"countDown:						\n"	
"       LDI r17,  0b0000        \n" //loading decimal 9 value to r17 register to compare with ones digit
"		CP  r19,  r17	    	\n" //compare r19 - r17(9)--if the ones digit is 0, after the decrementation tens digit should decrement and ones digit becomes nine
"		BREQ countDown2         \n" // if ones digit is 0, then branch countDown2 func
"       BRNE countDown1         \n" // else branch countDown1 func
"countDown1:                    \n"
"       DEC  r19                \n" // decrement operation
"		OUT  0x05, r19			\n" // PORTB <- r19
"		OUT  0x08, r20			\n" // PORTC <- r20
"		CALL delay				\n"	//
"		JMP  LOOP				\n"
"countDown2:					\n" // since ones digit is 9 we cannot apply previous funtion anymore. so we branching countDown2 funtion
"		LDI	 r19,  0b1001	    \n" // r19 which denotes ones digit assigning to 9
"       DEC  r20                \n" // r20 which denotes tens digit should decrement
"		OUT  0x08, r20			\n" // PORTC <-r20
"		OUT  0x05, r19			\n" // PORTB <- r19
"       CALL delay				\n"
"       JMP LOOP                \n"
";Your Functions Code End		\n" 
"								\n"    
"start:							\n" //Write your code
";Your Setup Code Begin			\n"    
"		IN 	 r19,  0x04 ;		\n" //r19 <- DDRD   
"		ORI	 r19,  0b001111;	\n"	//r19 || 0b001111
"		OUT  0x04, r19			\n" //DDRD <- r19
"       IN   r20,  0x07         \n"  // r20 <- DDRC
"       ORI  r20,  0b11111111;  \n"  // r19 || 0xFF
"       OUT  0x07, r20          \n"  // DDRC <- r20
";Your Setup Code End			\n" 
  );

}

void loop()
{
  asm(
"       IN   r19,  0x05 ;       \n" // portB value assigning to r19 for avoiding uncertainity     
"     	ORI	 r19,  0b0000       \n" // r19 = 0b0000 
"		OUT  0x05, r19          \n" // portB = r19 where r19 = 0000, because in first, seven segment display should show 00
"       IN   r20,  0x08 ;       \n" // portC value assigning to r19 for avoiding uncertainity 
"     	ORI	 r20,  0b0000       \n" // r20 = 0b0000
"		OUT  0x08, r20          \n" // portC = r20 where r20 = 0000, because in first, seven segment display should show 00
// "		IN	 r16,  0x03			 \n" this functionality give comipler error
// "       ANDI r16,  0b00110000   \n"
"LOOP:							\n"//Write your code
";Your LOOP Code Begin			\n" 
"       IN   r18,  0x03;        \n" // r18<-pinB pinB writing to r18 register
"       ANDI r18,  0b00110000   \n" // r18 evaluating for understand buttons' position
// "		CP	 r16,  r18			\n" tried to stop counting when button is held
// "		BREQ updateRegister		\n" this functionality gives compiler error

"       LDI  r17,  0b00010000   \n"    
"		CP   r18,  r17			\n"	// checking if first button presesed
" 		BREQ countUp			\n" // if first button pressed we should make increment operation (inc1)
"       LDI  r17,  0b00100000   \n"    
"       CP   r18,  r17   		\n" // checking if second button presesed
"       BREQ countDown        	\n" //if second button pressed we should make decrement operation (dec1)
"       LDI  r17,  0b00000000   \n"    
"       CP  r18,  r17   		\n" //if non of them pressed, it must go to beginning of the loop which means system is stable
"       BREQ LOOP               \n"
";Your LOOP Code End			\n" 
"		JMP  LOOP				\n"
  );
  
}