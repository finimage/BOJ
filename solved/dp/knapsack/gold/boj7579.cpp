#include<iostream>
using namespace std;

int dp[10000001]={0,},M[101]={0,},C[101]={0,};

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,m,i,j;
    cin>>n>>m;
    for(i=0;i<n;i++) cin>>M[i];
    for(i=0;i<n;i++) cin>>C[i];
    for(i=1;i<m;i++) dp[i]=-1;
    dp[m]=10001;
    for(i=0;i<n;i++){
        if(M[i]>=m) dp[m]=min(dp[m],C[i]);
        for(j=m;j>=1;j--){
            if(dp[j]!=-1){
                if(j+M[i]>=m) dp[m]=min(dp[m],dp[j]+C[i]);
                else{
                    if (dp[j+M[i]]==-1) dp[j+M[i]]=dp[j]+C[i];
                    else dp[j+M[i]]=min(dp[j+M[i]],dp[j]+C[i]);
                }
                if(j==M[i]) dp[j]=min(C[i],dp[j]);
            }
            else if(j==M[i]) dp[j]=C[i];
        }
    }
    cout<<dp[m];
}
