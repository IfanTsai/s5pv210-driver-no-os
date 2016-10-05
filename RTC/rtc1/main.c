//2016年09月21日16:51:09
#include "stdio.h"
#include "uart.h"
#include "interrupt.h"
#include "rtc.h"
#include "key.h"

static void delay()
{
	volatile int i, j;
	for(i=0;i<1000;i++)
		for(j=0;j<2000;j++);
}

int main(void)
{
	uart_init();
	system_init_exception();
	intc_setvectaddr(NUM_RTC_ALARM, do_rtc_alarm);
	intc_setvectaddr(NUM_EINT2, do_SW5);
	intc_enable(NUM_RTC_ALARM);
	intc_enable(NUM_EINT2);
	printf("--------rtc test-----------\n");
	delay();
	rtc_time time = {0};
	time.year = 2015;
	time.month = 9;
	time.date = 20;
	time.hour = 22;
	time.minute = 00;
	time.second = 10;
	time.day = 2;
	rtc_set_time(&time);

	time.second = 15;
	rtc_set_alarm(&time);
	

	while(1)
	{
		rtc_get_time(&time);
		printf("%d:%d:%d:%d:%d:%d:week%d   ", 
			time.year, time.month, time.date, 
			time.hour, time.minute, time.second, time.day);
		delay();
	}
	return 0;
}
