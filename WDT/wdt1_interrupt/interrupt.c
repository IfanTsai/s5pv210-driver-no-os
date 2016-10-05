#include <stdio.h>
#include "interrupt.h"

//绑定异常向量表并且初始化中断控制器
void system_init_exception(void)
{
	EXCEPTION_IRQ  = (unsigned int)irq_handle;
	EXCEPTION_FIQ = (unsigned int)irq_handle;
	
	// 初始化中断控制器的基本寄存器
	intc_init();
}

// 清除需要处理的中断的中断处理函数的地址
void intc_clearvectaddr(void)
{
    VIC0ADDR = 0;
    VIC1ADDR = 0;
    VIC2ADDR = 0;
    VIC3ADDR = 0;
}

// 初始化中断控制器
void intc_init(void)
{
    //先关闭所有中断
    intc_disable(NUM_ALL);

    // 选择中断类型为IRQ
    VIC0INTSELECT = 0x0;
    VIC1INTSELECT = 0x0;
    VIC2INTSELECT = 0x0;
    VIC3INTSELECT = 0x0;

    // 清VICxADDR
    intc_clearvectaddr();
}

//注册真正的中断处理函数到VICnVECTADDR寄存器相应的某位中
void intc_setvectaddr(unsigned int intnum, void (*handler)(void))
{
    //VIC0
    if(intnum<32)
    {
        *( (volatile unsigned int *)(VIC0VECTADDR + 4*(intnum-0)) ) = (unsigned)handler;
    }
    //VIC1
    else if(intnum<64)
    {
        *( (volatile unsigned int *)(VIC1VECTADDR + 4*(intnum-32)) ) = (unsigned)handler;
    }
    //VIC2
    else if(intnum<96)
    {
        *( (volatile unsigned int *)(VIC2VECTADDR + 4*(intnum-64)) ) = (unsigned)handler;
    }
    //VIC3
    else
    {
        *( (volatile unsigned int *)(VIC3VECTADDR + 4*(intnum-96)) ) = (unsigned)handler;
    }
}


// 使能中断
// 通过传参的intnum来使能某个具体的中断源，中断号在int.h中定义，是物理中断号
//s5pv210使能中断寄存器设置写1有效（使能），写0不影响，所以可以直接改寄存器赋值，而不需要关心原来状态
void intc_enable(unsigned int intnum)
{
	// 确定intnum在哪个寄存器的哪一位
	// <32就是0～31，必然在VIC0
    if(intnum<32)
    {
        VIC0INTENABLE = (1 << intnum);
    }
    else if(intnum<64)
    {
        VIC1INTENABLE = (1 << (intnum-32));
    }
    else if(intnum<96)
    {
        VIC2INTENABLE = (1 << (intnum-64));
    }
    else if(intnum<NUM_ALL)
    {
        VIC3INTENABLE = (1 << (intnum-96));
    }
    // NUM_ALL : enable all interrupt
    else
    {
        VIC0INTENABLE = 0xFFFFFFFF;
        VIC1INTENABLE = 0xFFFFFFFF;
        VIC2INTENABLE = 0xFFFFFFFF;
        VIC3INTENABLE = 0xFFFFFFFF;
    }

}

// 禁止中断
// 通过传参的intnum来禁止某个具体的中断源，中断号在int.h中定义，是物理中断号
//s5pv210禁止中断寄存器设置写1有效（禁止），写0不影响，所以可以直接改寄存器赋值，而不需要关心原来状态
void intc_disable(unsigned int intnum)
{
    if(intnum<32)
    {
        VIC0INTENCLEAR = (1 << intnum);
    }
    else if(intnum<64)
    {
        VIC0INTENCLEAR = (1 << (intnum-32));
    }
    else if(intnum<96)
    {
        VIC0INTENCLEAR = (1 << (intnum-64));
    }
    else if(intnum<NUM_ALL)
    {
        VIC0INTENCLEAR = (1 << (intnum-96));
    }
    // NUM_ALL : disable all interrupt
    else
    {
        VIC0INTENCLEAR = 0xFFFFFFFF;
        VIC1INTENCLEAR = 0xFFFFFFFF;
        VIC2INTENCLEAR = 0xFFFFFFFF;
        VIC3INTENCLEAR = 0xFFFFFFFF;
    }
}


// 通过读取VICnIRQSTATUS寄存器，判断其中哪个有一位为1，来得知哪个VIC发生中断了
unsigned int intc_getvicirqstatus(unsigned int ucontroller)
{
    if(ucontroller == 0)
        return	VIC0IRQSTATUS;
    else if(ucontroller == 1)
        return 	VIC1IRQSTATUS;
    else if(ucontroller == 2)
        return 	VIC2IRQSTATUS;
    else if(ucontroller == 3)
        return 	VIC3IRQSTATUS;
    else
    {}
    return 0;
}


// 真正的中断处理程序。意思就是说这里只考虑中断处理，不考虑保护/恢复现场
void irq_handler(void)
{	
	// 虽然硬件已经自动帮我们把isr放入了VICnADDR中，但是因为有4个，所以我们必须
	// 查询到底哪个VIC中断了，也就是说isr到底在哪个VICADDR寄存器中
	unsigned int vicaddr[4] = {VIC0ADDR,VIC1ADDR,VIC2ADDR,VIC3ADDR};
    int i=0;
    void (*isr)(void) = NULL;

    for(i=0; i<4; i++)
    {
		// 发生一个中断时，4个VIC中有3个是全0，1个的其中一位不是0
        if(intc_getvicirqstatus(i) != 0)
        {
            isr = (void (*)(void)) vicaddr[i];
            break;
        }
    }
    (*isr)();		// 通过函数指针来调用函数
}
