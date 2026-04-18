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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll n, m, q;

ll test(ll val) {
    if (val == 0) return m * (m + 1) / 2;
    ll p = m * m + 1;
    ll a = val / m, b = val % m;
    ll k = test(a);
    ll le = a * p + 1 + b * m;
    ll ri = a * p + 1 + b * m + m - 1;
    if (k < le) {
        le++;
        ri++;
    }
    if (le <= k && k <= ri) ri++;
    else k = 0;
    return (le + ri) * (ri - le + 1) / 2 - k;
}

void solve() {
    cin >> n;
    __int128 tmp = (__int128)m * (m + 1) / 2;
    if (m == 1) cout << "1\n";
    else if (tmp > 1e18) cout << "0\n";
    else {
        ll p = m * m + 1;
        if (test((n - 1) / p) == n) cout << "1\n";
        else cout << "0\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> m >> q;
    while (q--) solve();
}
