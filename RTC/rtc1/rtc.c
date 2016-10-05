#include "rtc.h"
#include "buzzer.h"
#include "interrupt.h"
#include "stdio.h"
#include "key.h"

static void delay()
{
	volatile int i, j;
	for(i=0;i<1000;i++)
		for(j=0;j<2000;j++);
}

void rtc_set_time(const rtc_time *ptime)
{
	RTCCON |= (1 << 0);//开rtc读写

	BCDYEAR = num_to_bcd(ptime->year - 2000);
	BCDMON  = num_to_bcd(ptime->month);
	BCDDAY  = num_to_bcd(ptime->date);
	BCDHOUR = num_to_bcd(ptime->hour);
	BCDMIN  = num_to_bcd(ptime->minute);
	BCDSEC  = num_to_bcd(ptime->second);
	BCDDAYWEEK = num_to_bcd(ptime->day);

	RTCCON &= ~(1 << 0);//关rtc读写
}

void rtc_get_time(rtc_time *ptime)
{
	RTCCON |= (1 << 0);//开rtc读写

	ptime->year = bcd_to_num(BCDYEAR) + 2000;
	ptime->month = bcd_to_num(BCDMON);
	ptime->date  = bcd_to_num(BCDDAY);
	ptime->hour = bcd_to_num(BCDHOUR);
	ptime->minute  = bcd_to_num(BCDMIN);
	ptime->second  = bcd_to_num(BCDSEC);
	ptime->day = bcd_to_num(BCDDAYWEEK);

	RTCCON &= ~(1 << 0);//关rtc读写
}

void rtc_set_alarm(const rtc_time *ptime)
{
	//buzzer_init();
	RTCALM |= (1 << 0);//使能alarm 秒
	RTCALM |= (1 << 6);//使能alarm 
	ALMSEC = num_to_bcd(ptime->second);
	buzzer_init();
	key_interrupt_init();
}

void do_rtc_alarm()
{
	printf("---time out---  ");
	buzzer_on();
	INTP |= (1 << 1);
	intc_clearvectaddr();
}
