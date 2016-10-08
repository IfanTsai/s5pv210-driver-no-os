#include "cmd.h"
#include "clib.h"
#include "led.h"
#include "buzzer.h"
#include "adc.h"
#include "lcd.h"

/*命令执行动作*/
static void do_notfind(char cmd[][CMD_LEN]);
static void do_exit(char cmd[][CMD_LEN]);
static void do_led(char cmd[][CMD_LEN]);
static void do_buzzer(char cmd[][CMD_LEN]);
static void do_adc(char cmd[][CMD_LEN]);
static void do_lcd(char cmd[][CMD_LEN]);

//命令集
char *cmd_set[CMD_SET_CNT] = {"led", "buzzer", "adc", "lcd"};

//将str按空格分割后放入cmd字符串数组中
void cmd_split(char *str, char cmd[][CMD_LEN])
{
	//先去掉头部的多余空格
	while(*str == ' ')
	{
		str++;
	}

	int i = 0, j = 0;
	while(*str)
	{
		if(*str != ' ')
		{
			cmd[i][j] = *str;
			j++;
			str++;
		}
		else
		{
			cmd[i][j] = '\0';
			i++;
			j = 0;
			while(*str == ' ')
				str++;
		}
	}
	cmd[i][j] = '\0';
}

//解析命令
int cmd_parser(char cmd[][CMD_LEN])
{
	int i;	
	/*判断是否终止程序*/
	if(!strcmp(cmd[0], "exit"))
	{
		return EXIT;
	}
	/*遍历命令集*/
	for(i=0;i<CMD_SET_CNT;i++)
	{
		if(!strcmp(cmd[0], cmd_set[i]))
		{
			return i;
		}
	}
	/*输入的命令不在命令集内*/
	return NOFIND;
}

//执行命令
void cmd_exec(int i, char cmd[][CMD_LEN])
{
	switch(i)
	{
		case EXIT:
			do_exit(cmd);
			break;
		case NOFIND:
			do_notfind(cmd);
			break;
		case LED:
			do_led(cmd);
			break;
		case BUZZER:
			do_buzzer(cmd);
			break;
		case ADC:
			do_adc(cmd);
			break;
		case LCD:
			do_lcd(cmd);
			break;
		default:
			puts("\r\nnot set\r\n");
	}
}



/**************命令执行函数************************/

static inline void do_notfind(char cmd[][CMD_LEN])
{
	puts("\r\n");
	puts(cmd[0]);
	puts(": command not find\r\n");
}

static inline void do_exit(char cmd[][CMD_LEN])
{
	puts("\r\nthe shell exited\r\n");
}

static void do_led(char cmd[][CMD_LEN])
{
	//puts("\r\nled\r\n");
	if(!strcmp(cmd[1], "1"))
	{
		if(!strcmp(cmd[2], "on"))
		{
			led1_on();
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "off"))
		{
			led1_off();
			puts("\r\n");
			return;
		}
	}
	if(!strcmp(cmd[1], "2"))
	{
		if(!strcmp(cmd[2], "on"))
		{
			led2_on();
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "off"))
		{
			led2_off();
			puts("\r\n");
			return;
		}
	}
	if(!strcmp(cmd[1], "3"))
	{
		if(!strcmp(cmd[2], "on"))
		{
			led3_on();
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "off"))
		{
			led3_off();
			puts("\r\n");
			return;
		}
	}
	if(!strcmp(cmd[1], "4"))
	{
		if(!strcmp(cmd[2], "on"))
		{
			led4_on();
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "off"))
		{
			led4_off();
			puts("\r\n");
			return;
		}
	}
	if(!strcmp(cmd[1], "on"))
	{
		led_on();
		puts("\r\n");
		return;
	}
	if(!strcmp(cmd[1], "off"))
	{
		led_off();
		puts("\r\n");
		return;
	}
	puts("\r\n");
	puts(cmd[0]);
	puts(": arguments error\r\n");
	puts("try: 'led on', 'led off'\r\n");
	puts("     'led 1 on', 'led 2 on', 'led 3 on', 'led 4 on'\r\n");
	puts("     'led 1 off', 'led 2 off', 'led 3 off', 'led 4 off'\r\n");

}

static void do_buzzer(char cmd[][CMD_LEN])
{
	if(!strcmp(cmd[1], "on"))
	{
		buzzer_on();
		puts("\r\n");
		return;
	}
	if(!strcmp(cmd[1], "off"))
	{
		buzzer_off();
		puts("\r\n");
		return;
	}
	puts("\r\n");
	puts(cmd[0]);
	puts(": arguments error\r\n");
	puts("try: 'buzzer on', 'buzzer off'\r\n");
}

static void do_adc(char cmd[][CMD_LEN])
{
	if(!strcmp(cmd[1], "collect"))
	{
		adc_collect();
		puts("\r\n");
		return;
	}
	puts("\r\n");
	puts(cmd[0]);
	puts(": arguments error\r\n");
	puts("try: 'adc collect'\r\n");
}

static void do_lcd(char cmd[][CMD_LEN])
{
	if(!strcmp(cmd[1], "set"))
	{
		if(!strcmp(cmd[2], "WHITE") || !strcmp(cmd[2], "white"))
		{
			lcd_set_bkcolor(WHITE);
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "RED") || !strcmp(cmd[2], "red"))
		{
			lcd_set_bkcolor(RED);
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "GREEN") || !strcmp(cmd[2], "green"))
		{
			lcd_set_bkcolor(GREEN);
			puts("\r\n");
			return;
		}
		if(!strcmp(cmd[2], "BLUE") || !strcmp(cmd[2], "blue"))
		{
			lcd_set_bkcolor(BLUE);
			puts("\r\n");
			return;
		}	
	}
	puts("\r\n");
	puts(cmd[0]);
	puts(": arguments error\r\n");
	puts("try: 'lcd set white', 'lcd set red'\r\n");
	puts("     'lcd set green', 'lcd set blue'\r\n");
}
