//2016年08月28日15:37:44
#define GPJ0CON 0xe0200240
#define GPJ0DAT 0xe0200244

.global _start
_start:
	ldr r0, =0x11111111
	ldr r1, =GPJ0CON
	str r0, [r1]
_loop:
	ldr r0, =~(0x01 << 3)
	ldr r1, =GPJ0DAT
	str r0, [r1]
	bl _delay

	ldr r0, =~(0x01 << 4)
	ldr r1, =GPJ0DAT
	str r0, [r1]
	bl _delay

    ldr r0, =~(0x01 << 5)
	ldr r1, =GPJ0DAT
	str r0, [r1]
	bl _delay

	b _loop 
	

_delay:
	ldr r2, =0x400000
_delay_loop:
	sub r2, r2, #1
	cmp r2, #0
	bne _delay_loop	
	mov pc, lr
