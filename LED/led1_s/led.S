//2016年08月28日11:19:27
#define GPJ0CON 0xe0200240
#define GPJ0DAT 0xe0200244
#define GPD0CON 0xe02000a0
#define GPD0DAT 0xe02000a4

.global _start
_start:
	ldr r0, =0x11111111
	ldr r1, =GPJ0CON
	str r0, [r1]
	
	ldr r0, =0x11111111
	ldr r1, =GPD0CON
	str r0, [r1]

	ldr r0, =~( (0x01 << 3) | (0x01 << 4) | (0x01 << 5) )//低电平亮
	ldr r1, =GPJ0DAT
	str r0, [r1]

	ldr r0, =0x00
	ldr r1, =GPD0DAT
	str r0, [r1]

	b .
	
