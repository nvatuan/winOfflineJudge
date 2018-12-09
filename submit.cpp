// #include <windows.h> // xu ly nhung thu lien quan den Win32
// #include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
// #include <iostream>	// thu vien INPUT OUTPUT
// #include <fstream>	// thu vien xu ly FILE
// #include <conio.h> 	// xu ly nhung thu lien quan den Console cmd
// #include <vector>	// cau truc du lieu VECTOR
// #include <map>		// cau truc du lieu MAP
#include "lorem-ipsum.hpp"
using namespace std;

//////////////////////////////////// INIT ////////////////////////////////////
vector <string> exefiles;
char PWD[1024];

bool nofiles = 1;
unsigned execount = 0;
///////////////////////////////// PROTOTYPE //////////////////////////////////
bool isExecutable(const char *fspec);
int checkBounds(short i,short j); 
int sselect(unsigned *X, unsigned *Y);
int selectExecutable();
void makeSourceFile();
int judge();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argu[]){

	if(argc == 1) return 0;

	//char surfix[] = "\\testcases\\";

	char * PATH = new char[strlen(argu[1])];//+ strlen(surfix) + 1];

	strcpy(PATH, argu[1]);
	//strcat(PATH, surfix);

    DIR *dir = opendir(PATH);
    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        if (entry->d_type != DT_DIR){
        	nofiles = 0;
        	//cout << entry->d_name << endl;
        	if(isExecutable(entry->d_name)){
        		execount++;
        		exefiles.push_back( string(entry->d_name) );
        	}
        }
        entry = readdir(dir);
    }
    clrscr(0, 0, 100, 100);
    gotoXY(0, 0);

    SetColor(15);
    cout << " .EXE METHOD: select one of the .exe files below\n";
    cout << "--------------------------------------------------\n";
    SetColor(7);
    if(!nofiles){
    	cout << "At " << argu[1] << endl;
    	cout << " [" << execount << "] .exe file(s) were found: " <<  endl;
    	SetColor(2);
    	for(unsigned i = 0; i < execount; i++){
    		cout << "   > " << exefiles[i] << endl;
    	}
    	SetColor(7);

    	selectExecutable(); //Return submission exe
    }
    else{
    	cout << "NO .EXE FILES FOUND, CODE-PASTING METHOD IS USED\n";
    	cout << "CODE-PASTING NOT IMPLEMENTED!/n";
    }
    cout << "\n";
/*
    SetColor(15);
    cout << " CODE-PASTING METHOD: paste your code below then ENTER\n";
    cout << "--------------------------------------------------\n";
    SetColor(7);
*/
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------- END MAIN --------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int checkBounds(unsigned i, unsigned j)
{
	if (i<4||j<3||i>(execount+3)||j>3) return 0;
	return 1;
}

int selectExecutable(){
	unsigned sX = 4, sY = 3;
	unsigned pvX = 4;

	gotoXY(sX, sY);
	while(1){

		SetColor(10);
		cout << "> " << exefiles[sX - 4] << endl;
		gotoXY(sX, sY);
		pvX = sX;

		switch(sselect(&sX, &sY)){
			case 1:
			case 2:
				return (sX - 4);
			default:;
		}

		SetColor(2);
		cout << "> " << exefiles[pvX - 4] << endl;
		gotoXY(sX, sY);
	}
}

int sselect(unsigned *X, unsigned *Y)
{
	char c;
	//do
	{
		c = getch();
		//std::cout << int(c) << " ";
		if (int(c) == -32) { // if the first value is esc
		    //getch(); // skip the [
		    switch( int(getch()) ) { // the real value
		        case 72:
		            if (checkBounds( (*X)-1, (*Y) )) (*X)--;
		            break;
		        case 80:
		            if (checkBounds( (*X)+1, (*Y) )) (*X)++;
		            break;
		        case 75:
		            if (checkBounds( (*X), (*Y)-1 )) (*Y)--;
		            break;
		        case 77:
		            if (checkBounds( (*X), (*Y)+1 )) (*Y)++;
		            break;
		    }
		    //gotoXY((*X),(*Y));
		}
		else{

			if(int(c) == 0) if(int(getch()) == 107) return -1;

			switch(int(c)){
				case 32:	// SPACE
					return 1;
				case 13:	// ENTER
					return 2;
				default:
					return 0;
			}
		}
	}
	return 0;
}

bool isExecutable(const char *fspec){
	char *e = strrchr (fspec, '.');
	return !strcmp(e, ".exe");
}