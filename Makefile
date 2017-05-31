# MAKEFILE
# Author: Kuziwa Sachikonye
# File Description: C Code Compiler
# Date: Thursday 1 October 2015

main.elf: main.o startup.o
	arm-none-eabi-ld -T linker.ld -nostartfiles -o main.elf main.o startup.o

main.s:  main.c
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m0 -g -S -Wall main.c

main.o: main.s
	arm-none-eabi-as -g -mcpu=cortex-m0 -mthumb -g -o main.o main.s

startup.o: startup.s
	arm-none-eabi-as -g -mcpu=cortex-m0 -mthumb -g -o startup.o startup.s

clean:
	rm *.o *.elf *.bin main.s

debug:
	open -a Terminal "`pwd`" | openocd -f interface/stlink-v2.cfg -f target/stm32f0x_stlink.cfg

run:
	arm-none-eabi-gdb main.elf