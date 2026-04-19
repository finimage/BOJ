#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, c, dp[1001][10001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, j; cin >> n >> c;
    for (i = 0; i <= 10000; i++) dp[1][i] = 1;
    for (i = 2; i <= 1000; i++) {
        for (j = 0; j <= 10000; j++) {
            dp[i][j] = ((j > 0 ? dp[i][j - 1] : 0) + dp[i - 1][j] - (j >= i ? dp[i - 1][j - i] : 0) + MOD) % MOD;
        }
    }
    cout << (dp[n][c] - (c > 0 ? dp[n][c - 1] : 0) + MOD) % MOD;
}
