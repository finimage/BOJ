import sys
input=sys.stdin.readline
def m_m(m1,m2):
    ans=[[0,0,0],[0,0,0],[0,0,0]]
    for i in range(3):
        for j in range(3):
            for k in range(3):
                ans[i][j]+=m1[i][k]*m2[k][j]
                ans[i][j]%=998244353
    return ans
def bi(n):
    l=[]
    while n!=0:
        r=n%2
        n//=2
        l.append(r)
    return l
def p(n):
    if 1<=n<=3:
        return 1
    l=bi(n-1)
    sq=[[[0,1,0],[0,0,1],[1,1,0]]]
    for i in range(len(l)-1):
        sq.append(m_m(sq[-1],sq[-1]))
    ans=[[0,1,0],[0,0,1],[1,1,0]]
    for i in range(len(l)):
        if l[i]:
            ans=m_m(ans,sq[i])
    return ans[2][1]
for i in range(int(input())):
    n=int(input())
    print(p(n))
