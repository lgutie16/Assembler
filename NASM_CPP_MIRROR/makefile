runme: 
	nasm -f elf -l mir.lst mir.asm
	g++ -c includes.cpp
	g++ -g -o mir mir.o includes.o 
	rm mir.lst mir.o includes.o



