#ifndef __LED_H__
#define __LED_H__

#define GPJ0CON   *((volatile unsigned int *)0xe0200240)
#define GPJ0DAT   *((volatile unsigned int *)0xe0200244)

#ifndef GPD0CON
#define GPD0CON   *((volatile unsigned int *)0xe02000a0)
#endif 

#ifndef GPD0DAT
#define GPD0DAT   *((volatile unsigned int *)0xe02000a4)
#endif

void led_init();
void led_flash();
void led1_on();
void led2_on();
void led3_on();
void led4_on();
void led1_off();
void led2_off();
void led3_off();
void led4_off();
void led_on();
void led_off();


#endif