#include<iostream>
#include<queue>
using namespace std;

char graph[1001][1001]={0,};
int check[1001][1001]={0,},dx[4]={1,0,0,-1},dy[4]={0,1,-1,0};
queue<pair<int,int>>q;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n,m,k,i,j,x1,x2,y1,y2,a,b,x,y;
    cin>>n>>m>>k;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++) cin>>graph[i][j];
    }
    cin>>x1>>y1>>x2>>y2;
    q.push({x1-1,y1-1});
    check[x1-1][y1-1]=1;
    while(!(q.empty())){
        a=q.front().first;
        b=q.front().second;
        q.pop();
        if(a==x2-1 && b==y2-1){
            cout<<check[a][b]-1;
            return 0;
        }
        for(i=0;i<4;i++){
            x=a;
            y=b;
            for(j=0;j<k;j++){
                x+=dx[i];
                y+=dy[i];
                if((0<=x && x<n)&&(0<=y && y<m)&&graph[x][y]=='.'){
                    if(check[x][y]==0){
                        check[x][y]=check[a][b]+1;
                        q.push({x,y});
                    }
                    else if(check[x][y]<=check[a][b]) break;
                }
                else break;
            }
        }
    }
    cout<<-1;
}
