#include "cmd.h"
#include "clib.h"

/*命令执行动作*/
static void do_notfind(char cmd[][CMD_LEN]);
static void do_exit(char cmd[][CMD_LEN]);
static void do_led(char cmd[][CMD_LEN]);

//命令集
char *cmd_set[CMD_SET_CNT] = {"led", "lcd", "uart", "buzzer", "adc"};

//将str按空格分割后放入cmd字符串数组中
void cmd_split(char *str, char cmd[][CMD_LEN])
{
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
		default:
			puts("\r\nnot set\r\n");
	}
}

static void do_notfind(char cmd[][CMD_LEN])
{
	puts("\r\n");
	puts(cmd[0]);
	puts(" command not find\r\n");
}

static void do_exit(char cmd[][CMD_LEN])
{
	puts("\r\nthe shell exited\r\n");
}

static void do_led(char cmd[][CMD_LEN])
{
	puts("\r\nled\r\n");
}

