CC		= arm-linux-gcc
LD 		= arm-linux-ld
OBJCOPY	= arm-linux-objcopy
OBJDUMP	= arm-linux-objdump
AR		= arm-linux-ar

INCDIR	:= $(shell pwd)
# C预处理器的flag，flag就是编译器可选的选项
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include -std=c99
# C编译器的flag
CFLAGS		:= -Wall -O2 -fno-builtin

#导出这些变量到全局，其实就是给子文件夹下面的Makefile使用
export CC LD OBJCOPY OBJDUMP AR CPPFLAGS CFLAGS


objs := start.o uart.o clock.o main.o myshell.o clib.o cmd.o

x210_simple_shell.bin: $(objs)
	$(LD) -Ttext 0xd0020010 -o x210_simple_shell.elf $^
	$(OBJCOPY) -O binary x210_simple_shell.elf x210_simple_shell.bin
	$(OBJDUMP) -D x210_simple_shell.elf > x210_simple_shell_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 x210_simple_shell.bin 210.bin

	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	