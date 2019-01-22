#include <bits/stdc++.h>
using namespace std;

char mark[1000001];

int main(){
	long long n;
	long tmp, ans = 0;
	cin >> n;
	n*=2;
	while(n--){
		cin >> tmp;
		ans += (!mark[tmp]);
		mark[tmp] = 1;
	}
	cout << ans;
}