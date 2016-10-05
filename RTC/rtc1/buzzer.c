#include "buzzer.h"
#if 0
void buzzer_init()
{
	/*配置为PWM timer2*/
	GPD0CON &= ~(0xf << 8);
	GPD0CON |= (0x2 << 8);
	/*设置预分频系数为65，即预分频后为1MHz*/	
	TCFG0 &= ~(0xff << 8);
	TCFG0 |= (65 << 8);
	/*设置MUX开关为2分频，即分频后为500KHZ*/	
	TCFG1 &= ~(0xf << 8);
	TCFG1 |= (0x1 << 8);
	/*设置蜂鸣器频率为20KHz，占空比为50%*/
	TCNTB2 = 250;
	TCMPB2 = 125;
	/*手动刷新TCNTB，TCMPB到TCNT，TCMP*/
	CON |= (1 << 13);
	CON &= ~(1 << 13);
	/*开启自动重装载*/
	CON |= (1 << 15);
	buzzer_off();
}
#endif
void buzzer_init()
{
	GPD0CON &= ~(0xf << 8);
	GPD0CON |= (0x1 << 8);
}
void buzzer_on()
{
	/*开定时器*/
	//CON |= (1 << 12);
	GPD0DAT |= (1 << 2);
}

void buzzer_off()
{
	/*关定时器*/
	//CON &= ~(1 << 12);
	GPD0DAT &= ~(1 << 2);
}
