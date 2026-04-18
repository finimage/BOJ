#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, k;
int grid[2005][2005];
ll dp1[2005][2005], dp2[2005][2005], dp[2005][2005][2];

void solve() {
    int i, j; cin >> n >> k;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) cin >> grid[i][j];
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) dp1[i][j] = max(dp1[i - 1][j], dp1[i][j - 1]) + grid[i][j];
    }
    for (i = n; i > 0; i--) {
        for (j = n; j > 0; j--) dp2[i][j] = max(dp2[i + 1][j], dp2[i][j + 1]) + grid[i][j];
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) dp[i][j][0] = dp[i][j][1] = dp1[i][j] + dp2[i][j] - grid[i][j];
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) dp[i][j][0] = max(dp[i][j][0], dp[i][j - 1][0]);
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) dp[j][i][1] = max(dp[j][i][1], dp[j - 1][i][1]);
    }
    ll ans = 50000000000;
    for (i = 1; i <= n - k + 1; i++) {
        for (j = 1; j <= n - k + 1; j++) {
            if (i == 1 && j == 1) continue;
            if (i == n - k + 1 && i == j) continue;
            ll tmp = 0;
            if (i + k <= n && j >= 2) tmp = max(tmp, dp[i + k][j - 1][0]);
            if (i >= 2 && j + k <= n) tmp = max(tmp, dp[i - 1][j + k][1]);
            ans = min(ans, tmp);
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
