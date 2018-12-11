#include <iostream>
using namespace std;

int H, T;

int main(){
	cin >> H >> T;

	while(!H && !T){
		cout << H/2 + (T/2) + (T%2) << endl;
		cin >> H >> T;
	}
}