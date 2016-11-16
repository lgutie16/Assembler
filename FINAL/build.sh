nasm -f elf32 -o proceso.o proceso.asm
gcc -o sum proceso.o main.cpp 