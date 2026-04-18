#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

ll n, m, arr[1000001];
ll f[1000001], fi[1000001];

ll powmod(ll a, ll b) {
    ll res = 1;
    while (b && a != 1) {
        if (b & 1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}

void preprocess() {
    ll i;
    f[0] = 1;
    for (i = 1; i <= 1000000; i++) f[i] = f[i - 1] * i % MOD;
    fi[1000000] = powmod(f[1000000], MOD - 2);
    for (i = 1000000; i >= 1; i--) fi[i - 1] = fi[i] * i % MOD;
}

void solve() {
    ll i; cin >> n >> m;
    for (i = 1; i <= n; i++) cin >> arr[i];
    ll ans; char c; cin >> c;
    if (c == 'S') {
        ll invnplus1 = powmod(n + 1, MOD - 2);
        ans = 2 * n * invnplus1 % MOD;
        cout << powmod(ans, m);
    }
    else {
        ll invnplus1 = powmod(n + 1, MOD - 2);
        ll inv2 = powmod(2, MOD - 2);
        ans = f[n] * invnplus1 % MOD + n * inv2 % MOD;
        cout << powmod(ans % MOD, m);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    preprocess();
    int T = 1; //cin >> T;
    while (T--) solve();
}
