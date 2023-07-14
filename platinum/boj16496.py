import sys
from collections import deque
input=sys.stdin.readline
n=int(input())
l=list(map(str,input().split()))
t=1
for i in l:
    if i!='0':
        t=0
        break
if t:
    print(0)
    exit()
dq=deque()
dq.append(l[0])
def sorting(a):
    k=dq.pop()
    ndq=deque()
    ndq.append(k)
    while int(k+a)<int(a+k):
        if not(dq):
            break
        k=dq.pop()
        ndq.append(k)
    if int(k+a)>=int(a+k):
        dq.append(k)
        ndq.pop()
    dq.append(a)
    while ndq:
        k=ndq.pop()
        dq.append(k)
for i in range(1,n):
    sorting(l[i])
for i in range(n):
    print(dq.popleft(),end='')
