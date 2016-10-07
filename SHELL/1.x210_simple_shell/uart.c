//2016年09月04日22:23:53
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

void uart_putc(char ch)
{
	while(!(UTRSTAT0 & (1 << 1)));
    UTXH0 = ch;
}

char uart_getc(void)
{
	while(!(UTRSTAT0 & (1 << 0)));
	char ch = URXH0;
	if(ch == '\r')
	{
		ch = '\n';
	}
	return ch;
}

char *uart_gets(char *str)
{
	char ch;
	char *tstr = str;
	while((ch = uart_getc()) != '\n')
	{
		if(ch != '\b')
		{
			uart_putc(ch);
			*str++ = ch;
		}
		else
		{
			if(str > tstr)
			{
				uart_putc('\b');
				uart_putc(' ');
				uart_putc('\b');
				str--;
			}
		}
	}
	*str = '\0';
	return tstr;
}

void uart_puts(const char *str)  
{  
    while (*str)  
    {  
		uart_putc(*str++);  
    }  
}


