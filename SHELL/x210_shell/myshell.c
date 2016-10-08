#include "clib.h" 
#include "myshell.h"
#include "cmd.h"
#include "uart.h"
#include "led.h"
#include "buzzer.h"
#include "adc.h"
#include "lcd.h"
#include "wdt.h"

//表示倒计时是否结束
int g_isgo = 0;

static void myshell_init()
{
	uart_init();
	led_init();
	buzzer_init();
	adc_init();
	lcd_init();
	wdt_time_init();
}

void myshell()
{
	myshell_init();
	char str[100] = {0};
	char cmd[CMD_CNT][CMD_LEN] = {"0"};

	puts("press any key to stop autoboot: ");
	g_isgo = 0;	//waring：防止全局变量初始化无效
	while( (!g_isgo) && (!is_key_press()) );//等待任意按键或者倒计时到0
	WTCON &= ~(0x1 << 5);//close watchdog timer
	puts("\r\n");
	if(g_isgo)//倒计时结束（仍没有按键按下）
	{
		buzzer_on();
		while(1);
	}
	while(1)
	{
		memset(str, 0, sizeof(str));
		puts("x210 shell$ ");
		while(!str[0])//输入为空时继续等待输入
		{
			gets(str);
		}
		cmd_split(str, cmd);//分割命令字符串
		int i = cmd_parser(cmd);//解析命令
		cmd_exec(i, cmd);//执行命令		
	}
}
