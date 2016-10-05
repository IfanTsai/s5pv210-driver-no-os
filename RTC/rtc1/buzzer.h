#ifndef __BUZZER_H__
#define __BUZZER_H__

#define GPD0CON (*((volatile unsigned int *)0xe02000a0))
#define GPD0DAT (*((volatile unsigned int *)0xe02000a4))
#define TCFG0   (*((volatile unsigned int *)0xe2500000))
#define TCFG1   (*((volatile unsigned int *)0xe2500004))
#define CON     (*((volatile unsigned int *)0xe2500008))
#define TCNTB2  (*((volatile unsigned int *)0xe2500024))
#define TCMPB2  (*((volatile unsigned int *)0xe2500028))


void buzzer_init();
void buzzer_on();
void buzzer_off();

#endif
