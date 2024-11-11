#include <LPC17xx.h>

unsigned int i;
unsigned int j;

int main()
{
	LPC_PINCON->PINSEL0 &= 0x3FFFFFFF;
	LPC_PINCON->PINSEL1 &= 0xFFFFC000;
	LPC_GPIO0-> FIODIR |= 0x007F8000; // OR 0xFF << 15
		
	while(1) {
		// ON the LEDs serially
		for(i=0; i<8; i++){
			LPC_GPIO0->FIOSET = 1<<(i+15);
			for(j=0; j<1000; j++);
		}
	
		// OFF the LEDs serially
		for(i=0; i<8; i++){
			LPC_GPIO0->FIOCLR = 1<<(i+15);
			for(j=0; j<1000; j++);
		}		
	}	
}
