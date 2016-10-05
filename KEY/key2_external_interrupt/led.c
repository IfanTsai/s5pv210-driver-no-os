//2016年09月07日20:09:47
#define GPJ0CON   *((volatile unsigned int *)0xe0200240)
#define GPJ0DAT   *((volatile unsigned int *)0xe0200244)
#define GPD0CON   *((volatile unsigned int *)0xe02000a0)
#define GPD0DAT   *((volatile unsigned int *)0xe02000a4)

void led_init();
void led_flash();
void delay();
void led1_on();
void led2_on();
void led3_on();
void led4_on();
void led_on();
void led_off();

void led_init()
{
	GPJ0CON = GPJ0CON | (0x1 << 12) | (0x1 << 16) | (0x1 << 20);
	GPD0CON = GPD0CON | (0x1 << 4);
}

void led_flash()
{
	led_off();
	delay();
	led_on();
	delay();
}

void led1_on()
{
	GPJ0DAT = GPJ0DAT & (~(0x1 << 3));
}

void led2_on()
{
	GPJ0DAT = GPJ0DAT & (~(0x1 << 4));
}

void led3_on()
{
	GPJ0DAT = GPJ0DAT & (~(0x1 << 5));
}

void led4_on()
{
	GPD0DAT = GPD0DAT & (~(0x1 << 1));
}

void led_off()
{
	GPJ0DAT = GPJ0DAT | ( (0x1 << 3) | (0x1 << 4) | (0x1 << 5) );
	GPD0DAT = GPD0DAT | ( 0x1 << 1 );
}

void led_on()
{
	led1_on();
	led2_on();
	led3_on();
	led4_on();
}

void delay()
{
	unsigned int i = 500000;
	while(i--);
}
