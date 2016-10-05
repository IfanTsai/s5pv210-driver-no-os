#ifndef __ADC_H__
#define __ADC_H__

#define TSADCCON0    (*((volatile unsigned int *)0xe1700000))
#define TSDATX0      (*((volatile unsigned int *)0xe170000c))
#define ADCMUX   	 (*((volatile unsigned int *)0xe170001c))

void adc_test();

#endif