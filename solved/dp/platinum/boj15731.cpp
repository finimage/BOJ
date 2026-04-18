#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

int n, dp[5002][5002];
string s;

void solve() {
    int i, j; cin >> s;
    n = s.size();
    dp[0][0] = 1;
    for (i = 1; i < n; i++) {
        if (s[i - 1] == 'f') {
            for (j = i; j > 0; j--) dp[i][j] = (int)(((ll)dp[i][j + 1] + (ll)dp[i - 1][j - 1] - (ll)dp[i - 1][j] + MOD) % MOD);
            dp[i][0] = dp[i][1];
        }
        else {
            for (j = i; j >= 0; j--) dp[i][j] = (int)(((ll)dp[i][j + 1] + (ll)dp[i - 1][j]) % MOD);
        }
    }
    cout << dp[n - 1][0];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
