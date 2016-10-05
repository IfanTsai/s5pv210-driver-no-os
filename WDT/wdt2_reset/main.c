
#include "interrupt.h"
#include "uart.h"
#include "wdt.h"

int main(void)
{
	static int i = 1;
	uart_init();
	//wdt_init_interrupt();
	wdt_init_reset();
	uart_puts("ok.\n");
	//system_init_exception();
	/*注册中断处理函数*/
	//intc_setvectaddr(NUM_WDT, do_wdt);
	/*使能中断号对应的中断*/
	//intc_enable(NUM_WDT);
	while(1);
	return 0;
}

