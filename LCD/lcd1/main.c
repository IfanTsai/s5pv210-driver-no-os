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
	/*while(1)	
	{
		lcd_set_bkcolor(RED);
		delay();
		lcd_set_bkcolor(GREEN);
		delay();
		lcd_set_bkcolor(BLUE);
		delay();
	}*/
	lcd_set_bkcolor(WHITE);
	/*lcd_draw_line(0, 0, ROW-1, COL-1, RED);
	lcd_draw_circle(ROW/2, COL/2, 50, BLUE);*/
	lcd_write_str(ROW/2, COL/2, "Abdde3343268fjijff44*&#@$(>.,?\\", RED);
	return 0;
}