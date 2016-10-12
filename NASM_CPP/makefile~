runme: practica2.cpp asm.o
	 g++ practica2.cpp asm.o -o runme

asm.o: proceso.asm 
	 nasm -f elf32 proceso.asm -o asm.o