#include "wdt.h"
#include "uart.h"
#include "interrupt.h"

void wdt_init_interrupt()
{
	WTCON &= ~(1 << 0);//disable reset
	WTCON |= (1 << 2);//enable interrupt

	//设置预分频系数为65，分频后为1MHz
	WTCON &= ~(0xff << 8);
	WTCON |= (65 << 8);

	//设置MUX开关分频为128,分频后为1/128MHz，周期为128us
	WTCON &= ~(0x3 << 3);
	WTCON |= (0x3 << 3);

	//设置定时为1.28秒，看门狗timer默认开启了自动重装载，但是第一次必须手动写进WTCNT中
	WTDAT = 10000;
	WTCNT = 10000;//这一句不可少

	WTCON |= (0x1 << 5);//open watchdog timer
}

void wdt_init_reset()
{
	WTCON |= (1 << 0);//enable reset
	WTCON &= ~(1 << 2);//disable interrupt

	//设置预分频系数为65，分频后为1MHz
	WTCON &= ~(0xff << 8);
	WTCON |= (65 << 8);

	//设置MUX开关分频为128,分频后为1/128MHz，周期为128us
	WTCON &= ~(0x3 << 3);
	WTCON |= (0x3 << 3);

	//设置定时为1.28秒，看门狗timer默认开启了自动重装载，但是第一次必须手动写进WTCNT中
	WTDAT = 10000;
	WTCNT = 10000;//这一句不可少

	WTCON |= (0x1 << 5);//open watchdog timer	
}

void do_wdt()
{
	static int i = 1;
	uart_puts("test");
	uart_puti(i++);
	uart_putc(' ');

	WTCLRINT = 1;//写任何值清中断
	intc_clearvectaddr();
}

