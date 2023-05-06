func:
	nasm -f -elf32 func.asm -o func.o
main: func
	gcc main.c func.o -o main

clear:
	rm func.o
