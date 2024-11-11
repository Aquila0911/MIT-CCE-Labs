#include <LPC17xx.h>

unsigned char seven_seg[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x3C, 0x39, 0x5E, 0x79, 0x71};
unsigned int i, j;

void delay(){
	for(j=0; j<100; j++);
}

int main()
{
	LPC_PINCON->PINSEL0 = 0;
	LPC_GPIO0->FIODIR = 0x00000FF0;
	
	while(1){
		LPC_GPIO0->FIOPIN = seven_seg[i]<<4;
		delay();
		i = (i+1)%16;
	}
}
