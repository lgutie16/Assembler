// basic file operations
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>


using namespace std;


void option1(){
	string line;
	ifstream aleatorio("aleatorio.txt");
	if (aleatorio.is_open()){
	  while (getline (aleatorio,line)){
	    cout << line << '\n';
	    //pasar line a entero y guardar  en array
	  }
	  aleatorio.close();
	}else cout << "Unable to open file";	
	//llamar proceso sort assembly 
}

void option2(){
	  int numbers = rand() % 10 + 1000;    
	  int number;
	  ofstream aleatorio;
	  int numbersList[numbers];
	  aleatorio.open ("aleatorio.txt");
	  for (int i = 0; i < numbers; ++i)
	  {
	  	number = rand();
	  	aleatorio << number << '\n';
	  	numbersList[i] = number;
	  }
	  aleatorio.close();	

	  //llamar proceso sort assembly 
}


int main () {
	  cout << "**Select an option**" << endl;
	  cout << "1. just read an file with given numbers" << endl;
	  cout << "2. create a file, generate numbers and read it" << endl;
	  cin >> selection;
	  if (selection == 1){
	  	option1();
	  }else if (selection == 2){
	  	option2();
	  }else{
	  	cout << "**Wrong selection**" << endl;
	  }
	return 0;
}