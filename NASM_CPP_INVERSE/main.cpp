#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <typeinfo>	
using namespace std;

extern "C" int proceso(int *data, int size);



void saveData(int data[], int numbers){
	 ofstream salida;
	 salida.open ("salida.txt");
	  for (int i = 0; i < numbers-1; ++i){
	  	salida << data[i] << '\n';
	  }
	  salida.close();

}

//https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Insertion_sort#NASM
//edx
extern "C"
void sort(int data[], int numbers){
	int temp = 0;
	for (int i = 0; i < numbers; ++i){
		temp = data[i];
		int j = i;
		while(j>0 and temp < data[j-1]){
			data[j] = data[j-1];
			j--;
		}	
		data[j] = temp;
	}

	 saveData(data, numbers);
}

void showData(){
	string line;
	ifstream salida("salida.txt");
	if (salida.is_open()){
	  while (getline (salida,line)){
	    cout << line << '\n';
	  }
	  salida.close();
	}else cout << "Unable to open file" << endl;
}

int countNumbers(){
	string line;
	int n = 0;
	ifstream aleatorio("aleatorio.txt");
	if (aleatorio.is_open()){
	  while (getline(aleatorio,line)){
	    n++;
	  }
	}else cout << "Unable to open file";
	return n;
}

void option1(){
	int i = countNumbers();
	if (i>9 && i<1001)
	{
		cout << "Numbers to sort: " << i << endl;
		int numbersList[i];
		int j = 0;
		int n = 0;
		string line;
		ifstream aleatorio("aleatorio.txt");		
		if (aleatorio.is_open()){
		  while (getline(aleatorio,line)){
		  	int n;
			istringstream ( line ) >> n;
		    numbersList[j] = n;
		    j++;
		  }
		  aleatorio.close();
		}else cout << "Unable to open file";

		//Exec Insertion sort
	    proceso(numbersList, j);

		//Save Sort Array in salida.txt
		cout << "Generating file... " << endl;
		saveData(numbersList, j);
	}		
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
	  	number = rand() % 1000 + 1;
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
	  cout << "******************************************************" << endl;
	  cout << "******************************************************" << endl;
	  cout << "******************************************************" << endl;
	  cout << "******************Select an option********************" << endl;
	  cout << "****1. just read an file with given numbers***********" << endl;
	  cout << "****2. create a file, generate numbers and read it****" << endl;
	  cout << "******************************************************" << endl;
	  cout << "******************************************************" << endl;

	  cin >> selection;
	  if (selection == 1){
	  	option1();
	  }else if (selection == 2){
	  	option2();
	  }else{
	  	cout << "**Wrong selection**" << endl;
	  }


	  cout << "******************************************************" << endl;
	  cout << "******************************************************" << endl;
	  cout << "*****************Press 1 to Show file*****************" << endl;
	  cout << "******************************************************" << endl;
	  cout << "******************************************************" << endl;
	  cin >> selection;
	  if (selection == 1){
	  	showData();
	  }else {
	  	cout << "**Wrong selection**" << endl;
	  }
	return 0;
}