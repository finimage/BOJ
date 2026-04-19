n, m, k = map(int, input().split())

ss = set()
ans = []

for i in range(1, m+1):
    tmp = i ^ k
    if tmp not in ss:
        ans.append(i)
        ss.add(i)
    if (len(ans) >= n):
        break

if len(ans) >= n:
    for i in range(n):
        print(ans[i], end = ' ')
else:
    print(-1)
