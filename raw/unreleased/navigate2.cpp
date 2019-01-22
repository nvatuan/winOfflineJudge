// #include <windows.h> // xu ly nhung thu lien quan den Win32
// #include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
// #include <iostream>	// thu vien INPUT OUTPUT
// #include <fstream>	// thu vien xu ly FILE
// #include <conio.h> 	// xu ly nhung thu lien quan den Console cmd
// #include <vector>	// cau truc du lieu VECTOR
// #include <map>		// cau truc du lieu MAP
#include "lorem-ipsum2.hpp"
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
vector< string > statementLines;

vector< bool > existStatement;
vector< string > probs;
const int HSCREEN = 100;
const int VSCREEN = 100;

string statustext;
int SCRH_CALI = 45;
int SCRV_CALI = 63;
int maxlines = 0;

short statusupdated;
short statuscolor = 7;

int validselected = -1;
int selected = -1;

char* absPWD;
char PWD[1024]; 
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
bool screenCalibrate();
void submitConsolePop();
void updateStatusBar(short interupt, string msg);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argu[]){

	if(argc == 1){
		system("START /MAX navigate2.exe 0");
		exit(0);
	}
	else{
		initStatusExitcode(); promptDir(); PROBSLOWERBOUND = probs.size()+1;
		clrscr(0, 0, HSCREEN, VSCREEN);
	}
	
reloadDisplay:
	gotoXY(2, 0);
	SetColor("white");

	//clrscr(2, 0, SCRHCALIBRATE, 8);
	clrscr(2, 0, HSCREEN, VSCREEN);

	for(unsigned i = 0; i < probs.size(); i++){
		string sPdetailsPath = string(absPWD) + "\\" + probs[i] + "\\pdetails";
		ifstream fPdetails( sPdetailsPath );
		if(fPdetails.is_open()){
			int problemStatus = 0;

			fPdetails >> problemStatus;
			fPdetails.close();

			switch(problemStatus){
				case 100:
					SetColor("Green");
					break;
				case -1:
					SetColor("Red");
					break;
				case -2:
					SetColor("red");
					break;
				default:
					SetColor("white");
					break;
			}
		}
		else{
			SetColor("white");
		}
		if(!existStatement[i]) SetColor("Black");
		cout << "[" << probs[i] << "]";
		SetColor("white");
		if(i != selected) cout << "|\n";
		else cout << "\n";
	}
	cout << "--------|\n";

	X = 2;
	Y = 1;
	bool submitting = 0;
	do{
		SetColor("white");
		if(ppstatement(selected)); //ppstatement(validselected);

		if(statusupdated){
			updateStatusBar(statuscolor, STATUSMSG);
			statusupdated = 0;
		}
		gotoXY(X, Y);

		if(submitting){
			submitting = 0;
			submitConsolePop();
		}

		while(1){
			switch(select(&X, &Y)){
				case -2:
					goto reloadDisplay;
				case -1:
					exit(0);
				case 1:		// Selected Statement
					goto breakoutSelecting;
				case 2: 	// Submit statement
					submitting = 1;
					goto breakoutSelecting;
				case 3: 
					screenCalibrate();
					goto reloadDisplay;
				default:;
			}
		};
breakoutSelecting:
		selected = (X-2);

	} while(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------ END MAIN ------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void submitConsolePop(){
	string cmdSubmitStr = "START submit.exe " + string(absPWD) + '\\' + probs[X-2];
	system(cmdSubmitStr.c_str());
	return;
}
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

	string sPWD(absPWD);
	string sFLOOK;
	sFLOOK = sPWD + FLOOK + to_s( problem_id ) + "\\" + FPROB;

	ifstream fpstate (sFLOOK);
	string line;

	bool bold = 0;
	int linecount = 0;
	unsigned ppsX = 2, ppsY = 8;

	//gotoXY(2, 8);
	statementLines.clear();

	if (fpstate.is_open()){
	    while (!fpstate.eof() ){
	    	getline(fpstate, line);
	    	
	    	int l = line.length();
	    	while(l++ < 100){
	    	 	line += ' ';
	    	}
	    	linecount++;

	    	statementLines.push_back(line);
	    }
	    fpstate.close();

		gotoXY(ppsX++, ppsY);

		if(!(bold++)) SetColor("White");
    	else SetColor("white");
    	if(line == "INPUT:" || line == "OUTPUT:") SetColor("White");
    	if(line[0]=='-'  && line[1]=='-' && line[2]=='[') SetColor("White");

    	cout << "| ";





	    maxlines = max(linecount, maxlines);
	    while(linecount++ <= maxlines){
	    	gotoXY(ppsX++, ppsY);
	     	cout << "                                                                                                     ";
	    }

	    STATUSMSG = " SUCCESS: " + sFLOOK + " loaded";
	    statusupdated = 1;
	    statuscolor = cl["Green"];

	    gotoXY(selected+2, 8);
		cout << "=>";

		validselected = selected;
	    return 0;
	}
	else{
		STATUSMSG = " ERROR: NO PROBLEM STATEMENT. \"" + sFLOOK + "\" not found";
		statusupdated = 1;

		gotoXY(selected+2, 0);
		statuscolor = cl["Red"];

		existStatement[selected] = 0;
		SetColor("Black");
		cout << "[" << probs[selected] << "]";
		selected = validselected;

		return 1;
	}
}	
//---------------------------------------------------------------------------------------------------------------------------------//
bool list_dir(){
	string sPATH = string(PWD);
	sPATH += "\\data";

	absPWD = (char*) malloc( (sPATH.length() + 1)*sizeof(char) );
	strcpy(absPWD, sPATH.c_str());
	//cout << "list_dir(): " << absPWD << endl;
	//char* PATH = ".";

    DIR *dir = opendir(absPWD);
    struct dirent *entry = readdir(dir);

    SetColor("Green");
    cout << "./\n";

    while (entry != NULL)
    {
        if (entry->d_type == DT_DIR){
        	SetColor("white");
	        if((entry->d_name)[0] == 'P' || (entry->d_name)[1] == '#') {
        		probs.push_back(entry->d_name);
        		existStatement.push_back(1);

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
bool screenCalibrate(){

refresh:
	//clrscr(2, 0, 100, 70);
	clrscr(0, 0, HSCREEN, VSCREEN);

	STATUSMSG        = " ! [UP]/[DOWN] to set the HEIGHT of your text display,[ESC] to redo, [ENTER] to finish !";

	string border    = "        V__________________________________________________";
	string clrborder = "|                                                  ";

	int X = 30;
	int Y = 0;
	
	for(int i = 2; i < X; i++){
		cout << "        |\n";
	}
	cout << border << endl;

	while(1){
		updateStatusBar(cl["White"], STATUSMSG);
		
		gotoXY(X, Y);
		cout << X;
		gotoXY(X, 8);

		char c = getch();
		switch(int(c)){
			case 72:
				if(X > 20) {
					cout << clrborder;
					X--;
					gotoXY(X, Y);
					cout << border << endl;
				}
				break;
			case 80:
				if(X < 80) {
					cout << clrborder;
					X++;
					gotoXY(X, Y);
					cout << border << endl;
				}
				break;
			case 13:
				SCRH_CALI = X;
				goto jumptoScreenVerticalCalibrate;
			case 27:
				goto refresh;
			//default:
		}
	}
	
jumptoScreenVerticalCalibrate:
	STATUSMSG        = " ! [LEFT]/[RIGHT] to set the WIDTH of your text display, [ESC] to redo, [ENTER] to finish !";

	string border2    = ">|";
	string clrborder2 = "  ";

	X = SCRH_CALI;
	Y = 20;
	
	gotoXY(X, 0);
	cout << Y;
	gotoXY(X, 9);
	for(int i = 9; i < Y-2; i++){
		cout << "-";
	}
	cout << border2;

	while(1){
		updateStatusBar(cl["White"], STATUSMSG);
		gotoXY(X, Y);
		cout << (Y-9);

		char c = getch();
		switch(int(c)){
			case 75:	//LEFT
				if(Y > 20) {
					gotoXY(X, Y-3);
					cout << border2;
					cout << "   ";
					//cout << clrborder2;
					Y--;
					gotoXY(X, Y);
					//cout << border2;
				}
				break;
			case 77:	//RIGHT
				if(Y < 100) {
					gotoXY(X, Y-2);
					cout << "-";
					cout << border2;
					Y++;
					gotoXY(X, Y);
					//cout << border << endl;
				}
				break;
			case 13:
				SCRV_CALI = Y;
				goto jumpoutScreenCalibrate;
			case 27:
				goto refresh;
			//default:
		}
	}
jumpoutScreenCalibrate:
	
	statustext = "";
	for(int i = 0; i <= SCRV_CALI; i++) statustext += '-';
	
	gotoXY(0, 0);
	cout << statustext << endl << statustext;
	system("pause > nul");
	statusupdated = 1;
	STATUSMSG = "Nothing is currently selected.";
	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
bool promptDir(){
	getcwd( PWD, FILENAME_MAX );

	//cout << "promptDir(): " << PWD << endl;

	while(1){
		cout << " Locating \\data\\ folders...\n";
		cout << " > Your working directory currently is:\n";
		SetColor("Green");
		cout << PWD << "\\data\\"<< "\n";
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
//------------------------------------------------------------------------------------------------------------------------------------------//
void updateStatusBar(short interupt, string msg){
	unsigned X = 0;
	gotoXY(0, 0);
	switch(interupt){
		case 0:
			return;
		default:
			SetColor(interupt);
			std::cout << msg;
			SetColor(7);
	}
	
	for(unsigned i = msg.length(); i <= SCRV_CALI; i++) cout << ' ';
	printf("|\n");
	string controlpanel = "| Control: [H][F5][UP][DOWN] | View: [SPACE] |";
	gotoXY(1, SCRV_CALI - controlpanel.length() - 16); //SUBMIT: [ENTER] length
	cout << controlpanel;
	
	SetColor(15);
	printf(" SUBMIT: [ENTER]");
	SetColor(7);
	printf(" |\n");

	gotoXY(3, 0);
}
