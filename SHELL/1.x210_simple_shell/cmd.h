#ifndef __CMD_H__
#define __CMD_H__

#define CMD_SET_CNT	  5   //命令集的个数
#define CMD_CNT      10   //最大支持多少个带参数的命令长度的组合
#define CMD_LEN      10   //最大支持分割后不带参数的命令长度

/*命令号*/
#define NOFIND       -2
#define EXIT         -1
#define LED           0

void cmd_split(char *str, char cmd[][CMD_LEN]);
int cmd_parser(char cmd[][CMD_LEN]);
void cmd_exec(int, char cmd[][CMD_LEN]);

#endif
