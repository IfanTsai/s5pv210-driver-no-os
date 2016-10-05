#include "uart.h"

void uart_init()
{
	/*配置GPIO*/
	GPA0CON = GPA0CON & (~0xff);
	GPA0CON = GPA0CON | 0x22;

	ULCON0 = 0x3;
    UCON0  = 0x5;
	UFCON0 = 0x0;
	UMCON0 = 0x0;
    /*波特率设置 115200*/
	UBRDIV0 = 35;
	UDIVSLOT0 = 0x888;
}

void uart_putc(char c)
{
	while(!(UTRSTAT0 & (1 << 1)));
    UTXH0 = c;
}

void uart_puti(int i)
{
	char str[10] = {0};
	tostr(i, str);
	uart_puts(str);
}

char uart_getc(void)
{
	while(!(UTRSTAT0 & (1 << 0)));
	return URXH0;
}

void uart_puts(const char *str)  
{  
    while (*str != '\0')  
    {  
		uart_putc(*str++);  
    }  
}

void tostr(int num, char *pstr)
{
	int tnum = num;//副本
	int len = 0;//数字位数计数器
	while(tnum)
	{
		len++;
		tnum /= 10;
	}

	for (int i = len - 1; i >= 0; i--)
	{
		pstr[i] = num % 10 + 48;
		num /= 10;
	}
}