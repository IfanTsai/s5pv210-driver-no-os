#include "lcd.h"

static void delay()
{
	volatile unsigned int i, j;
	for(i=0;i<2000;i++)
		for(j=0;j<1000;j++);
}

int main(void)
{
	lcd_init();
	while(1)	
	{
		lcd_set_bkcolor(RED);
		delay();
		lcd_set_bkcolor(GREEN);
		delay();
		lcd_set_bkcolor(BLUE);
		delay();
	}
	return 0;
}