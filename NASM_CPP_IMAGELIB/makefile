runme: main.o manage_image.exe
	 nasm -f elf32 main.asm -o main.o 
	 ld -s -o runme main.o 

manage_image.exe: manage_image.cpp asm.o
	 g++ -o manage_image.exe manage_image.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
	