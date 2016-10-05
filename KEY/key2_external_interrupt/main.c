//2016年9月15日21:38:40
#include "interrupt.h"
#include "key.h"
#include "uart.h"

#define EINT_SW5 NUM_EINT2
#define EINT_SW6 NUM_EINT3
#define EINT_SW7_to_10 NUM_EINT16_31

int main(void)
{
	uart_init();
	uart_puts("ok.\n");
	system_init_exception();
	key_interrupt_init();
	/*使能中断号对应的中断*/
	intc_enable(EINT_SW5);
	intc_enable(EINT_SW6);
	intc_enable(EINT_SW7_to_10);
	/*注册中断处理函数*/
	intc_setvectaddr(EINT_SW5, do_SW5);
	intc_setvectaddr(EINT_SW6, do_SW6);
	intc_setvectaddr(EINT_SW7_to_10, do_SW7_to_10);
	
	return 0;
}
