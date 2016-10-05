#include "lcd.h"
#include "picture.h"
#include "led.h"

int main(void)
{
	/*led_init();
	while(1)
		led_flash();*/
	lcd_init();
	//lcd_set_bkcolor(RED);
	lcd_draw_picture(gImage_picture);
	while(1);
	return 0;
}
