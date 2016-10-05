//2016年09月17日14:51:19
#include "uart.h"
#include "buzzer.h"

int main(void)
{
	uart_init();
	buzzer_init();
	buzzer_on();
	return 0;
}

