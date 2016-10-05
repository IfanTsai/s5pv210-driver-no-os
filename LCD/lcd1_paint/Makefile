lcd.bin: start.o  clock.o  sdram_init.o lcd.o main.o
	arm-linux-ld -Ttext 0xd0020010  -o lcd.elf $^
	arm-linux-objcopy -O binary lcd.elf lcd.bin
	arm-linux-objdump -D lcd.elf > lcd_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 lcd.bin 210.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib -std=c99

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
