#include <windows.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <map>
using namespace std;

//////////////////////////////// COLOR
map <string, int> cl = {
	{"black", 0}, {"blue", 1}, {"green", 2}, {"aqua", 3},
	{"red", 4}, {"purple", 5}, {"yellow", 6}, {"white", 7},

	{"Black", 8}, {"Blue", 9}, {"Green", 10}, {"Aqua", 11},
	{"Red", 12}, {"Purple", 13}, {"Yellow", 14}, {"White", 15},
};
//////////////////////////////// FILE
string \
	FPROB = "probstatement.txt", \
	FLOOK = "\\P#",				 \
	FWD = "workingdir.string";

ifstream filewd (FWD);

string PWD;

string to_s(char *st);
void gotoXY(short x, short y);
void clrscr(int h);

void SetColor(string value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cl[value]);
}
//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
int main(int argc, char *argu[]){

	filewd >> PWD;
	filewd.close();
	//SetColor("White");

	FLOOK = PWD + FLOOK + to_s(argu[1]) + "\\" + FPROB;
	cout << FLOOK;

refresh:
	ifstream fpstate (FLOOK);
	string line;
	bool firstline = 0;

	if (fpstate.is_open()){
	    while (!fpstate.eof() ){
	    	if(!(firstline++)) SetColor("White");
	    	else SetColor("white");
	    	
	    	getline(fpstate, line);
	    	cout << endl << line;
	    }
	    fpstate.close();
	    do{
	    	if(int(getch()) == 13) {
	    		clrscr(200);
	    		goto refresh;
	    	}
	    } while(1);
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

void gotoXY(short x, short y)
{
    static HANDLE h = NULL;
    if(!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {y,x};
    SetConsoleCursorPosition(h,c);
}

void clrscr(int h)
{
	gotoXY(0,0);
	for(int i = 1; i <= h; i++) 
		cout<<"                                                                                                                   \n";
	gotoXY(0,0);
}