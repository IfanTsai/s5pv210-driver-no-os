key.bin: start.o key.o clock.o main.o led.o
	arm-linux-ld -Ttext 0xd0020010  -o key.elf $^
	arm-linux-objcopy -O binary key.elf key.bin
	arm-linux-objdump -D key.elf > key_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 key.bin 210.bin
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c -nostdlib

%.o : %.c
	arm-linux-gcc -o $@ $< -c -nostdlib 

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f

	
	
