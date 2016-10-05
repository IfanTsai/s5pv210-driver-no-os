//2016年08月28日11:33:17
/*
* note:
* 调用函数时使用bl指令，bl指令会在跳转前把地址写到lr寄存器中，所以在写函数体时结束要用mov pc，lr返回
* mov pc, lr把调用前的地址放到pc中，pc是程序指针
*/
#define GPJ0CON 0xe0200240
#define GPJ0DAT 0xe0200244

.global _start
_start:
	ldr r0, =0x11111111
	ldr r1, =GPJ0CON
	str r0, [r1]
_loop:
	ldr r0, =0x00
	ldr r1, =GPJ0DAT
	str r0, [r1]
	bl _delay
	ldr r0, =0xff
	ldr r1, =GPJ0DAT
	str r0, [r1]
	bl _delay
	b _loop


_delay:
	ldr r2, =8000000
_delay_loop:
	sub r2, r2, #1
	cmp r2, #0        //相等则cpsr寄存器中的z位置1	 
	bne _delay_loop   //不相等则跳转（内部是根据cpsr寄存器中的z位来判断）
    mov pc, lr
