//2016年08月29日21:06:27
//该启动代码做的一系列动作，其实在iROM中的bl0已经做了
//2016年08月31日16:18:55
//该代码假设运行地址为0xd0020010，链接地址为0xd0024000
//做了一个运行地址到链接地址的重定位

/*notes:
*bss段只在程序运行前才开辟并清零，实际上bss段不占用可执行文件的大小(只记录起始和结束地址),
*bss段一般是不需要手动清零的，编译器会在我们需要执行的程序前添加一个汇编头程序,
*这段头程序就会在main函数执行前初始化c语言的运行时环境,
*运行时环境要求其中就有bss段的变量清0,
*但是重定位后那段代码在运行时才有的，编译器并不知道它的存在，
*所以需要我们手动去清零.
*
*
*而为什么只需要重定位代码段和数据段,而不需要重定位bss段?
*是因为还没到执行main函数前(在该start.S中)就需要重定位,此时还没开始清零bss段,
*bss段为非零值,因此也就不需要重定位bss段了(而是重定位后手动清零).
*/
#define WTCON     0xe2700000
#define SVC_STACK 0xd0037d80

.global _start
_start:
	/*关看门狗*/
	ldr r0, =0x0	
	ldr r1, =WTCON
	str r0, [r1]
	
    /*设置SVC栈（满减栈）*/
	ldr sp, =SVC_STACK

	/*初始化icache*/
	mrc p15, 0, r0, c1, c0, 0//读出cp15的值到r0中
	//bic r0, r0, #(1 << 12)//bit12为0 关icache（bic为位清零）
	orr r0, r0, #(1 << 12)//bit12为0 开icache（orr为按位或）
	mcr p15, 0, r0, c1, c0, 0//把r0的值写到cp15中

	/*判断链接地址和运行地址是否相等*/	
	adr r0, _start//短加载，加载的是运行地址
	ldr r1, =_start//长加载，加载的是链接地址
	ldr r2, =bss_start
	cmp r0, r1
	beq bss_clean

copy_loop:
	ldr r3, [r0], #4
	str r3, [r1], #4
	cmp r3, r2
	bne copy_loop

bss_clean:
	ldr r0, =bss_start
	ldr r1, =bss_end
	cmp r0, r1
    beq led_run	//r0和r1的值相等表示bss段为空，即无未初始化的全局变量
	mov r2, #0
	
clean_loop:
	str r2, [r0], #4
	cmp r0, r1
	bne clean_loop

led_run:
	ldr pc, =main//长跳转，跳转到重定位后的代码
	//bl main//短跳转
	b .
