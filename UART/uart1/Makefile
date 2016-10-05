uart.bin: start.o uart.o clock.o main.o
	arm-linux-ld -Ttext 0xd0020010  -o uart.elf $^
	arm-linux-objcopy -O binary uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 uart.bin 210.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib 

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
