import sys
input=sys.stdin.readline
n=int(input())
l=[]
dp=[]
for i in range(n):
    a,b=map(int,input().split())
    l.append((a,b))
    dp.append([0]*n)
for i in range(1,n):
    for j in range(n-i):
        dp[i][j]=2**31
        for k in range(0,i):
            dp[i][j]=min(dp[i][j],dp[k][j]+dp[i-k-1][j+k+1]+l[j][0]*l[j+k+1][0]*l[j+i][1])
print(dp[n-1][0])
