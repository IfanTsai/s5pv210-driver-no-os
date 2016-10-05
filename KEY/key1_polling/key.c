//2016年09月07日20:16:18
#define GPH0CON (*((volatile unsigned int *)0xe0200c00))
#define GPH0DAT (*((volatile unsigned int *)0xe0200c04))
#define GPH2CON (*((volatile unsigned int *)0xe0200c40))
#define GPH2DAT (*((volatile unsigned int *)0xe0200c44))
#define SW5     (GPH0DAT & (0x1 << 2))
#define SW6     (GPH0DAT & (0x1 << 3))
#define SW7     (GPH2DAT & (0x1 << 0))
#define SW8     (GPH2DAT & (0x1 << 1))
#define SW9     (GPH2DAT & (0x1 << 2))
#define SW10    (GPH2DAT & (0x1 << 3))

void key_init();
void key_polling();

void key_init()
{
	GPH0CON = GPH0CON & (~(0xff << 8));
	GPH2CON = GPH2CON & (~(0xffff));
}

void key_polling()
{
	while(1)
	{
		if(SW5)
		{
			led_off();
		}
		else 
		{
			led1_on();
		}
		if(SW6)
		{
			led_off();
		}
		else
		{
			led2_on();
		}
		if(SW7)
		{
			led_off();
		}
		else
		{
			led3_on();
		}
		if(SW8)
		{
			led_off();
		}
		else
		{
			led4_on();
		}
		if(SW9)
		{
			led_off();
		}
		else
		{
			led_flash();
		}
		if(SW10)
		{
			led_off();
		}
		else
		{
			led_on();
		}
	}
}
