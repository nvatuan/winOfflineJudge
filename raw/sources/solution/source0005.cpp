#include <bits/stdc++.h>
using namespace std;
 
int main() {
	long long n, k;
	cin >> n >> k;

	while(1){
		if(n%10 + 1 < k){
			k -= (n%10 + 1);
			n /= 10;
		}
		else{
			if(n%10 + 1 == k) cout << (n/10);
			else cout << (n - k);
			break;
		}
	}
}

