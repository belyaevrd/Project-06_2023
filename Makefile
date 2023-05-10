.PHONY: all clean

all: func.o main.c
	gcc -m32 -no-pie main.c func.o -o main -lm
func.o: func.asm
	nasm -f elf32 func.asm -o func.o
clean: 
	rm func.o
