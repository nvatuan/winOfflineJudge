// #include <windows.h> // xu ly nhung thu lien quan den Win32
// #include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
// #include <iostream>	// thu vien INPUT OUTPUT
// #include <fstream>	// thu vien xu ly FILE
// #include <conio.h> 	// xu ly nhung thu lien quan den Console cmd
// #include <vector>	// cau truc du lieu VECTOR
// #include <map>		// cau truc du lieu MAP
#include "lorem-ipsum.hpp"
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
	FWD = "workingdir.string";
string \
	FPROB = "probstatement.txt", \
	FLOOK = "\\P#",				 \
	STATUSMSG = "";

struct statusVerboseExitcode{
	int no;
	int hello;
	int fnotfound;
} stt;

//////////////////////////////// INIT
vector< string > unsolved, attempted, solved;
vector< string > probs;
const int HSCREEN = 100;
const int VSCREEN = 100;
int maxlines = 0;

short statusupdated;
short statuscolor = 7;
int selected = -1;

char PWD[256]; 
size_t len = sizeof(PWD);

int folders;
int bytes;

unsigned X, Y;

////////////////////////////////////////////////////////////// FUNCTION //////////////////////////////////////////////////////////////
void SetColor(string value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cl[value]);
}

void initStatusExitcode(){
	stt.no = 0;
	stt.hello = 1;
	stt.fnotfound = 2;
}
///////////////////////////////////////////////////////////// PROTOTYPE /////////////////////////////////////////////////////////////
bool list_dir();
bool promptDir();
void concatnum(char s[], int num);
int ppstatement(int problem_id);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argu[]){

	if(argc == 1){
		system("START /MAX navigate.exe 0");
		exit(0);
	}

	initStatusExitcode();

	probs.clear();
	promptDir();
	// probs contains the folder;
	PROBSLOWERBOUND = probs.size()-1;
	PROBSLOWERBOUND += 2;
	
	clrscr(0, 0, HSCREEN, VSCREEN);

	gotoXY(2, 0);
	SetColor("white");
	for(unsigned i = 0; i < probs.size(); i++){
		cout << "[" << probs[i] << "]\n";
	}

	X = 2;
	Y = 1;
	do{
		SetColor("white");
		ppstatement(selected);

		if(statusupdated){
			updateStatusBar(statuscolor, STATUSMSG);
			statusupdated = 0;
		}
		gotoXY(X, Y);

		while(1){
			if(select(&X, &Y)) break;
		};
		selected = (X-2);

	} while(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------ END MAIN ------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ppstatement(int problem_id){
	//filewd >> PWD;
	//filewd.close();
	//SetColor("White");
	if(problem_id < 0 || 9999 < problem_id){
		statusupdated = 1;
		STATUSMSG = " Nothing is currently selected.";
		statuscolor = cl["white"];
		return 1;
	}

	string sPWD(PWD);
	string sFLOOK;

	sFLOOK = sPWD + FLOOK + to_s( problem_id ) + "\\" + FPROB;
	unsigned ppsX = 2, ppsY = 8;

	ifstream fpstate (sFLOOK);
	string line;
	bool bold = 0;
	int linecount = 0;

	//gotoXY(2, 8);
	if (fpstate.is_open()){
	    while (!fpstate.eof() ){
	    	gotoXY(ppsX++, ppsY);

	    	line = "                                                                                                   ";
	    	getline(fpstate, line);

			if(!(bold++)) SetColor("White");
	    	else SetColor("white");
	    	if(line == "INPUT:" || line == "OUTPUT:") SetColor("White");
	    	if(line[0]=='-'  && line[1]=='-' && line[2]=='[') SetColor("White");

	    	cout << "| ";
	    	int l = line.length();
	    	while(l++ < 100){
	    	 	line += ' ';
	    	}
	    	linecount++;
	    	cout << line;
	    }

	    maxlines = max(linecount, maxlines);
	    while(linecount++ <= maxlines){
	    	gotoXY(ppsX++, ppsY);
	     	cout << "                                                                                                     ";
	    }

	    fpstate.close();

	    //gotoXY(X, Y);
	    STATUSMSG = " SUCCESS: " + sFLOOK + " loaded";
	    statusupdated = 1;
	    statuscolor = cl["Green"];

	    gotoXY(selected+2, 0);

		cout << "[" << probs[selected] << "]";
		SetColor("White");
		cout << "->";

	    return 0;
	}
	else{
		STATUSMSG = " ERROR: " + sFLOOK + " not found";
		statusupdated = 1;

		gotoXY(selected+2, 0);
		statuscolor = cl["Red"];

		SetColor("red");
		cout << "[" << probs[selected] << "]";

		return 1;
	}
}	
//---------------------------------------------------------------------------------------------------------------------------------//
bool list_dir(){
	const char* PATH = ".";
    DIR *dir = opendir(PATH);
    struct dirent *entry = readdir(dir);

    SetColor("Green");
    cout << "./\n";

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR){
        	SetColor("white");
	        if((entry->d_name)[0] == 'P' || (entry->d_name)[1] == '#') {
        		probs.push_back(entry->d_name);
        		printf("| ");
        		SetColor("Green");
        		printf("%s\n", entry->d_name);
	        }
        }
        entry = readdir(dir);
    }
    if(!probs.size()) return 1;

    closedir(dir);
    SetColor("white");
    printf("|______     Press Enter to continue.\n");
    getchar();
    return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
bool promptDir(){
	getcwd( PWD, FILENAME_MAX );

	//ofstream filewd (FWD);
	//filewd << PWD;
	//filewd.close();

	while(1){
		cout << " Locating PROBLEMS_STATEMENTs folders...\n";
		cout << " > Your working directory is currently:\n";
		SetColor("Green");
		cout << "    " << PWD << "\n";
		SetColor("White");
		//SetColor("Yellow");
		if(list_dir()){
			cout << " > There is no PROBLEMS_STATEMENTs in your working directory.\n";
			exit(0);
		}
		else break;
		SetColor("white");
		cout << endl;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
void concatnum(char s[], int num){
	int i = 0;
	while(int(s[i]) != 0) i++;

	do {
		s[i] = char(num%10 + '0');
		i++;
		num /= 10;
	} while (num%10 > 0);
	s[i] = '\0';
}