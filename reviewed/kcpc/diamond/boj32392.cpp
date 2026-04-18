#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
ll n;
ll dp[502][502];
ll h[502][502];
ll x[502], y[502];
 
ll find_min(ll le, ll ri) {
    if (dp[le][ri] != -1) return dp[le][ri];
    ll i, res, ret = 2000000000000;
    for (i = le; i < ri; i++) {
        res = 0;
        res = find_min(le, i) + find_min(i + 1, ri) + min(y[i], y[i + 1]) - h[le][ri];
        if (h[le][i] != h[le][ri]) res += x[i] - x[max(le - 1, (ll)0)];
        if (h[i + 1][ri] != h[le][ri]) res += x[ri] - x[i];
        ret = min(ret, res);
    }
    if (ret == 2000000000000) ret = 0;
    //cout <<le << ' ' << ri << ' ' << ret << '\n'; 
    return dp[le][ri] = ret;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, j; cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        if (y[i] == y[i - 1]) {
            x[i - 1] += x[i];
            i--;
            n--;
        }
        else x[i] += x[i - 1];
    }
    x[n + 1] += x[n];
    for (i = 0; i <= n + 1; i++) {
        h[i][i] = y[i];
        dp[i][i] = -1;
        for (j = i + 1; j <= n + 1; j++) {
            h[i][j] = min(h[i][j - 1], y[j]);
            dp[i][j] = -1;
        }
    }
    cout << find_min(0, n + 1) - x[n + 1];
}
