void dbgu_print_ascii(const char* string){}

#define PIOB_PER (volatile unsigned int * const) 0xFFFFF400 //PIO Controller PIO Enable Register
#define PIOB_OER (volatile unsigned int * const) 0xFFFFF410 //PIO Controller Output Enable Register
#define PIOB_CODR (volatile unsigned int * const) 0xFFFFF434 //PIO Controller Clear Output Data Register
#define PIOB_SODR (volatile unsigned int * const) 0xFFFFF430 //PIO Controller Set Output Data Register

#define PIOC_ODR (volatile unsigned int * const) 0xFFFFF614 //PIO Controller Output Disable Register
#define PIOC_PUER (volatile unsigned int * const) 0xFFFFF664 //PIO Pull Up Enable Register
#define PMC_PCER (volatile unsigned int * const) 0xFFFFFC10 //PMC Peripheral Clock Enable Register !!!!!!!!!!!!!
#define PIOC_PDSR (volatile unsigned int * const) 0xFFFFF63C //PIO Controller Pin Data Status Register


#define time 2500000

void delay(int x)
{
	volatile unsigned int i=0;
	for(i=0;i<x;i++)
	{
		if(!(*PIOC_PDSR & 1<<5)) 
			break; //niwelowanie opĂłĹşnienia
	}
}



int main()
{

//Zegar
*(PMC_PCER) = 1<<4; //wĹaczenie zegara

//Dioda
*(PIOB_PER) = 1<<8; //wlaczenie PIO enable register
*(PIOB_OER) = 1<<8; //ustawienie output enable register, pozwala ustawiac 1/0

//Przyciski
*(PIOC_ODR) = 1<<5; //ustawienie output disable register
*(PIOC_PUER) = 1<<5; 




while(1)
{	
	if(!(*PIOC_PDSR & 1<<5)) //sprawdzenie czy wcisniety
	{
		*(PIOB_CODR) = 1<<8; //wlaczenie diosy
	}

	else
	{	
		*(PIOB_SODR) = 1<<8;
		delay(time);
		*(PIOB_CODR) = 1<<8; 	
		delay(time);
		
		
	}
}
}
