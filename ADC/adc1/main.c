//2016年10月2日20:10:53
#include "stdio.h"
#include "uart.h"
#include "adc.h"
	
int main(void)
{
	uart_init();
	adc_test();
	return 0;
}
