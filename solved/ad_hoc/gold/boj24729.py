import sys
input = sys.stdin.readline

n = int(input())
l = list(map(int, input().split()))
Min = min(l)

cnt = [0 for _ in range(100005)]
for i in l:
    cnt[i] += 1

tmp = Min
cnt[tmp] -= 1
for i in range(n-1):
    if cnt[tmp + 1]:
        cnt[tmp + 1] -= 1
        tmp += 1
    elif cnt[tmp - 1]:
        cnt[tmp - 1] -= 1
        tmp -= 1
    else:
        print(-1)
        exit()
if abs(tmp - Min) != 1:
    print(-1)
else:
    print(1)
