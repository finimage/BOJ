n=int(input())
def m_m(l1,l2):
    l=[[0,0],[0,0]]
    for i in range(2):
        for j in range(2):
            for k in range(2):
                l[i][j]+=l1[i][k]*l2[k][j]
                l[i][j]%=1000000
    return l
def bi(n):
    l=[]
    while n!=0:
        r=n%2
        n//=2
        l.append(r)
    return l
def f(a):
    if a==0:
        return 0
    if a==1:
        return 1
    bin_l=bi(a-1)
    l=[]
    l.append([[1,1],[1,0]])
    for i in range(1,len(bin_l)):
        l.append(m_m(l[-1],l[-1]))
    ans=[[1,0],[0,1]]
    for i in range(len(bin_l)):
        if bin_l[i]:
            ans=m_m(ans,l[i])
    return ans[0][0]
print(f(n)%1000000)
