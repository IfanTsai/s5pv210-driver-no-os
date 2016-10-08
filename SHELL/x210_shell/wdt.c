#include "wdt.h"
#include "uart.h"
#include "interrupt.h"
#include "myshell.h"
#include "clib.h"

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

	//设置定时为1秒，看门狗timer默认开启了自动重装载，但是第一次必须手动写进WTCNT中
	WTDAT = (unsigned int)(1000000/128 + 0.5);
	WTCNT = (unsigned int)(1000000/128 + 0.5);//这一句不可少

	WTCON |= (0x1 << 5);//open watchdog timer
}

void do_wdt()
{
	static int i = 1;
	uart_puts("test");
	uart_putc(i++);
	uart_putc(' ');

	WTCLRINT = 1;//写任何值清中断
	intc_clearvectaddr();
}

void wdt_time_init()
{
	wdt_init_interrupt();
	system_init_exception();
	/*注册中断处理函数*/
	intc_setvectaddr(NUM_WDT, do_wdt_timer);
	/*使能中断号对应的中断*/
	intc_enable(NUM_WDT);
}

void do_wdt_timer()
{
	//倒计时三个数，显示3,2,1,0
	static int bootloader_time = 4;
	bootloader_time--;
	/*显示倒计时的值*/
	char val[2] = {0};
	puts(itoa(bootloader_time, val));
	putc('\b');
	/*倒计时结束*/
	if(bootloader_time == 0)
	{
		g_isgo = 1;
		WTCON &= ~(0x1 << 5);//close watchdog timer
	}
	WTCLRINT = 1;//写任何值清中断
	intc_clearvectaddr();
}

