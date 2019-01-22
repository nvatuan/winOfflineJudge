#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	string t[1001];
	int R, G, B, tmp;
	double r[1001];

	cin >> N;
	cin.ignore();
	for(int i = 0; i<N; i++){	
		getline(cin, t[i]);
	}

	for(int i = 0; i<N; i++){
		cin >> R;
		G = 0; B = 0;
		while(R--){
			cin >> tmp;
			if(tmp == 1) G++;
			else B++;
		}
		r[i] = double(G)/(G+B);
	}
	
	// for(int i = 0; i < N; i++){
	// 	cout << "t[" << i << "] = " << t[i] << endl;
	// }
	
	for(int i = 0; i < N; i++){
		tmp = i;
		for(int j = 0; j < N; j++){
			if(r[tmp] < r[j]) tmp = j;
		}
		cout << t[tmp] << endl;
		r[tmp] = -1.0;
	}
}