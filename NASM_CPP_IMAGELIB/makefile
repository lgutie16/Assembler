all: runme

runme:  asm.o manage_image.o
	 g++ manage_image.o asm.o -I /opt/fred -o runme

manage_image.o: manage_image.cpp 	
	 g++ -o hello_word.exe hello_world.cpp -I /opt/fred -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
	 
asm.o: asm.asm
	 nasm -f elf32 asm.asm -o asm.o
	
clean:
	rm -rf *.o runme