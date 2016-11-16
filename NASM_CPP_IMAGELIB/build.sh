nasm -f elf -l main.lst main.asm
g++ -c manage_image.cpp
g++ -nostdlib -m32 -g -o main main.o manage_image.o 
rm main.lst main.o manage_image.o

