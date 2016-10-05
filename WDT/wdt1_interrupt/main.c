//2016年9月17日21:46:23
#include "interrupt.h"
#include "uart.h"
#include "wdt.h"

int main(void)
{
	uart_init();
	wdt_init_interrupt();
	uart_puts("ok.\n");
	system_init_exception();
	/*注册中断处理函数*/
	intc_setvectaddr(NUM_WDT, do_wdt);
	/*使能中断号对应的中断*/
	intc_enable(NUM_WDT);

	return 0;
}
