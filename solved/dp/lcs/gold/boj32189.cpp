#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 998244353
using namespace std;

int n;
string s;

int LCS(string s1, string s2) {
    int l1 = s1.size(), l2 = s2.size(), i, j;
    vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0));
    for (i = 1; i <= l1; i++) {
        for (j = 1; j <= l2; j++) {
            dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1])});
        }
    }
    return dp[l1][l2];
}

int cal(int a) {
    int i;
    string s1 = "", s2 = "";
    for (i = 0; i < a; i++) s1 += s[i];
    for (i = a; i < n; i++) s2 += s[i];
    return min(a, n - a) - LCS(s1, s2);
}

void solve() {
    int le, ri, i; cin >> s;
    n = s.size();
    le = max(0, (n + 1) / 2 - 2);
    ri = min(n, (n + 1) / 2 + 2);
    int ans = 0;
    for (i = le; i <= ri; i++) ans = max(ans, cal(i));
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
