#include <windows.h> // xu ly nhung thu lien quan den Win32
#include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
#include <iostream>	// thu vien INPUT OUTPUT
#include <stdlib.h> // thu vien chuan C
#include <fstream>	// thu vien xu ly FILE
#include <conio.h> 	// xu ly nhung thu lien quan den Console cmd
#include <vector>	// cau truc du lieu VECTOR
#include <map>		// cau truc du lieu MAP

int PROBSLOWERBOUND;

void SetColor(int value){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);	
}
//------------------------------------------------------------------------------------------------------------------------------------------//
int checkListProbs(short i,short j)
{
	if (i<2||j<1||i>PROBSLOWERBOUND||j>6) return 0;
	return 1;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void gotoXY(short x, short y)
{
    static HANDLE h = NULL;
    if(!h) h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {y,x};
    SetConsoleCursorPosition(h,c);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
int select(unsigned *X, unsigned *Y)
{
	char c;
	//do
	{
		c = getch();
		//std::cout << getch() << " " << getch() << " ";
		//std::cout << int(c) << " ";
		if (int(c) == -32) { // if the first value is esc
		    //getch(); // skip the [
		    switch( int(getch()) ) { // the real value
		        case 72:
		            if (checkListProbs( (*X)-1, (*Y) )) (*X)--;
		            break;
		        case 80:
		            if (checkListProbs( (*X)+1, (*Y) )) (*X)++;
		            break;
		        case 75:
		            if (checkListProbs( (*X), (*Y)-1 )) (*Y)--;
		            break;
		        case 77:
		            if (checkListProbs( (*X), (*Y)+1 )) (*Y)++;
		            break;
		    }
		    gotoXY((*X),(*Y));
		}
		else{
			
			if(int(c) == 0) {
				char cc = getch();
				if(int(cc) == 107) return -1;
				if(int(cc) == 63)  return -2;
			}

			switch(int(c)){
				case 32:	// SPACE
					return 1;
				case 13:	// ENTER
					return 2;
				case 104:	// h
				case 72:	// H
					return 3;
				default:
					return 0;
			}
		}
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void clrscr(int sh, int sv, int h, int v)
{
	char emptyline[v+2];
	memset(emptyline, ' ', v);
	emptyline[v] = '\n';
	emptyline[v+1] = '\0';

	gotoXY(sh, sv);
	for(int i = 0; i < h; i++) {
		//for(int j = 0; j < v; j++) std::cout << ' ';
		//std::cout << "\n";
		printf("%s", emptyline);
	}
	gotoXY(2,0);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void updateStatusBar(short interupt, std::string msg){
	//unsigned X = 0;
	gotoXY(0, 0);
	switch(interupt){
		case 0:
			return;
		default:
			SetColor(interupt);
			std::cout << msg;
			SetColor(7);
	}
	for(unsigned i = msg.length(); i < 108; i++) std::cout << ' ';
	//gotoXY(0, 108);
	printf("|\n");

	printf("---------------------------------------------| Control: [H][F5][UP][DOWN] | View: [SPACE] |");
	SetColor(15);
	printf(" SUBMIT: [ENTER]");
	SetColor(7);
	printf(" |\n");

	gotoXY(3, 0);
}
//------------------------------------------------------------------------------------------------------------------------------------------//
std::string to_s(int problem_id){
	std::string s = "";
	int d = 1000;

	while(d > 0){
		if(problem_id >= d) s += char((problem_id/d) + '0');
		else s += '0';
		problem_id %= d;
		d /= 10;
	}
	return s;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void displayHeading(){
	SetColor(10);
	std::cout << R"(                                                                                                                                                 )" << "\n";
	Sleep(150); std::cout << R"(  ,ad8888ba,                                                                                             88        88               88           )" << "\n";
	Sleep(150); std::cout << R"( d8"'    `"8b                             ,d                                           ,d                88        88               88           )" << "\n";
	Sleep(150); std::cout << R"(d8'                                       88                                           88                88        88               88           )" << "\n";
	Sleep(150); std::cout << R"(88              ,adPPYba,   8b,dPPYba,  MM88MMM  8b,dPPYba,  ,adPPYYba,   ,adPPYba,  MM88MMM  ,adPPYba,  88aaaaaaaa88  88       88  88,dPPYba,   )" << "\n";
	Sleep(150); std::cout << R"(88             a8"     "8a  88P'   `"8a   88     88P'   "Y8  ""     `Y8  a8"     ""    88     I8[    ""  88""""""""88  88       88  88P'    "8a  )" << "\n";
	Sleep(150); std::cout << R"(Y8,            8b       d8  88       88   88     88          ,adPPPPP88  8b            88      `"Y8ba,   88        88  88       88  88       d8  )" << "\n";
	Sleep(150); std::cout << R"( Y8a.    .a8P  "8a,   ,a8"  88       88   88,    88          88,    ,88  "8a,   ,aa    88,    aa    ]8I  88        88  "8a,   ,a88  88b,   ,a8"  )" << "\n";
	Sleep(150); std::cout << R"(  `"Y8888Y"'    `"YbbdP"'   88       88   "Y888  88          `"8bbdP"Y8   `"Ybbd8"'    "Y888  `"YbbdP"'  88        88   `"YbbdP'Y8  8Y"Ybbd8"'   )" << "\n";
	Sleep(150); std::cout << R"(------------------------------------------------------------------------------------------------  version 1.0.0  --------------------------------)" << "\n";
	//clrscr(0, 0, 100, 100);
	SetColor(7);
}