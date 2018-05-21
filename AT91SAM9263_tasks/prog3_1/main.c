#include "AT91SAM9263.h"

#define A 1<<25
#define B 1<<24
#define C 1<<22
#define D 1<<21
#define E 1<<20
#define F 1<<27
#define G 1<<26
#define H 1<<23

void initLED()
{
	AT91C_BASE_PIOB->PIO_PER = (A|B|C|D|E|F|G|H);
        AT91C_BASE_PIOB->PIO_OER = (A|B|C|D|E|F|G|H);
}

void wyczysc()
{
        AT91C_BASE_PIOB->PIO_CODR=(A|B|C|D|E|F|G|H);
}

void on(int a)
{

        AT91C_BASE_PIOB->PIO_SODR = a;
}

void delay(int a)
{
        volatile int i;
        for(i=0;i<a;i++);
}


int main()
{
        int decoder[10];
        decoder[0] = A|B|C|D|E|F;
        decoder[1] = B|C;
        decoder[2] = A|B|G|E|D;
        decoder[3] = A|B|G|C|D;
        decoder[4] = F|G|B|C;
        decoder[5] = A|F|G|C|D;
        decoder[6] = A|F|E|D|C|G;
        decoder[7] = A|B|C;
        decoder[8] = A|B|C|D|E|F|G;
        decoder[9] = A|B|C|D|F|G;

        initLED();
        volatile int iterator_p=0;
        while(1)
        {
                wyczysc();
                on(decoder[iterator]);
                delay(1000000);
                iterator_p++;
                if(iterator_p>9)
			iterator_p=0;
		
        }


}

void dbgu_print_ascii(const char* string){}
