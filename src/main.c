#include <stm32f103x6.h>
#include <gpio_drv.h>


void Delays(int time);

int main(void)
{
	init_GPIO(PA,0,IN,I_PP);
	init_GPIO(PC,13,OUT50, O_GP_PP);
	
	while(1)
	{
		if(read_GPIO(PA,0)==1) /// Checking status of PIN ! portA 
		{
			Delays(10);
			toggle_GPIO(PC,13); /// Toggle the PIN state
			Delays(10);
		}
		else
		{
			write_GPIO(PC,13,1); /// Set the PIN 13 port C high
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
