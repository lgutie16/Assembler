#include <unistd.h>
#define cimg_OS 0
#define cimg_display 0
#include "CImg.h"
#include <iostream>

using namespace cimg_library;
using namespace std;


int loadimg(char* arg){
	printf("hello");
	return 7;
}

int saveimg(char* arg){
	printf("hello");
	return 8;
}

int getdims(){
	printf("hello");
	return 9;
}
	
	
void pixchange(int p1, int p2){
	printf("hello");
}


int array(int a[], int length);   // external ASM procedure

int main()
{
  	printf ("hello world\n");
    return 0;
}