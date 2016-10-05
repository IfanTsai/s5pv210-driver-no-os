#include "sd.h"
typedef unsigned int bool;

// 通道号：0，或者2
// 开始扇区号：45
// 读取扇区个数：2048
// 读取后放入内存地址：0x23E00000
// with_init：0
typedef bool(*pCopySDMMCtoMem)(int, unsigned int, unsigned short, unsigned int*, bool);
typedef void(*jump)();

// 从SD卡第45扇区开始，复制2048个扇区内容到DDR的0x23E00000，然后跳转到23E00000去执行
void copy_bl2_to_ddr()
{
	// 读取SD卡扇区到DDR中
	pCopySDMMCtoMem p1 = (pCopySDMMCtoMem)(*((unsigned int *)0xD0037F98));
	p1(2, SD_START_BLOCK, SD_BLOCK_CNT, (unsigned int *)DDR_START_ADDR, 0);	

	//由于BL1和BL2是分开的两段程序而无法使用ldr跳转，
	//所以使用函数调用的方法来跳转
	jump p2 = (jump)DDR_START_ADDR;
	p2();
}






















