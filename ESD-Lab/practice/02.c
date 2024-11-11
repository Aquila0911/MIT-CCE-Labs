#include <LPC17xx.h>

unsigned int dig_count;
unsigned int dig_value[5] = {0, 4, 3, 2, 1};
unsigned int select_segment[5] = {0, 0<<23, 1<<23, 2<<23, 3<<23};
unsigned int temp1, temp2, i=0;
unsigned char seven_seg[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x3C, 0x39, 0x5E, 0x79, 0x71};

void delay(){
	for(i=0; i<100; i++);
}

void display(){
	LPC_GPIO1->FIOPIN = select_segment[dig_count];
	LPC_GPIO0->FIOPIN = seven_seg[dig_value[dig_count]]<<4;
	for(i=0; i<500; i++);
	LPC_GPIO0->FIOCLR = 0x00000FF0;
}

int main()
{
	LPC_PINCON->PINSEL0 = 0;
	LPC_PINCON->PINSEL3 = 0;
	LPC_GPIO0->FIODIR = 0x00000FF0;
	LPC_GPIO1->FIODIR = 0x07800000;
	
	while(1){
		delay();
		
		dig_count += 1;
		if(dig_count == 0x05){
			dig_count = 0x00;
		}
		
		display();
	}
}
