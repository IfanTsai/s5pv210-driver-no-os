//2016年09月07日20:09:47
#include "led.h"

static void delay()
{
	unsigned int i = 500000;
	while(i--);
}

void led_init()
{
	GPJ0CON = GPJ0CON | (0x1 << 12) | (0x1 << 16) | (0x1 << 20);
	GPD0CON = GPD0CON | (0x1 << 4);
	led_off();
}

void led_flash()
{
	led_off();
	delay();
	led_on();
	delay();
}

inline void led1_on()
{
	GPJ0DAT = GPJ0DAT & (~(0x1 << 3));
}

inline void led1_off()
{
	GPJ0DAT = GPJ0DAT | (0x1 << 3);
}

inline void led2_on()
{
	GPJ0DAT = GPJ0DAT & (~(0x1 << 4));
}

inline void led2_off()
{
	GPJ0DAT = GPJ0DAT | (0x1 << 4);
}

inline void led3_on()
{
	GPJ0DAT = GPJ0DAT & (~(0x1 << 5));
}

inline void led3_off()
{
	GPJ0DAT = GPJ0DAT | (0x1 << 5);
}

inline void led4_on()
{
	GPD0DAT = GPD0DAT & (~(0x1 << 1));
}

inline void led4_off()
{
	GPD0DAT = GPD0DAT | (0x1 << 1);
}

void led_off()
{
	GPJ0DAT = GPJ0DAT | ( (0x1 << 3) | (0x1 << 4) | (0x1 << 5) );
	GPD0DAT = GPD0DAT | ( 0x1 << 1 );
}

void led_on()
{
	led1_on();
	led2_on();
	led3_on();
	led4_on();
}

