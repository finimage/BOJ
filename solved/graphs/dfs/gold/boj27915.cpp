#include<iostream>
using namespace std;

int stage[100001]={0,1,0};

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,i,t,o=1,e=0;
    cin>>n;
    for(i=2;i<=n;i++){
        cin>>t;
        stage[i]=stage[t]+1;
        if(stage[i]%2==0) e++;
        else o++;
    }
    cout<<max(o,e);
}
