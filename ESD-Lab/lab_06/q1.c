#include <LPC17xx.h>

unsigned int j;
unsigned char x=0;

int main()
{
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	
	while(1){
		LPC_GPIO0->FIOPIN = x<<4;
		for(j=0; j<100; j++);
		x++;
	}
}
