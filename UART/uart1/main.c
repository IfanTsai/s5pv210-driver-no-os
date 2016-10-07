#include "uart.h"

static void delay()
{
	volatile unsigned int i = 500000;
	while(i--);
}

int main(void)
{
	uart_init();
	char str[] = "hello\r\n";
	while(1)
	{
		uart_puts(str);
		delay();
	}
	return 0;
}

