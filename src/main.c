#include <stm32f103x6.h>
#include <rcc_cfg.h>
#include <gpio_drv.h>


void Delays(int time);

int main(void)
{
	Set_Clock_HSE_8mhz_72mhz();
	GPIO_Init(PA,0,IN,I_PP);
	GPIO_Init(PC,13,OUT50, O_GP_PP);
	
	while(1)
	{
		if(Read_GPIO(PA,0)==1) /// Checking status of PIN ! portA 
		{
			Delays(10);
			Toggle_GPIO(PC,13); /// Toggle the PIN state
			Delays(10);
		}
		else
		{
			Write_GPIO(PC,13,1); /// Set the PIN 13 port C high
		}
	}
	
}


void Delays(int time) /// Random delay function
{
	int t;
	for(;time>0;time--)
	{
	 for(t=0;t<100000;t++)
		{__ASM("nop");}
	}
}
