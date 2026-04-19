import sys
input = sys.stdin.readline

def ck(a):
    p = a // 3
    r = a % 3
    res = p * (p + 1) // 2 * 9 - 2 + 3 * r * (p + 1)
    return res

def sol(n):
    le, ri, res = 0, n, 0
    while le <= ri:
        mid = (le + ri) // 2
        if n >= ck(mid):
            res = mid
            le = mid + 1
        else:
            ri = mid - 1
    print(res + 1)

t = int(input())
for i in range(t):
    n = int(input())
    sol(n)
