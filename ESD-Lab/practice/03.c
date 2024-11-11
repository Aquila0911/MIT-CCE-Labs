#include<LPC17xx.h>
#define DL 4
#define SL 15
#define Button 12
#define Rows 10
#define Cols 23
#define default_key 0x78
 
int count=0;
int seven_seg[16] = {0x3F, 0x06, 0x5B,.......};
int select_seg[4] = {0,1,2,3};
int dig_count=0;
int digits[4] = {0,0,0,0};
int flag=1;
int input =0;

int key_map[4][4] = {
    {'0','1','2','3'},
    {'4','5','6','7'},
    {'8','9','A','B'},
    {'C','D','E','F'},
}


//P0.4 - P0.11 is Data
//P0.15 - P0.18 is Select
//P2.12 is the button
//P1.23 - P1.26 For COLUMNS
//P2.10 - P2.13  for ROWS


int main()
{
    LPC_GPIO0->FIODIR = 0xFF<<DL|0xF<<SL;
    LPC_GPIO2->FIODIR = 0xF<<Rows;
    while(1)
    {
        x = scan();
        if(x!=default_key)
            digits[input] = x;
            input++%4;
        update();+
    }
}
void increment()
{
    digits[0]++;
    if(digits[0]>0xF)
    {
        digits[0] = 0;
        digits[1]++;
        if(digits[1]>0xF)
        {
            digits[1]=0;
            digits[2]++;
            if(digits[2]>0xF)
            {
                digits[2]=0;
                digits[3]++;
                if(digits[3]>0xF)
                {
                    digits[3]=0;
                }
            }
        }
    }
}
void decrement()
{
    digits[0]--;
    if(digits[0]==0x0)
    {
        digits[0] = 0xF;
        digits[1]--;
        if(digits[1]==0x0)
        {
            digits[1]=0xF;
            digits[2]--;
            if(digits[2]==0x0)
            {
                digits[2]=0xF;
                digits[3]--;
                if(digits[3]==0x0)
                {
                    digits[3]=F;
                }
            }
        }
    }
}
void update()
{
    count++;
    if(count==10000)
    {
        count=0;
        
        // if(flag)
        //     increment();
        // else
        //     decrement();
    }
    display();
}
void display()
{
    LPC_GPIO1->FIOPIN = select_seg[dig_count]<<SL;
    LPC_GPIO0->FIOPIN = seven_seg[digits[dig_count]]<<DL;
    dig_count = (dig_count+1)%4;
    for(int i=0;i<10000;i++);
}

void scan()
{
    for(i=0;i<4;i++;)
    {
        LPC_GPIO2->FIOPIN = 1<<i+Rows;
        y = (LPC_GPIO1->FIOPIN>>Cols)&0xF;
        if(y)
            for(j=0;j<4;j++)
            {
                if(y&(0x1<<j))
                    return key_map[i][j];
            }
    }
    return default_key;
}
