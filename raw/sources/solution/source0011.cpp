#include <bits/stdc++.h>
using namespace std;

int H, T, ans;

int main(){
    while(1){
        cin >> H >> T;
        if(!H && !T) return 0;
        if(T == 0){
            if(H%2) cout << -1;
            else cout << H/2;
        }
        else{
            ans = 0;
            while(1){
                if(!H && !T) {cout << ans; break;}
                if(H>=2){ H-=2; ans++; continue; }
                if(T>=2){ T-=2; H++; ans++; continue; }
                else{ T++; ans++; }
            }
        }
        cout << endl;
    }
}