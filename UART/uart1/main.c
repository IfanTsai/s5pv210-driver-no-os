#include "uart.h"

int main(void)
{
	uart_init();
	char str[] = "hello\n";
	while(1)
	{
		uart_puts(str);
		delay();
	}
	return 0;
}

