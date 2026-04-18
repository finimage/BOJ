#include<iostream>
using namespace std;

int graph[1001][1001]={0,},check[2]={0,};

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int r,c,i,j,MIN=1001;
    cin>>r>>c;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            cin>>graph[i][j];
            if((i%2==0 && j%2==1)||(i%2==1 && j%2==0)){
                MIN=min(MIN,graph[i][j]);
                if(MIN==graph[i][j]){
                    check[0]=i;
                    check[1]=j;
                }
            }
        }
    }
    if(r%2==1){
        for(i=0;i<r;i++){
            if(i%2==0){
                for(j=1;j<c;j++) cout<<'R';
            }
            else{
                for(j=1;j<c;j++) cout<<'L';
            }
            if(i==r-1) break;
            cout<<'D';
        }
        cout<<endl;
    }
    else if(c%2==1){
        for(i=0;i<c;i++){
            if(i%2==0){
                for(j=1;j<r;j++) cout<<'D';
            }
            else{
                for(j=1;j<r;j++) cout<<'U';
            }
            if(i==c-1) break;
            cout<<'R';
        }
        cout<<endl;
    }
    else{
        if(check[0]%2==0){
            for(i=0;i<check[0];i++){
                if(i%2==0){
                    for(j=1;j<c;j++) cout<<'R';
                }
                else{
                    for(j=1;j<c;j++) cout<<'L';
                }
                cout<<'D';
            }
            for(i=0;i<check[1];i++){
                if(i%2==0) cout<<'D';
                else cout<<'U';
                cout<<'R';
            }
            if(check[1]!=c-1) cout<<'R';
            for(i=check[1]+1;i<c;i++){
                if(i%2==0) cout<<'U';
                else cout<<'D';
                if(i==c-1) break;
                cout<<'R';
            }
            if(c-1!=check[1] && r-1!=check[0]) cout<<'D';
            for(i=check[0]+2;i<r;i++){
                if(i%2==0){
                    for(j=1;j<c;j++) cout<<'L';
                }
                else{
                    for(j=1;j<c;j++) cout<<'R';
                }
                if(i==r-1) break;
                cout<<'D';
            }
            cout<<endl;
        }
        else{
            for(i=0;i<check[0]-1;i++){
                if(i%2==0){
                    for(j=1;j<c;j++) cout<<'R';
                }
                else{
                    for(j=1;j<c;j++) cout<<'L';
                }
                cout<<'D';
            }
            for(i=0;i<check[1];i++){
                if(i%2==0) cout<<'D';
                else cout<<'U';
                cout<<'R';
            }
            if(check[1]!=c-1) cout<<'R';
            for(i=check[1]+1;i<c;i++){
                if(i%2==0) cout<<'U';
                else cout<<'D';
                if(i==c-1) break;
                cout<<'R';
            }
            if(c-1!=check[1] && r-1!=check[0]) cout<<'D';
            for(i=check[0]+1;i<r;i++){
                if(i%2==0){
                    for(j=1;j<c;j++) cout<<'L';
                }
                else{
                    for(j=1;j<c;j++) cout<<'R';
                }
                if(i==r-1) break;
                cout<<'D';
            }
            cout<<endl;
        }
    }
}
