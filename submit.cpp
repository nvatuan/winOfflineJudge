// #include <windows.h> // xu ly nhung thu lien quan den Win32
// #include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
// #include <iostream>	// thu vien INPUT OUTPUT
// #include <fstream>	// thu vien xu ly FILE
// #include <conio.h> 	// xu ly nhung thu lien quan den Console cmd
// #include <vector>	// cau truc du lieu VECTOR
// #include <map>		// cau truc du lieu MAP
#include "lorem-ipsum.hpp"
#include <tchar.h>		// kieu du lieu dac biet, khong can quan tam
using namespace std;

//////////////////////////////////// INIT ////////////////////////////////////
vector <string> exefiles;
string sPATH;
//string JUDGECOMMAND;

char * PATH;

unsigned execount = 0;
///////////////////////////////// INIT JUDGE /////////////////////////////////
int STATUS;
int TESTSCOUNT;
int TESTSPASS;
int TESTSPASSBEST;
int SUBMISSIONS;
int TIMELIMIT;
int EXTRATIME = 100;
///////////////////////////////// PROTOTYPE //////////////////////////////////
int readSubDetails();
int checkBounds(short i,short j); 
bool isExecutable(const char *fspec);
int sselect(unsigned *X, unsigned *Y);

int judge(int exe_id);
DWORD WINAPI runningThread( LPVOID lpParam );

int selectExecutable();
void makeSourceFile();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argu[]){

	if(argc == 1) return 0;

	//char surfix[] = "\\testcases\\";

	PATH = (char*) malloc( strlen(argu[1]) * sizeof(char) );
	//char * PATH = new char[strlen(argu[1]) + 1];//+ strlen(surfix) + 1];

	strcpy(PATH, argu[1]);
	sPATH = string(PATH);

	//strcat(PATH, surfix);

    DIR *dir = opendir(PATH);
    struct dirent *entry = readdir(dir);

    execount = 0;

    while (entry != NULL)
    {
        if (entry->d_type != DT_DIR){
        	//cout << entry->d_name << endl;
        	if(isExecutable(entry->d_name)){
        		execount++;
        		exefiles.push_back( string(entry->d_name) );
        	}
        }
        entry = readdir(dir);
    }
    //cout << "??????"; system("pause");
    //clrscr(0, 0, 100, 100);
    gotoXY(0, 0);

    SetColor(15);
    cout << " .EXE METHOD: [UP][DOWN] to choose, [ENTER] to SUBMIT\n";
    cout << "--------------------------------------------------\n";
    SetColor(7);

    if(!!execount){
    	cout << "At ";
    	SetColor(15);
    	cout << argu[1] << endl;
    	SetColor(7);

    	if(execount == 1) 
    		 cout << " [" << execount << "] .exe file was found: " <<  endl;
    	else cout << " [" << execount << "] .exe files were found: " <<  endl;

    	SetColor(2);
    	for(unsigned i = 0; i < execount; i++){
    		cout << "   > " << exefiles[i] << endl;
    	}
    	SetColor(7);

    	if(readSubDetails()) return 0;
    	judge( selectExecutable() );
    }
    else{
    	cout << "  NO .EXE FILES FOUND\n";// CODE-PASTING METHOD IS USED\n";
    	//cout << "CODE-PASTING NOT IMPLEMENTED!\n";
    }
    SetColor(7);
    cout << "--------------------------------------------------\n";
    system("pause");
    exit(0);
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
DWORD WINAPI runningThread( LPVOID lpParam )
{    
    if( (GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE ) return 1; // ? Time
    //system( JUDGECOMMAND.c_str() );
    return 0; 
} 

int judge(int exe_id){
	cout << "\nJUDGING...\n";
	string juryin = "in";
	string ppout = "userout";
	string juryout = "out";

	string sCMDCOPY = "copy " + sPATH + "\\" + exefiles[exe_id] + " /B " + \
					sPATH + "\\" + "CopyOf" + exefiles[exe_id] + " /B";
	string sCMDDEL = 




	HANDLE hRunningThread = 0;

	char aJUDGECOMMAND[MAX_PATH];
	int subProcessStatus;

	SetColor(10);
	for(int t_id = 1; t_id <= TESTSCOUNT; t_id++){
	    string JUDGECOMMAND = "C:\\Windows\\System32\\cmd.exe /c type " + sPATH + "\\testcases\\in" + to_string(t_id) + \
		    		   "|" + sPATH + "\\" + exefiles[exe_id] + ">" + \
					   sPATH + "\\testcases\\userout";

		strcpy(aJUDGECOMMAND, JUDGECOMMAND.c_str());

		PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
		STARTUPINFO StartupInfo; //This is an [in] parameter
		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field

		if(CreateProcessA(NULL, aJUDGECOMMAND, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
		{ 
		    subProcessStatus = WaitForSingleObject( ProcessInfo.hProcess, TIMELIMIT + EXTRATIME );
		    
		    if(!subProcessStatus){
				cout << "Test " << t_id << " ran.\n";
				CloseHandle(ProcessInfo.hThread);
		    	CloseHandle(ProcessInfo.hProcess);
				continue;
			}
			else{ //TIME LIMIT EXCEEDED
				SetColor(12);
				cout << "Time Limit Exceed on Test " << t_id << "\n";
				cout << TerminateThread(hRunningThread, 1);
				CloseHandle(ProcessInfo.hThread);
		    	CloseHandle(ProcessInfo.hProcess);
		    	//system
				printf("\n%lu", ProcessInfo.dwProcessId);
				return -1; 
			}
		}
	}
	return 0;
}

int readSubDetails(){
	string surfix = "\\pdetails";
	string subDetails = sPATH + surfix;

	if(access( subDetails.c_str(), F_OK) != -1){
		cout << "Details file exists, getting data...\n";	
	}
	else{
		cout << "Details file doesn't exist, Judging is Aborted.\n";
		return 1;
	}
	if(access( subDetails.c_str(), R_OK) == -1){
		cout << "Read permission for Details file is not given, Judging is Aborted.\n";
		return 1;
	}

	ifstream sdetails (subDetails);
	sdetails >> STATUS;
	sdetails >> TESTSCOUNT;
	sdetails >> TESTSPASS;
	sdetails >> TESTSPASSBEST;
	sdetails >> SUBMISSIONS;
	sdetails >> TIMELIMIT;
	sdetails.close();

	//(TIMELIMIT < 100 || TIMELIMIT > 10000) CHECK

	return 0;
}

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
				gotoXY(4 + execount, 2);
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
				case 32: 
					return 1;	// SPACE
				case 13: 
					return 2;	// ENTER
				default: return 0;
			}
		}
	}
	return 0;
}

bool isExecutable(const char *fspec){
	char *e = strrchr (fspec, '.');

	if(!e) return 0;
	return (strcmp(e, ".exe") == 0); 
}