
main:
	nasm -f elf32 func.asm -o func.o
	gcc -m32 main.c func.o -o main

clear:
	rm func.o
