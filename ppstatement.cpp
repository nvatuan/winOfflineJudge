#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>
using namespace std;

string \
	FPROB = "probstatement.txt", \
	FLOOK = "\\P#",				 \
	FWD = "workingdir.string";

ifstream filewd (FWD);

string PWD;

string to_s(char *st);

//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
int main(int argc, char *argu[]){

	filewd >> PWD;
	filewd.close();

	FLOOK = PWD + FLOOK + to_s(argu[1]) + "\\" + FPROB;
	cout << FLOOK;

	ifstream fpstate (FLOOK);
	string line;

	if (fpstate.is_open()){
	    while (! fpstate.eof() ){
	    	getline(fpstate, line);
	    	cout << endl << line;
	    }
	    fpstate.close();
	}
	else{
		cout << endl << "  ERROR: " << FLOOK << " not found!\n";
	}
}
//------------------------------------------------------------ END MAIN ------------------------------------------------------------//
string to_s(char *st){
	if(st[0] < '0' && st[0] > '9') exit(0);

	int i = 0;
	int num = 0;
	while('0' <= st[i] && st[i] <= '9'){
		num = num*10 + (st[i] - '0');
		i++;
	}

	if(num < 0 || num > 9999){
		cout << "Invalid file No. " << num << endl;
		system("pause");
		exit(0);
	}

	string s = "";
	int d = 1000;

	while(d > 0){
		if(num >= d) s += char((num/d) + '0');
		else s += '0';
		num %= d;
		d /= 10;
	}
	return s;
}