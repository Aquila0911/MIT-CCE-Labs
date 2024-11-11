//C Program to do the following - Varying intensity using Row 0 of Matrix Keyboard.

/* Intensity Level         Key Pressed
        10%                    0
        25%                    1
        50%                    2
        75%                    3
*/

#include<LPC17xx.h>

void initpwm(void);
void updatepulsewidth(unsigned int pulsewidth);
void delayms(unsigned int milliseconds);
int scan(void);
unsigned int temp3;
int pulsewidth[]={0,2500,5000,10000};
int dir=0;

int main(void)
{
		float in_vtg;
		unsigned int adc_temp;
		char vtg[7],dval[7];
		LPC_GPIO0 -> FIODIR = 0xF << 23 | 1 << 27 | 1 << 28;
    LPC_GPIO0->FIODIR = 0xf00;
    initpwm();
		LPC_PINCON->PINSEL3|=3<<30;//p1.31 as AD0.5
		LPC_SC->PCONP |=(1<<12);//enable peripheral adc
		LPC_SC->PCONP |= (1<<15); //Power for GPIO block
	
    while(1)
    {
			LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24);//0x01200001; //ADC0.5, start conversion and operational
			while(!( LPC_ADC->ADGDR >>31 == 0));//31st bit is done bit
			adc_temp = LPC_ADC->ADGDR;
			adc_temp >>= 4;
			adc_temp &= 0x00000FFF; //12 bit ADC
			in_vtg = ((float)adc_temp * 3.3/0xfff); //calculating input analog as 0.805mv is resolution
			
			if(in_vtg<0.5)
					updatepulsewidth(pulsewidth[0]);
			else if(in_vtg<1.25)
					updatepulsewidth(pulsewidth[1]);
			else if(in_vtg<2.0)
					updatepulsewidth(pulsewidth[2]);
			else if(in_vtg<3.3)
					updatepulsewidth(pulsewidth[3]);
			delayms(10000);
    }

}


void initpwm(void)
{
    LPC_PINCON->PINSEL3|=0x8000;
    LPC_PWM1->PCR=0x1000;
    LPC_PWM1->PR=0;
    LPC_PWM1->MR0=10000;
    LPC_PWM1->MCR=2;
    LPC_PWM1->LER=0xff;
    LPC_PWM1->TCR=0x2;
    LPC_PWM1->TCR=0x9;
}

void updatepulsewidth(unsigned int pulsewidth)
{
    LPC_PWM1->MR4=pulsewidth;
    LPC_PWM1->LER=0xff;
}

void delayms(unsigned int milliseconds)
{
    LPC_TIM0->CTCR=0x0;
    LPC_TIM0->PR=2;
    LPC_TIM0->TCR=0x02;
    LPC_TIM0->TCR=0x1;
    while(LPC_TIM0->TC<milliseconds);
    LPC_TIM0->TCR=0;
}
