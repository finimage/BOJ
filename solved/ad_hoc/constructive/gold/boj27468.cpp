#include<iostream>
using namespace std;

int main(){
    int n,i;
    cin >> n;
    cout << "YES\n";
    if(n%2==0){
        cout << 1 << ' ' << 2 << ' ' << 4 << ' ' << 3 << ' ';
        for(i=5;i<=n;i+=2){
            if(i%4==1) cout << i << ' ' << i + 1 << ' ';
            else cout << i + 1 << ' ' << i << ' ';
        }
    }
    else{
        cout << 3 << ' ' << 1 << ' ' << 2 << ' ';
        for(i=4;i<=n;i+=2){
            if(i%4==0) cout << i << ' ' << i + 1 << ' ';
            else cout << i + 1 << ' ' << i << ' ';
        }
    }
}
