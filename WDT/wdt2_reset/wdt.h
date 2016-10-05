#ifndef __WDT_H__
#define __WDT_H__

#define WTCON     (*((volatile unsigned int *)0xe2700000))
#define WTDAT     (*((volatile unsigned int *)0xe2700004))
#define WTCNT     (*((volatile unsigned int *)0xe2700008))
#define WTCLRINT  (*((volatile unsigned int *)0xe270000c))

void wdt_init_interrupt();
void wdt_init_reset();
void do_wdt();


#endif