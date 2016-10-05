wdt.bin: start.o  clock.o led.o main.o interrupt.o uart.o wdt.o	
	arm-linux-ld -Ttext 0xd0020010  -o wdt.elf $^
	arm-linux-objcopy -O binary wdt.elf wdt.bin
	arm-linux-objdump -D wdt.elf > wdt_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 wdt.bin 210.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib -std=c99

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib -std=c99

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
