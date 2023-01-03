#include <gpio_drv.h>

void init_GPIO(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt)
{
    volatile unsigned long * CR;
    unsigned short tPIN = pin;
    unsigned short offset = 0x00;
	
	if(pin > 7)
		{
			tPIN -= 8;
			offset = 0x01;
		}
		
	if(port == 1)
		{
			RCC->APB2ENR |= 4; //// Enabling PORT A
			CR = (volatile unsigned long *) (GPIOA + offset);
		}
	else if(port == 2)
		{
			RCC->APB2ENR |= 8; //// Enabling PORT A
			CR = (volatile unsigned long *) (GPIOB + offset);
		}
	else if(port == 3)
		{
			RCC->APB2ENR |= 0x10; //// Enabling PORT A
			CR = (volatile unsigned long *) (GPIOC + offset);
		}
		
		*CR &= ~(0xf<<(tPIN)*4); ///Reset the taget pin
		*CR |= ((dir <<(tPIN*4)) | (opt<<(tPIN*4+2))); //// Set up the direction and the option of the PIN
}

int read_GPIO(unsigned short port, unsigned short pin)
{
    volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(port == 1)
		{
			IDR = (volatile unsigned long *) (GPIOA + offset);
		}
	else if(port == 2)
		{
			IDR = (volatile unsigned long *) (GPIOB + offset);
		}
	else if(port == 3)
	{
		IDR = (volatile unsigned long *) (GPIOC + offset);
	}
	state = ((*IDR & (1<<pin))>>pin);
	return state;
}

void write_GPIO(unsigned short port, unsigned short pin, unsigned short state)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;
	
	if(port == 1)
		{
			ODR = (volatile unsigned long *) (GPIOA + offset);
		}
	else if(port == 2)
		{
			ODR = (volatile unsigned long *) (GPIOB + offset);
		}
	else if(port == 3)
	{
		ODR = (volatile unsigned long *) (GPIOC + offset);
	}
	state ? (*ODR |= (state<<pin)) : (*ODR &= ~(1<<pin));
}

void toggle_GPIO(unsigned short port, unsigned short pin)
{
	if (read_GPIO(port,pin))
		{
			write_GPIO(port,pin,0);
		}
	else
		{
			write_GPIO(port,pin,1);
		}
}