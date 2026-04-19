#include<bits/stdc++.h>
#define ld long double
using namespace std;

int n, m, s, e;
ld dp[501][10001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j; cin >> n >> m >> s >> e;
    if (n == 2) {
        if (m % 2) {
            if (s != e) cout << 1;
            else cout << 0;
        }
        else {
            if (s != e) cout << 0;
            else cout << 1;
        }
        return 0;
    }
    dp[s][0] = 1;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (j == 1) dp[j][i] += (dp[j + 1][i - 1] + dp[j][i - 1] * (n - 2)) / (n - 1);
            else if (j == n) dp[j][i] += (dp[j - 1][i - 1] + dp[j][i - 1] * (n - 2)) / (n - 1);
            else dp[j][i] += (dp[j + 1][i - 1] + dp[j - 1][i - 1] + dp[j][i - 1] * (n - 3))/ (n - 1);
        }
    }
    cout << fixed << setprecision(9);
    cout << dp[e][m];
}
