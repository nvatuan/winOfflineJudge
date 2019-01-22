#include <bits/stdc++.h>
using namespace std;

int main(){
	long long n;
	long long ans = 0;

	long long c[4];
	int coin[4] = {20, 10, 5, 1};
	int cid = 0;

	cin >> n;
	cin >> c[3] >> c[2] >> c[1] >> c[0];

	while(cid<4){
		ans += min(n, c[cid]) * coin[cid];
		n -= min(n, c[cid]);
		cid++;
	}
	cout << ans;
}