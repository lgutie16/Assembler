runme: main.cpp asm.o
	 g++ main.cpp asm.o -o runme

asm.o: proceso.asm 
	 nasm -f elf32 proceso.asm -o asm.o
