#ifndef __RTC_H__
#define __RTC_H__

typedef struct rtc_time
{
	unsigned int year;
	unsigned int month;
	unsigned int date;//日
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int day;//星期
}rtc_time;

#define INTP	     (*((volatile unsigned int *)0xe2800030))
#define RTCCON       (*((volatile unsigned int *)0xe2800040))
#define RTCALM       (*((volatile unsigned int *)0xe2800050))
#define ALMSEC       (*((volatile unsigned int *)0xe2800054))
#define ALMMIN       (*((volatile unsigned int *)0xe2800058))
#define ALMHOUR      (*((volatile unsigned int *)0xe280005c))
#define ALMDAY       (*((volatile unsigned int *)0xe2800060))
#define ALMMON       (*((volatile unsigned int *)0xe2800064))
#define ALMYEAR      (*((volatile unsigned int *)0xe2800068))
#define BCDSEC       (*((volatile unsigned int *)0xe2800070))
#define BCDMIN       (*((volatile unsigned int *)0xe2800074))
#define BCDHOUR      (*((volatile unsigned int *)0xe2800078))
#define BCDDAY       (*((volatile unsigned int *)0xe280007c))
#define BCDDAYWEEK   (*((volatile unsigned int *)0xe2800080))
#define BCDMON       (*((volatile unsigned int *)0xe2800084))
#define BCDYEAR      (*((volatile unsigned int *)0xe2800088))

/*bcd转码解码*/
#define num_to_bcd(num)   ( (((num)/10) << 4) | ((num) % 10) )
#define bcd_to_num(bcd)   ( (((bcd)  & 0xf0) >> 4)*10 + ((bcd)  & 0x0f) )

void rtc_set_time(const rtc_time *ptime);
void rtc_get_time(rtc_time *ptime);
void rtc_set_alarm(const rtc_time *ptime);
void do_rtc_alarm();


#endif
