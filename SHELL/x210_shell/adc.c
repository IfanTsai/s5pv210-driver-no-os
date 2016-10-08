#include "adc.h"
#include "uart.h"
#include "clib.h"

static void delay()
{
	volatile unsigned int i, j;
	for(i=0;i<2000;i++)
		for(j=0;j<1000;j++);
}

void adc_init()
{
	TSADCCON0 |= (0x1 << 16);//12bit A/D conversion
	TSADCCON0 |= (0x1 << 14);//enable convert prescaler 
	TSADCCON0 |= (65 << 6);//PCLK/(65 + 1) = 1MHz, A/D convert rate = 1MHz / 5 = 200KSPS
	TSADCCON0 &= ~(0x1 << 2);//normal operation mode
	TSADCCON0 &= ~(0x1 << 1);//disable start by read
	//TSADCCON0 |= (0x1 << 1);//enable start by read
	ADCMUX &= ~(0xf << 0);//analog input channel select AIN0
}

void adc_collect()
{
	//start 
	TSADCCON0 |= (0x1 << 0);
	//wait 
	while(!(TSADCCON0 & (0x1 << 15)));
	//read
	unsigned int val = TSDATX0 & (0xfff << 0);

	char str[10] = {0};
	itoa(val, str);
	puts("\r\nvalue = ");
	puts(str);
}

void adc_test()
{
	adc_init();
	//TSADCCON0 |= (0x1 << 0);
	while(1)
	{
		adc_collect();
		delay();
	}
}

