#include<bits/stdc++.h>
#define ll long long
using namespace std;

string s;
vector<int> p, dp;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int l, i, k = 0; cin >> l >> s;
    p.resize(l);
    dp.resize(l);
    ll ans = 0;
    for (i = 1; i < l; i++) {
        while (k > 0 && s[k] != s[i]) k = p[k - 1];
        if (s[k] == s[i]) k++;
        p[i] = dp[i] = k;
        if (dp[k - 1] != 0) dp[i] = dp[k - 1];
        if (dp[i]) ans += i + 1 - dp[i];
    }
    cout << ans;
}
