#include <LPC17xx.h>

unsigned int i=0;
unsigned int j=0;
unsigned char x=0;
unsigned long y=0;

void up(){
	for(i=0; i<8; i++){
		LPC_GPIO0->FIOPIN = x<<4;
		x++;
		for(j=0; j<1000; j++);
	}
}
						
void down(){
	for(i=0; i<8; i++){
		LPC_GPIO0->FIOPIN = x<<4;
		x--;
		for(j=0; j<1000000; j++);
	}
}

int main(){
	LPC_PINCON-> PINSEL0 &= 0xFF0000FF;
	LPC_PINCON-> PINSEL3 &= 0x00;
	LPC_GPIO0-> FIODIR |= 0xFF<<4;		
	LPC_GPIO2-> FIODIR = 0;

	while(1){
		y = LPC_GPIO2->FIOPIN & 1;
		if(y)
			up();
		else
			down();
	}	
}
