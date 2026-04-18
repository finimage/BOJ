#include<iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    long long n,k,q,i,j,tem,ans=0,t;
    cin>>n>>k>>q;
    for(i=1;i<=n;i++){
        t=0;
        for(j=0;j<k;j++){
            cin>>tem;
            if(i==1) t+=tem-i;
            else{
                if(i<=tem) t+=tem-i;
                else t+=n-i+tem;
            }
        }
        ans+=t;
        if(i==1 && t==0) ans+=n;
    }
    if(ans==n || ans/n<=q) cout<<1;
    else cout<<0;
}
