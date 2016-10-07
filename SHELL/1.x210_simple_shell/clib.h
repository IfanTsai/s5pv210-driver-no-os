#ifndef __CLIB_H__
#define __CLIB_H__
/*
*clib里存放着移植到x210开发板用的c库函数，各函数接口和使用跟c库的一样。
*涉及到输入输出的时候，需要初始化串口（call uart_init）。
*/

void putc(char ch);
void puts(const char *str);
char getc();
char *gets(char *str);
void memset(void *p, int val, int len);
int strlen(const char *str);
int strcmp(const char *s1, const char *s2);

#endif