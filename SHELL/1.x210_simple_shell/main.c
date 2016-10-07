#include "uart.h"

void myshell();

int main(void)
{
	uart_init();
	myshell();//里面使用了串口的输出输入，所以要在上面使用uart_init()
	return 0;
}

