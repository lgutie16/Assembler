runme: manage_image.cpp asm.o
	 g++ manage_image.cpp asm.o -o runme

asm.o: main.asm 
	 nasm -f elf32 main.asm -o asm.o