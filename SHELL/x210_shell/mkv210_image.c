//2016年08月26日22:30:15
//将能用usb调试的镜像生成带头信息的SD卡镜像
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

#define BUF_SIZE (16*1024)
#define IMG_SIZE (16*1024)//BL1代码:16kb
#define HEADER_SIZE 16//BL1中头信息:16字节	


int main(int argc, char *argv[])
{
	/*命令行参数个数检验*/
	if(argc != 3)
	{
		printf("%s argc error\n", argv[0]);
		return -1;
	}

	/*创建buf*/
	char *buf = (char *)malloc(BUF_SIZE);
	if(!buf)
	{
		printf("buf malloc error\n");
		return -1;
	}
	bzero(buf, BUF_SIZE);

	/*打开usb镜像文件*/
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("opne argv[1]");
		free(buf);
		return -1;
	}
	/*获取usb镜像文件大小*/
	int file_len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	/*读取usb镜像内容到buf的第16字节*/	
	int count = (file_len < (IMG_SIZE - HEADER_SIZE)) ? file_len : (IMG_SIZE - HEADER_SIZE);
	int rnum = read(fd, &buf[16], count);
	if(rnum < 0)
	{
		perror("read");
		close(fd);
		free(buf);
		return -1;
	}
	close(fd);
	
	/*计算校验和*/
	char *a = buf + HEADER_SIZE;
	int check_sum = 0;
	for(int i=0;i<(IMG_SIZE - HEADER_SIZE);i++)
	{
		check_sum += (0xFF) & *a++;
	}
	/*将校验和写入buf中*/
	a = buf + 8;
	*( (unsigned int *)a ) = check_sum;
	
	/*创建sd卡镜像文件*/
	umask(0);
	fd = open(argv[2], O_RDWR | O_CREAT, 0777);
	if(fd < 0)
	{
		perror("open argv[2]");
		close(fd);
		free(buf);
		return -1;
	}
	/*将buf里全部内容写到sd卡镜像*/
	int wnum = write(fd, buf, BUF_SIZE);
	if(wnum < 0)
	{
		perror("write");
		close(fd);
		free(buf);
		return -1;
	}

	close(fd);
	free(buf);

	return 0;
}
