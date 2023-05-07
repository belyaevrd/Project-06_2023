
main:
	nasm -f elf32 func.asm -o func.o
	gcc -m32 -no-pie main.c func.o -o main

clear:
	rm func.o
