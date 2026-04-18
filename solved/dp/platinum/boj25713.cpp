#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

int n, m, k;
int g[1005][1005][2];
int dp[1005][1005];

void solve() {
    int i, j, a, b, c, d; cin >> n >> m >> k;
    for (i = 0; i < k; i++) {
        cin >> a >> b >> c >> d;
        for (j = a; j <= c; j++) g[j][b - 1][0]++;
        for (j = b; j <= d; j++) g[a - 1][j][1]++;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) dp[i][j] = k + 1;
    }
    dp[1][1] = max(g[1][0][0], g[0][1][1]);
    for (i = 2; i <= n; i++) dp[i][1] = max(dp[i - 1][1] + g[i - 1][1][1], g[i][0][0]);
    for (i = 2; i <= m; i++) dp[1][i] = max(dp[1][i - 1] + g[1][i - 1][0], g[0][i][1]);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + g[i][j][0]);
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + g[i][j][1]);
        }
    }
    cout << dp[n][m];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
