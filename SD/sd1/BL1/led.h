#ifndef __LED_H__
#define __LED_H__    	    

#define GPJ0CON   *((volatile unsigned int *)0xe0200240)
#define GPJ0DAT   *((volatile unsigned int *)0xe0200244)
#define GPD0CON   *((volatile unsigned int *)0xe02000a0)
#define GPD0DAT   *((volatile unsigned int *)0xe02000a4)

void led_init();
void led_flash();
void delay();
void led1_on();
void led2_on();
void led3_on();
void led4_on();
void led_on();
void led_off();



#endif