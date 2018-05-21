#include "AT91SAM9263.h"
#include "AT91SAM9263-EK.h"

#define A 1<<25
#define B 1<<24
#define C 1<<22
#define D 1<<21
#define E 1<<20
#define F 1<<27
#define G 1<<26
#define H 1<<23
#define CLOCK 1<<4 //needed?
#define BUTTON 1<<5
#define LEFT 1<<28
#define RIGHT 1<<30
//#define ALL 1<<31

const int decoder[10] = 
{

        A|B|C|D|E|F,
        B|C,
        A|B|G|E|D,
        A|B|G|C|D,
        F|G|B|C,
        A|F|G|C|D,
        A|F|E|D|C|G,
        A|B|C,
        A|B|C|D|E|F|G,
        A|B|C|D|F|G
};

void initLED()
{
	//lights
	AT91C_BASE_PIOB->PIO_PER = (A|B|C|D|E|F|G|H|LEFT|RIGHT/*|ALL*/);
    AT91C_BASE_PIOB->PIO_OER = (A|B|C|D|E|F|G|H|LEFT|RIGHT/*|ALL*/);
	AT91C_BASE_PIOB->PIO_CODR = (A|B|C|D|E|F|G|H|LEFT|RIGHT/*|All*/);
    AT91C_BASE_PIOB->PIO_SODR = (TRight|TLeft);
	
}

void initCLOCK()
{
	//clock
	AT91C_BASE_PMC->PMC_PCER = CLOCK;
}

void initBUTTON()
{
	//button
	AT91C_BASE_PIOC->PIO_ODR = BUTTON;
	AT91C_BASE_PIOC->PIO_PPUER = BUTTON;
}
void clear()
{
        AT91C_BASE_PIOB->PIO_CODR=(A|B|C|D|E|F|G|H);
}

void on(int a)
{

        AT91C_BASE_PIOB->PIO_SODR = a;
}

void off(int a)
{

        AT91C_BASE_PIOB->PIO_CODR = a;
}

void delay(int a)
{
        volatile int i;
        for(i=0;i<a;i++);
}

void leftON()
{
	PIOB->PIO_CODR = (LEFT);
}

void leftOFF()
{
	PIOB->PIO_SODR = (LEFT);
}

void rightON()
{
	PIOB->PIO_CODR = (RIGHT);
}

void rightOFF()
{
	PIOB->PIO_SODR = (RIGHT);
}

/*
void buttonON()
{
	return(!AT91C_BASE_PIOC->PIO_PDSR & 1<<5);
}
*/

int main()
{
		volatile int iterator_p=0;
		volatile int iterator_l=0;
		initCLOCK();
        initLED();
		initBUTTON();

		
        while(1)
        {	
			clear();
			leftON();
			on(decoder[iterator_l]);
			leftOFF();
			rightON();
			on(decoder[iterator_p]);
			rightOFF();
			delay(500000);
			if(!AT91C_BASE_PIOC->PIO_PDSR & 1<<5)//if(buttonON())
			{
				iterator_p--;
				if(iterator_p<0)
				{
					iterator_p=9;
					iterator_l--;
					if(iterator_l<0 && iterator_p<0)
					{
						iterator_p = 0;
						iterator_l = 0;
					}
				}
			}
			else
			{
				iterator_p++
				if(iterator_p>9)
				{
					iterator_p=0;
					iterator_l++;
					if(iterator_l>9 && iterator_p>9)
					{
						iterator_p = 9;
						iterator_l = 9;
					}
				}
			}
        }


}

void dbgu_print_ascii(const char* string){}
