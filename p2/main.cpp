#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

extern "C" int proceso(int *data, int size);

//https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Insertion_sort#NASM

void saveData(int data[], int numbers){
	 ofstream salida;
	 salida.open ("salida.txt");
	  for (int i = 0; i < numbers; ++i){
	  	salida << data[i] << '\n';
	  }
	  salida.close();
}

void showData(){
	string line;
	ifstream salida("salida.txt");
	if (salida.is_open()){
	  while (getline (salida,line)){
	    cout << line << '\n';
	  }
	  salida.close();
	}else cout << "Unable to open file";
}


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
	  //File specifications	
	  int numbers = rand() % 1000 + 10;  
	  cout << "Generate Numbers: " << numbers << endl;  
	  int number;	  
	  int numbersList[numbers];

	  //File Creation :: Saving ramdom data
	  ofstream aleatorio;
	  aleatorio.open ("aleatorio.txt");
	  for (int i = 0; i < numbers; ++i){
	  	number = rand();
	  	aleatorio << number << '\n';
	  	numbersList[i] = number;
	  }
	  aleatorio.close();	

	  //Exec Insertion sort
	  proceso(numbersList, numbers);

	  //Save Sort Array in salida.txt
	  cout << "Generating file... " << endl;
	  saveData(numbersList, numbers);	  
}




int main () {
	  int selection;
	  cout << "************************" << endl;
	  cout << "************************" << endl;
	  cout << "************************" << endl;
	  cout << "****Select an option****" << endl;
	  cout << "1. just read an file with given numbers" << endl;
	  cout << "2. create a file, generate numbers and read it" << endl;
	  cout << "************************" << endl;
	  cout << "************************" << endl;

	  cin >> selection;
	  if (selection == 1){
	  	option1();
	  }else if (selection == 2){
	  	option2();
	  }else{
	  	cout << "**Wrong selection**" << endl;
	  }


	  cout << "************************" << endl;
	  cout << "************************" << endl;
	  cout << "**Press 1 to Show file**" << endl;
	  cout << "************************" << endl;
	  cout << "************************" << endl;
	  cin >> selection;
	  if (selection == 1){
	  	showData();
	  }else {
	  	cout << "**Wrong selection**" << endl;
	  }
	return 0;
}