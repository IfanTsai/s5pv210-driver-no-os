#include "clib.h"
#include "uart.h"

void putc(char ch)
{
	uart_putc(ch);
}

void puts(const char *str)
{
	uart_puts(str);
}

char getc()
{
	return uart_getc();
}

char *gets(char *str)
{
	return uart_gets(str);
}

void memset(void *p, int val, int len)
{
	char *tp = (char *)p;
	for(int i=0;i<len;i++)
	{
		*tp = val;
		tp++;
	}
}

int strlen(const char *str)
{
	int len = 0;
	while(*str)
	{
		len++;
		str++;
	}
	return len;
}

int strcmp(const char *s1, const char *s2)
{
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if(len1 != len2)
	{
		return -1;
	}

	for(int i=0;i<len1;i++)
	{
		if(s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}

	return 0;	
}