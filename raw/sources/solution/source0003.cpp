#include <bits/stdc++.h>
using namespace std;

int main(){
	long long n, k;
	scanf("%lld", &n);
	
	k = 0;
	while(n){
		k += (n%10);
		n/=10;
	}
	if(k%9) cout << (k%9);
	while(k>8){
		k-=9;
		cout << 9;
	}
}