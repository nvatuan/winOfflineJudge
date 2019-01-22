#include <stdio.h>

int main(){
	long long a;
	scanf("%lld", &a);
	printf("%lld", a - (2 - (a%2)));
	return 0;
}