#define GPJ0CON   *((volatile unsigned int *)0xe0200240)
#define GPJ0DAT   *((volatile unsigned int *)0xe0200244)

void delay();

int main(void)
{
    GPJ0CON = 0x11111111;
	while(1)
	{
		GPJ0DAT = 0xff;
		delay();
		GPJ0DAT = 0x00;
		delay();
	}
	return 0;
}

void delay()
{
	unsigned int i = 500000;
	while(i--);
}
