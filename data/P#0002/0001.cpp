#include <iostream>
using namespace std;

int main(){
	string st;
	getline(cin, st);

	for(unsigned i = 0; i < st.length(); i++){
		if(('a' <= st[i])&&(st[i] <= 'z')) cout << st[i];
		if(('A' <= st[i])&&(st[i] <= 'Z')) cout << char(st[i] + 'a' - 'A');
	}
	//while(1){};
}
