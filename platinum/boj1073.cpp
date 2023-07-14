#include<iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,i,check[10]={0,},tf=1;
    char c1,c2;
    long long int ans=1,ret[5]={1,1,3,15,105};
    cin>>n;
    for(i=0;i<n;i++){
        cin>>c1>>c2;
        check[c1-'0']++;
        check[c2-'0']++;
    }
    for(i=0;i<10;i++){
        if(check[i]%2==1){
            tf=0;
            break;
        }
    }
    if(tf){
        for(i=0;i<10;i++) ans*=ret[check[i]/2];
        cout<<ans;
    }
    else cout<<0;
}
