#include "AT91SAM9263.h"

#define A 1<<25
#define B 1<<24
#define C 1<<22
#define D 1<<21
#define E 1<<20
#define F 1<<27
#define G 1<<26
#define H 1<<23
//#define CLOCK 1<<4 //needed?
#define BUTTON 1<<5
#define LEFT 1<<28
#define RIGHT 1<<30
#define ALL 1<<31
#define TIME 500

const int decoder[10] = 
{

        A|B|C|D|E|F,	//0
        B|C,		//1
        A|B|G|E|D,	//2
        A|B|G|C|D,	//3
        F|G|B|C,	//4
        A|F|G|C|D,	//5
        A|F|E|D|C|G,	//6
        A|B|C,		//7
        A|B|C|D|E|F|G,	//8
        A|B|C|D|F|G	//9
};

void initLED()
{
	//lights
	AT91C_BASE_PIOB->PIO_PER = (A|B|C|D|E|F|G|H|LEFT|RIGHT|ALL);
    	AT91C_BASE_PIOB->PIO_OER = (A|B|C|D|E|F|G|H|LEFT|RIGHT|ALL);
	AT91C_BASE_PIOB->PIO_CODR = (A|B|C|D|E|F|G|H|ALL);
   	AT91C_BASE_PIOB->PIO_SODR = (RIGHT|LEFT);
	
}
/*
void initCLOCK()
{
	//clock
	AT91C_BASE_PMC->PMC_PCER = CLOCK;
}
*/
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
	AT91C_BASE_PIOB->PIO_CODR = (LEFT);
}

void leftOFF()
{
	AT91C_BASE_PIOB->PIO_SODR = (LEFT);
}

void rightON()
{
	AT91C_BASE_PIOB->PIO_CODR = (RIGHT);
}

void rightOFF()
{
	AT91C_BASE_PIOB->PIO_SODR = (RIGHT);
}

/*
void buttonON()
{
	return(!AT91C_BASE_PIOC->PIO_PDSR & 1<<5);
}
*/

void display(int a, int b)
{
  volatile int yolo=0;
	for(yolo = 0;yolo<100;yolo++)
	{
        clear();
	rightON();
        on(decoder[b]);
        delay(6250);
        off(decoder[b]);
	delay(6250);	
	rightOFF();
	clear();
	leftON();
        on(decoder[a]);
        delay(6250);
	off(decoder[a]);	
	delay(6250);
	leftOFF();
	}
        
}

int main()
{
		volatile int iterator=0;
		//initCLOCK();
        	initLED();
		initBUTTON();

		
        while(1)
        {
		
		display(iterator/10,iterator%10);
                if(!(AT91C_BASE_PIOC->PIO_PDSR & BUTTON))
                        iterator--;
                else
                        iterator++;
                if(iterator>99)
                        iterator=99;
                if(iterator<0)
                        iterator=0;
		
        }


}

void dbgu_print_ascii(const char* string){}
