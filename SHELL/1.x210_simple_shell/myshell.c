#include "clib.h" 
#include "myshell.h"
#include "cmd.h"
#include "uart.h"

static void myshell_init()
{
	uart_init();
}

void myshell()
{
	myshell_init();
	char str[100] = {0};
	char cmd[CMD_CNT][CMD_LEN] = {"0"};

	while(1)
	{
		memset(str, 0, sizeof(str));
		puts("myshell$ ");
		while(!str[0])//输入为空时继续等待输入
		{
			gets(str);
		}
		cmd_split(str, cmd);//分割命令字符串
		int i = cmd_parser(cmd);//解析命令
		cmd_exec(i, cmd);//执行命令		
	}
}
