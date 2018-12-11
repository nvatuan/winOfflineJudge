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
int MODE_AC = 1;
int JUDGERETURN;

int STATUS;
int TESTSCOUNT;
int TESTSPASS;
int TESTSPASSBEST;
int SUBMISSIONS;
int TIMELIMIT;
int EXTRATIME = 100;
///////////////////////////////// PROTOTYPE //////////////////////////////////
int readSubDetails();
int writeSubDetails();
int checkBounds(short i,short j); 
bool isExecutable(const char *fspec);
int sselect(unsigned *X, unsigned *Y);

int checkWA(int t_id);
int judge(int exe_id);

int selectExecutable();
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
    	JUDGERETURN = judge( selectExecutable() );

    	writeSubDetails();
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
int checkWA(int t_id){
	//string juryin  = sPATH + "\\testcases\\in";
		
	string juryout = sPATH + "\\testcases\\out" + to_string(t_id);
	string consout = sPATH + "\\testcases\\userout";

	if(access( juryout.c_str(), F_OK) == -1){
		cout << "JURY OUTPUT out FILE DOESNT EXIST!\n";
		return -1;
	}
	if(access( consout.c_str(), F_OK) == -1){
		cout << "YOUR OUTPUT userout FILE DOESNT EXIST!\n";
		return -1;	
	}

	string line1, line2;

	ifstream fJ(juryout);
	ifstream fC(consout);

	if(!(fJ.is_open() && fC.is_open())) return -1;

	while(!( fJ.eof()&&fC.eof() )){
		fJ >> line1;
		fC >> line2;
		//if(fJ.eof()^fC.eof()) return 1; // WRONG
		if(line1 != line2) return 1;
	}	
	return 0;
}

int judge(int exe_id){
	cout << "\nJUDGING...\n";
	////////////////////////////////  COMMANDLINE STRING
	string sCLONE   = "Doppelganger_" + exefiles[exe_id];
	string sCMDCOPY = "COPY \"" + sPATH + "\\" + exefiles[exe_id] + "\" /B " + \
					       "\"" + sPATH + "\\" + sCLONE           + "\" /B > nul";
	string sCMDDEL  = "DEL  \"" + sPATH + "\\" + sCLONE + "\"";
	string sCMDKIL  = "TASKKILL /F /IM \"" + sCLONE + "\" > nul";
	//////////////////////////////// CREATEPROCESS() INIT

	char aJUDGECOMMAND[MAX_PATH];
	int subProcessStatus;

	system(sCMDCOPY.c_str()); 

	SetColor(10);
	int t_id = 0;
	//for(int t_id = 1; t_id <= TESTSCOUNT; t_id++){		// ABANDONING TESTCOUNT VARIABLE
	while(++t_id){
		string inNo = sPATH + "\\testcases\\in" + to_string(t_id);
		if(access( inNo.c_str(), F_OK) == -1){ break; }
		string outNo = sPATH + "\\testcases\\out" + to_string(t_id);
		if(access( outNo.c_str(), F_OK) == -1){ SetColor(7); cout << "Output file out" << t_id << " doesnt seem to exist.\n"; continue; }

	    string JUDGECOMMAND = \
	    	"C:\\Windows\\System32\\cmd.exe /c type " + inNo + \
		    "| \"" + sPATH + "\\" + sCLONE + \
		    "\" >" + sPATH + "\\testcases\\userout";

		strcpy(aJUDGECOMMAND, JUDGECOMMAND.c_str());

		PROCESS_INFORMATION ProcessInfo; 
		STARTUPINFO StartupInfo; 
		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field

		if(CreateProcessA(NULL, aJUDGECOMMAND, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo))
		{ 
		    subProcessStatus = WaitForSingleObject( ProcessInfo.hProcess, TIMELIMIT + EXTRATIME );
		    
		    if(!subProcessStatus){
		    	SetColor(15);
				cout << "Test " << t_id << " ran.\n";
				CloseHandle(ProcessInfo.hThread);
		    	CloseHandle(ProcessInfo.hProcess);

		    	switch(checkWA(t_id)){
		    		case 0:
			    		SetColor(10);
			    		cout << "Correct Answer.\n";
			    		break;
			    	case 1:
			    		SetColor(12);
			    		cout << "Wrong Answer on Test " << t_id << "\n";
			    		if(MODE_AC){
			    			system(sCMDDEL.c_str());
			    			return -1;
			    		}
			    	case -1:
			    		SetColor(15);
			    		cout << "Cannot open test files to cross-check answer.\n";
			    		system(sCMDDEL.c_str());
			    		return -100;
		    	}
				continue;
			}
			else{ //TIME LIMIT EXCEEDED

				SetColor(12);
				cout << "Time Limit Exceed on Test " << t_id << "\n";
				CloseHandle(ProcessInfo.hThread);
		    	CloseHandle(ProcessInfo.hProcess);
		    	
		    	system(sCMDKIL.c_str());
				system(sCMDDEL.c_str());
				if(MODE_AC) return -2; 
			}
		}
	}
	system(sCMDDEL.c_str());
	if(t_id == 1) {SetColor(15); cout << "NO TESTFILE FOUND, MAKE SURE THAT YOUR TESTFILES WERE LABLED FROM in1/out1\n"; return -100;}
	else return 100;
}

int readSubDetails(){
	string surfix = "\\pdetails";
	string subDetails = sPATH + surfix;

	if(access( subDetails.c_str(), F_OK) != -1){
		cout << "Details file exists, getting data...\n";
		if(access( subDetails.c_str(), R_OK) == -1){
			cout << "Read permission for Details file is not given, Judging is Aborted.\n";
			return 1;
		}
	}
	else{
		cout << "Details file doesn't exist, Creating a default one.\n";
		//STATUS = 0;
		JUDGERETURN = 0;
		TESTSPASS = 0;
		TESTSPASSBEST = 0;
		SUBMISSIONS = -1;
		TIMELIMIT = 1000;

		writeSubDetails();
		//return 1;
	}

	ifstream sdetails (subDetails);
	sdetails >> STATUS;
	//sdetails >> TESTSCOUNT;
	sdetails >> TESTSPASS;
	sdetails >> TESTSPASSBEST;
	sdetails >> SUBMISSIONS;
	sdetails >> TIMELIMIT;
	sdetails.close();

	//(TIMELIMIT < 100 || TIMELIMIT > 10000) CHECK

	return 0;
}
int writeSubDetails(){
	if(JUDGERETURN == -100){
		cout << "Program didnt function as intended, abort updating details file.\n";
		return 0;
	}

	string surfix = "\\pdetails";
	string subDetails = sPATH + surfix;

	if(access( subDetails.c_str(), F_OK) != -1){
		cout << "Writing to Details file...\n";	
		if(access( subDetails.c_str(), R_OK) == -1){
			cout << "Read permission for Details file is not given, judge result is discared.\n";
			return 1;
		}
	}
	else{
		cout << "Details file doesn't exist, making a new pdetails file...\n";
		//return 1;
	}

	ofstream sdetails (subDetails);

	if(STATUS != 100) sdetails << JUDGERETURN << endl;
	else sdetails << STATUS << endl;
	//sdetails >> TESTSCOUNT;
	sdetails << TESTSPASS << endl;
	sdetails << TESTSPASSBEST << endl;
	sdetails << (SUBMISSIONS + 1) << endl;
	sdetails << TIMELIMIT << endl;
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
				gotoXY(4 + execount + 1, 2);
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
				case 27:
					exit(0);
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