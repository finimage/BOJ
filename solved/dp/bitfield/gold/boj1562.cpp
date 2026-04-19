#include<bits/stdc++.h>
#define MOD 1000000000
using namespace std;

int n, dp[101][11][1024];

int bit_dp(int l, int num, int visited) {
    if (dp[l][num][visited]) return dp[l][num][visited];
    if (n == l) {
        if (visited == 1023) return 1;
        else return 0;
    }
    int res = 0;
    if (num > 0) {
        dp[l + 1][num - 1][visited | (1 << (num - 1))] = bit_dp(l + 1, num - 1, visited | (1 << (num - 1)));
        res += dp[l + 1][num - 1][visited | (1 << (num - 1))];
        res %= MOD;
    }
    if (num < 9) {
        dp[l + 1][num + 1][visited | (1 << (num + 1))] = bit_dp(l + 1, num + 1, visited | (1 << (num + 1)));
        res += dp[l + 1][num + 1][visited | (1 << (num + 1))];
        res %= MOD;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, ans = 0; cin >> n;
    for (i = 1; i < 10; i++) {
        ans += bit_dp(1, i, 1 << i);
        ans %= MOD;
    }
    cout << ans;
}
