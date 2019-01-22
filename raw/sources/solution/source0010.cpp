#include <bits/stdc++.h>
using namespace std;

int main(){
	string st;
	char c = 0;
	int multiplier[8] = {128, 64, 32, 16, 8, 4, 2, 1};
	cin >> st;
	for(int i = 0; i < st.length(); i++){
		c += ( (st[i]=='1')*(multiplier[i%8]) );
		if(i%8 == 7){
			cout << c;
			c = 0;
		}
	}
}