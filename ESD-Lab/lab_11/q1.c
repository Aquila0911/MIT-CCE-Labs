#include<LPC17xx.h>

unsigned long int flag = 0x00;

int main()
{
	LPC_PINCON->PINSEL3 = 2<<14;
	LPC_PWM1->TCR = 0x02;
	LPC_PWM1->PCR = 0x00001000;
	LPC_PWM1->PR = 0;
	LPC_PWM1->MCR = 3;
	LPC_PWM1->MR0 = 30000;
	LPC_PWM1->MR4 = 50;
	LPC_PWM1->LER = 0xFF;
	LPC_PWM1->TCR = 9;

	NVIC_EnableIRQ(PWM1_IRQn);
	while(1);
}

void PWM1_IRQHandler()
{
	LPC_PWM1->IR = 0x01;
	if(flag == 0x00)
	{
		LPC_PWM1->MR4 += 50;
		LPC_PWM1->LER = 0xFF;
		if(LPC_PWM1->MR4 > 29900)
			{
			flag = 0xFF;
			LPC_PWM1->LER = 0xFF;
			}
	}
	else if(flag == 0xFF)
	{
		LPC_PWM1->MR4 -= 50;
		LPC_PWM1->LER = 0xFF;
		if(LPC_PWM1->MR4 < 100)
		{
		flag = 0x0;
		LPC_PWM1->LER = 0xFF;
		}
	}
}
