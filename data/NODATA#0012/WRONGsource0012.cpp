#include <bits/stdc++.h>
using namespace std;

int room[1002][1002];
int tile[1002][1002];

int conn[1002][1002];

int main(){
	long long R, C;
	
	cin >> R >> C;
	for(int i = 0; i < R; i++){
		cin.ignore();
		for(int j = 0; j < C; j++){
			switch(getchar()){
				case 'W': room[i][j] = 1;
				case 'D':;
			}
		}
	}

	int pudcount = 0, pudid = 0;

	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			if(!tile[i][j]){
				if(room[i][j]){
					pudcount++;
					pudid++;

					tile[i][j] = pudid;
				}
			}

			if(tile[i][j]){
				if((tile[i+1][j]) && (tile[i+1][j] != tile[i][j])){
					if(!conn[tile[i+1][j]][tile[i][j]]){
						pudcount--;
						conn[tile[i+1][j]][tile[i][j]] = 1;
						conn[tile[i][j]][tile[i+1][j]] = 1;
					}
				}
				else if(room[i+1][j]) tile[i+1][j] = tile[i][j];
				if((tile[i][j+1]) && (tile[i][j+1] != tile[i][j])){
					if(!conn[tile[i][j+1]][tile[i][j]]){
						pudcount--;
						conn[tile[i][j+1]][tile[i][j]] = 1;
						conn[tile[i][j]][tile[i][j+1]] = 1;
					}
				}
				else if(room[i][j+1]) tile[i][j+1] = tile[i][j];
			}			
		}
	}

	cout << pudcount << endl;

	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			cout << tile[i][j];
		}
		cout << endl;
	}
}

/*
6 6
WWWWWW
WDDDDW
WDWWDW
WDWWDW
WDWWDW
WWWWWW

7 9
WWWWWWWWW
WDDDDDDDW
WDWWWWWWW
WDWDDDDDW
WDWDWWWWW
WDWDWDDDW
WWWWWWWWW

WRONG ANSWER