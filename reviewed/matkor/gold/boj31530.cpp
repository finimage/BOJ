#include<bits/stdc++.h>
#define ll long long
#define INF 1000000007
using namespace std;

ll dp[8][1000001];

void solve() {
    int h, S, i, t, ck = 0; cin >> h >> S;
    for (i = 0; i < S; i++) {
        cin >> t;
        if (t == -1) ck += 4;
        if (t == 0) ck += 2;
        if (t == 1) ck++;
    }
    cout << dp[ck][h - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T, i; cin >> T;
    for (i = 1; i < 8; i++) dp[i][0] = dp[i][1] = 1;
    dp[3][1] =  dp[5][1] = dp[6][1] = 2;
    dp[7][1] = 3;
    for (i = 2; i <= 1000000; i++) {
        dp[1][i] = dp[2][i] = dp[4][i] = 1;
        dp[5][i] = dp[5][i - 1] * dp[5][i - 2] % INF * 2 % INF;
        dp[3][i] = dp[6][i] = (dp[3][i - 1] * dp[3][i - 2] % INF + dp[3][i - 1] * dp[3][i - 1] % INF) % INF;
        dp[7][i] = (dp[7][i - 1] * dp[7][i - 1] % INF + dp[7][i - 1] * dp[7][i - 2] % INF * 2 % INF ) % INF;
    }
    while (T--) solve();
}
