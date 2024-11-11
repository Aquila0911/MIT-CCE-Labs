#include <lpc17xx.h>
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()
#include <stdio.h>
#define RS_CTRL 0x08000000 // P0.27, 1<<27
#define EN_CTRL 0x10000000 // P0.28, 1<<28
#define DT_CTRL 0x07800000 // P0.23 to P0.26 data lines, 0x07800000

#define Ref_Vtg 3.300
#define Full_Scale 0xFFF //12 bit ADC

unsigned long int temp1 = 0, temp2 = 0;
unsigned char flag1 = 0, flag2 = 0;
unsigned char num_str[5];
unsigned long int init_command[] = {0x30, 0x30, 0x30, 0x20, 0x28, 0x0C, 0x06, 0x01, 0x80};

void lcd_write(void);
void port_write(void);
void delay_lcd(unsigned int);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char*);
void lcd_clear(void);
void roll_dice(void);

int main(void)
{
		unsigned long adc_temp;
		unsigned int i;
		float in_vtg;
		unsigned char vtg[7];
		unsigned char dval[7];
		unsigned char Msg3[11] = {"ANALOG IP:"};
		unsigned char Msg4[12] = {"ADC OUTPUT:"};
    SystemInit();
    SystemCoreClockUpdate();
    LPC_GPIO0->FIODIR = DT_CTRL | RS_CTRL | EN_CTRL;
    

    lcd_clear();
		LPC_SC->PCONP = (LPC_SC->PCONP | (1<<15));
		for(i=0;i<9;i++)
    {
        lcd_command(init_command[i]);
        delay_lcd(30000);
    }
    
		LPC_PINCON->PINSEL3 |= 0xC0000000; 
		LPC_SC->PCONP |= (1<<12); 
		
		SystemCoreClockUpdate();
		temp1 = 0x80;
		lcd_command(temp1);
		delay_lcd(800);
		lcd_string(&Msg3[0]);
		temp1 = 0xC0;
		lcd_command(temp1);
		delay_lcd(800);
		lcd_string(&Msg4[0]);
		
		while(1)
{
		LPC_ADC->ADCR = (1<<5)|(1<<21)|(1<<24);
		
		while((adc_temp = LPC_ADC->ADGDR) == 0x80000000);
		
		adc_temp = LPC_ADC->ADGDR;
		adc_temp >>= 4;
		adc_temp &= 0x00000FFF; 
		in_vtg = (((float)adc_temp * (float)Ref_Vtg))/((float)Full_Scale); 
		
		sprintf(vtg,"%3.2fV",in_vtg);
		
		sprintf(dval,"%x",adc_temp);
		for(i=0;i<2000;i++);
		temp1 = 0x8A;
		lcd_command(temp1);
		delay_lcd(800);
		lcd_string(&vtg[0]);
		temp1 = 0xCB;
		lcd_command(temp1);
		delay_lcd(800);
		lcd_string(&dval[0]);
		for(i=0;i<200000;i++);
		for(i=0;i<7;i++)
			vtg[i] = dval[i] = 0x00;
		adc_temp = 0;
		in_vtg = 0;
		}
}

void lcd_command(unsigned char command)
{
    flag1 = 0;
    temp1 = command;
    lcd_write();
}

void lcd_data(unsigned char data)
{
    flag1 = 1;
    temp1 = data;
    lcd_write();
}

void lcd_string(unsigned char* str)
{
    while (*str)
    {
        lcd_data(*str++);
    }
}

void lcd_clear(void)
{
    lcd_command(0x01);
    delay_lcd(30000);
}

void lcd_write(void)
{
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;
    temp2 = temp1 & 0xF0;
    temp2 = temp2 << 19;
    port_write();
    
    if (flag2 == 0)
    {
        temp2 = temp1 & 0x0F;
        temp2 = temp2 << 23;
        port_write();
    }
}

void port_write(void)
{
    LPC_GPIO0->FIOPIN = temp2;
    
    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = RS_CTRL;
    else
        LPC_GPIO0->FIOSET = RS_CTRL;
    
    LPC_GPIO0->FIOSET = EN_CTRL;
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL;
    delay_lcd(30000);
}

void delay_lcd(unsigned int r1)
{
    unsigned int r;
    for (r = 0; r < r1; r++);
    return;
}
