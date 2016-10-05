buzzer.bin: start.o uart.o clock.o main.o buzzer.o		
	arm-linux-ld -Ttext 0xd0020010  -o buzzer.elf $^
	arm-linux-objcopy -O binary buzzer.elf buzzer.bin
	arm-linux-objdump -D buzzer.elf > buzzer_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 buzzer.bin 210.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib 

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
