void setup()
{
  asm(
"		JMP start				\n"
"delay: LDI	 r23,  81			\n"	//Delay 1 sec
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
"								\n"	
";Your Functions Code End		\n" 
"								\n"    
"start:							\n" //Write your code
";Your Setup Code Begin			\n"    
"		IN 	 r16,  0x0A ;		\n" //r16 <- DDRD   
"		ORI	 r16,  0b11111111	\n"	//r16[0] <- 0b11111111
"		OUT  0x0A, r16			\n" //DDRD <- r16   
";Your Setup Code End			\n" 
  );

}

void loop()
{
  asm(
"LOOP:							\n"//Write your code
";Your LOOP Code Begin			\n"    
"	LDI		r17,	0b00000001 		\n"  // r17 <- 00000001 	
"	LDI		r16,	0b10000000		\n" // r16 <- 10000000
"	OUT		0x0B,	r17			\n"
"	CALL	delay				\n"
"Incrementation:				\n"
"	LSL		r17					\n" // r17 <- r17+1
"	OUT		0x0B,	r17			\n" // PORTD <- r17
"	CALL	delay				\n"
"	CPSE	r16,	r17			\n" // compare r17 and r16, don't jump to incrementation if equal
"	JMP		Incrementation"	
";Your LOOP Code End			\n" 
"		JMP  LOOP				\n"
  );
  
}