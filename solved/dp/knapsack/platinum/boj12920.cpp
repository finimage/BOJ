#include<iostream>
using namespace std;

int bag[101][10001]={0,},V[101]={0,},C[101]={0,},K[101]={0,};

int main(){
    int n,m,i,j,temp1,temp2,ans=0;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++) scanf("%d %d %d",&V[i],&C[i],&K[i]);
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++) bag[i][j]=bag[i-1][j];
        temp2=1;
        while(K[i]>0){
            temp1=min(K[i],temp2);
            for(j=m;j>=V[i]*temp1;j--) bag[i][j]=max(bag[i][j-V[i]*temp1]+C[i]*temp1,bag[i][j]);
            temp2*=2;
            K[i]-=temp1;
        }
    }
    for(i=1;i<=m;i++) ans=max(ans,bag[n][i]);
    printf("%d",ans);
}
