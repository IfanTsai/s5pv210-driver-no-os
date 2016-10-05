//2016年9月22日21:20:11
#include "led.h"

int main(void)
{
	led_init();
	while(1)
	{
		led_flash();
	}
	return 0;
}
