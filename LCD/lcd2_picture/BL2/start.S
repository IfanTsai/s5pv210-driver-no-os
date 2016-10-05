//2016年09月23日17:50:03
#define WTCON     0xe2700000
#define SVC_STACK 0xd0037d80

.global _start
_start:
	bl main 
	b .
