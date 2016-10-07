#include "clib.h" 

#define BUF_SET_LEN	  5

void myshell()
{
	//命令集
	char *cmd_set[BUF_SET_LEN] = {"led", "lcd", "uart", "buzzer", "adc"};
	char cmd[100] = {0};
	int i;
	while(1)
	{
		memset(cmd, 0, sizeof(cmd));
		puts("myshell$ ");
		while(!cmd[0])//输入为空时继续等待输入
		{
			gets(cmd);
		}
		//puts("\r\n-----------\r\n");
		//puts(cmd);
		/*判断是否终止程序*/
		if(!strcmp(cmd, "exit"))
		{
			puts("\r\nthe shell exited");
			break;
		}
		/*遍历命令集*/
		for(i=0;i<BUF_SET_LEN;i++)
		{
			if(!strcmp(cmd, cmd_set[i]))
			{
				puts("\r\n");
				puts(cmd);
				puts("\r\n");
				break;
			}
		}
		/*输入的命令不在命令集内*/
		if(i == BUF_SET_LEN)
		{
			puts("\r\n");
			puts(cmd);
			puts(": not find commend\r\n");
		}
	}
}
