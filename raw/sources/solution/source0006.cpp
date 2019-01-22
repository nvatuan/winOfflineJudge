#include <bits/stdc++.h>
using namespace std;

int main(){
	long long W, L, ans = 0;
	cin >> W >> L;
	W *= L;
	while(W){
		switch(getchar()){
			case 'W': ans++;
			case 'D': W--;
		}
	}
	cout << ans;
}