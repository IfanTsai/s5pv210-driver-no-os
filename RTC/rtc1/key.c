#include "key.h"
#include "uart.h"
#include "interrupt.h"
#include "buzzer.h"

void key_interrupt_init()
{
	/*配置GPIO为中断模式*/
	GPH0CON |= (0xff << 8);
	GPH2CON |= (0xffff << 0); 
	/*配置下降沿触发*/
	EXT_INT_0_CON &= ~(0xff << 8);
	EXT_INT_0_CON |= ( (0x2 << 8) | (0x2 << 12 ) );
	EXT_INT_2_CON &= ~(0xffff << 0);
	EXT_INT_2_CON |= ( (0x2 << 0) | ( 0x2 << 4) | (0x2 << 8) | (0x2 << 12) );
	/*允许中断*/
	EXT_INT_0_MASK &= ~(0x3 << 2);
	EXT_INT_2_MASK &= ~(0x0f << 0);
	/*清挂起*/
	EXT_INT_0_PEND |= (0x3 << 2);
	EXT_INT_2_PEND |= (0x0f << 0);
}

void do_SW5()
{
#if 0
	uart_puts("SW5 press.\n");
	EXT_INT_0_PEND |= (0x1 << 2);
	intc_clearvectaddr();
#endif
	buzzer_off();	
	EXT_INT_0_PEND |= (0x1 << 2);
	intc_clearvectaddr();
}
#if 0
void do_SW6()
{
	uart_puts("SW6 press.\n");
	EXT_INT_0_PEND |= (0x1 << 3);
	intc_clearvectaddr();
}

void do_SW7_to_10()
{
	if(EXT_INT_2_PEND & (0x1 << 0))
	{
		uart_puts("SW7 press.\n");
		EXT_INT_2_PEND |= (0x1 << 0);
		intc_clearvectaddr();
	}
	if(EXT_INT_2_PEND & (0x1 << 1))
	{
		uart_puts("SW8 press.\n");
		EXT_INT_2_PEND |= (0x1 << 1);
		intc_clearvectaddr();
	}
	if(EXT_INT_2_PEND & (0x1 << 2))
	{
		uart_puts("SW9 press.\n");
		EXT_INT_2_PEND |= (0x1 << 1);
		intc_clearvectaddr();
	}
	if(EXT_INT_2_PEND & (0x1 << 3))
	{
		uart_puts("SW10 press.\n");
		EXT_INT_2_PEND |= (0x1 << 1);
		intc_clearvectaddr();
	}
}
#endif

void key_init()
{
	GPH0CON = GPH0CON & (~(0xff << 8));
	GPH2CON = GPH2CON & (~(0xffff));
}

#if 0
void key_polling()
{
	while(1)
	{
		if(SW5)
		{
			led_off();
		}
		else 
		{
			led1_on();
		}
		if(SW6)
		{
			led_off();
		}
		else
		{
			led2_on();
		}
		if(SW7)
		{
			led_off();
		}
		else
		{
			led3_on();
		}
		if(SW8)
		{
			led_off();
		}
		else
		{
			led4_on();
		}
		if(SW9)
		{
			led_off();
		}
		else
		{
			led_flash();
		}
		if(SW10)
		{
			led_off();
		}
		else
		{
			led_on();
		}
	}
}
#endif