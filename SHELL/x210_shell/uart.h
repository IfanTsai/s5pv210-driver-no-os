#ifndef __UART_H__
#define __UART_H__

#define GPA0CON   (*((volatile unsigned int *)0xe0200000))
#define ULCON0    (*((volatile unsigned int *)0xe2900000))
#define UCON0     (*((volatile unsigned int *)0xe2900004))
#define UFCON0    (*((volatile unsigned int *)0xe2900008))
#define UMCON0    (*((volatile unsigned int *)0xe290000c))
#define UTRSTAT0  (*((volatile unsigned int *)0xe2900010))
#define UTXH0     (*((volatile unsigned int *)0xe2900020))
#define URXH0     (*((volatile unsigned int *)0xe2900024))
#define UBRDIV0   (*((volatile unsigned int *)0xe2900028))
#define UDIVSLOT0 (*((volatile unsigned int *)0xe290002c))

void uart_init();
void uart_putc(char ch);
void uart_puts(const char *str);
char uart_getc();
char *uart_gets(char *str);
int is_key_press();

#endif
