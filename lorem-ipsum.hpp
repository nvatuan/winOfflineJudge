#include <windows.h> // xu ly nhung thu lien quan den Win32
#include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
#include <iostream>	// thu vien INPUT OUTPUT
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
		c=getch();
		switch(int(c)){
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
			case 32:
				return 1;
			case 13:
				return 1;
			default:
				return 0;
		}
		gotoXY((*X),(*Y));
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void clrscr(int sh, int sv, int h, int v)
{
	for(int i = 0; i < h; i++) {
		gotoXY(sh+i, sv);
		for(int j = 0; j < v; j++) std::cout << ' ';
		std::cout << "\n";
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
	printf("------------------------------------------------------------------------------------------------------------|\n");
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