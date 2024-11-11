#include <LPC17xx.h>

unsigned long int i=0;
unsigned int j=0;

int main()
{
	unsigned char seven_seg[16] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	LPC_PINCON-> PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0-> FIODIR |= 0xFF<<4;
	LPC_GPIO1-> FIODIR=0xFFFFFFFF;

	while(1){
		LPC_GPIO0->FIOPIN = seven_seg[i]<<4;
		for(j=0;j<5000000;j++);
		i=(i+1)%16;
	}
						
}
