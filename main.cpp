#include <iostream>	// thu vien INPUT OUTPUT
#include <fstream>	// thu vien xu ly FILE
#include <map>		// cau truc du lieu MAP
#include <windows.h> // xu ly nhung thu lien quan den CMD
using namespace std;

//////////////////////////////// FILE
string \
	FPROB = "probstatement.txt", \
	FIN = "", \
	WD = "";

ifstream fp (FPROB);

//////////////////////////////// COLOR
map <string, int> cl = {
	{"black", 0}, {"blue", 1}, {"green", 2}, {"aqua", 3},
	{"red", 4}, {"purple", 5}, {"yellow", 6}, {"white", 7},

	{"Black", 8}, {"Blue", 9}, {"Green", 10}, {"Aqua", 11},
	{"Red", 12}, {"Purple", 13}, {"Yellow", 14}, {"White", 15},
};

//////////////////////////////// FUNCTION
void SetColor(string value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cl[value]);
}

//////////////////////////////// MAIN
int main(){
	char pBuf[256]; size_t len = sizeof(pBuf);
	int bytes = GetModuleFileName(NULL, pBuf, len);
	//
	if(bytes == 0){
		cout << "Could not found the currect directory, this is a bug, please report back.\n";
	    return 0;
	}
	bool shown = 0;

	while(1){
		cout << "> Your working directory is currently:\n";
		SetColor("Green");
		cout << "    " << pBuf << "\n";
		SetColor("white");

		if(!shown){
			cout << "> If this is the folder you want, press Enter.\n";
			cout << "> Else paste below the folder path you want to go to.\n";
			shown++;
		}
		else{
			cout << "> Make change?\n";
		}

		SetColor("Yellow");
		cout << "<   ";
		fflush(stdin);
		cin >> WD;
		SetColor("white");
		cout << endl;
	}
}