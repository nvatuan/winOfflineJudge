#include <windows.h> // xu ly nhung thu lien quan den Win32
#include <conio.h> 	// xu ly nhung thu lien quan den Console cmd
#include <dirent.h> // xu ly cac ve PATH cac folder va file (directory)
#include <iostream>	// thu vien INPUT OUTPUT
#include <fstream>	// thu vien xu ly FILE
#include <map>		// cau truc du lieu MAP
#include <vector>	// cau truc du lieu VECTOR
using namespace std;

//////////////////////////////// FILE
string \
	FWD = "workingdir.string";

//////////////////////////////// COLOR
map <string, int> cl = {
	{"black", 0}, {"blue", 1}, {"green", 2}, {"aqua", 3},
	{"red", 4}, {"purple", 5}, {"yellow", 6}, {"white", 7},

	{"Black", 8}, {"Blue", 9}, {"Green", 10}, {"Aqua", 11},
	{"Red", 12}, {"Purple", 13}, {"Yellow", 14}, {"White", 15},
};
//////////////////////////////// INIT
vector< string > unsolved, attempted, solved;
vector< string > probs;
const int HSCREEN = 100;

int folders;
char PWD[256]; 
size_t len = sizeof(PWD);
int bytes;

unsigned X, Y;

///////////////////////////////////////////////////////////// PROTOTYPE /////////////////////////////////////////////////////////////
int check(short i,short j);
void gotoXY(short x, short y);
void clrscr(int h);
int select();

////////////////////////////////////////////////////////////// FUNCTION //////////////////////////////////////////////////////////////
void SetColor(string value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cl[value]);
}

bool list_dir();
bool promptDir();

//-------------------------------------------------------------- MAIN --------------------------------------------------------------//
int main(){
	probs.clear();
	promptDir();
	// probs contains the folder;
	X = 0;
	Y = 0;
	clrscr(HSCREEN);

	do{
		clrscr(probs.size());
		for(unsigned i = 0; i < probs.size(); i++){
			if(X == i) SetColor("White");
			else SetColor("white");
			cout << "[" << probs[i] << "]\n";
		}
		gotoXY(X, Y);
		select();
	} while(1);
}

//------------------------------------------------------------ END MAIN ------------------------------------------------------------//
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

	ofstream filewd (FWD);
	filewd << PWD;
	filewd.close();

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
int check(short i,short j)
{
	if (i<0||j<0||i>10||j>10) return 0;
	return 1;
}
//------------------------------------------------------------------------------------------------------------------------------------------//
int select()
{
	char c;
	//do
	{
		c=getch();
		if (c==72)
		{
			if (check(X-1,(Y+1)/2)) X--;
		}
		else if ((int)c==80)
		{
			if (check(X+1,(Y+1)/2)) X++;
		}
		else if ((int)c==75)
		{
			if (check(X,(Y-1)/2)) Y--;
		}
		else if ((int)c==77)
		{
			if (check(X,(Y+3)/2)) Y++;
		}
		gotoXY(X,Y);
	}
	//while ((int)c!=13);
	return 0;
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
void clrscr(int h)
{
	gotoXY(0,0);
	for(int i = 1; i <= h; i++) 
		cout<<"                                                                                                                   \n";
	gotoXY(0,0);
}