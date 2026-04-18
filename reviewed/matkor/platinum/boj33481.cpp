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

ll nchoose2(ll a) {
    return a * (a - 1) / 2;
}

void solve() {
    ll i; cin >> n >> m;
    ll sum = 0;
    for (i = 1; i <= n; i++) {
        cin >> arr[i];
        sum = (sum + arr[i]) % MOD;
    }
    ll ans; char c; cin >> c;
    if (c == 'S') {
        ll tmp = powmod((nchoose2(n) % MOD * 3 + n) % MOD, MOD - 2);
        ans = 0;
        for (i = 1; i <= n; i++) {
            ll tmp1 = (n - 1 + i + 3 * nchoose2(i - 1) % MOD + 3 * nchoose2(n - i) % MOD) % MOD;
            ll tmp2 = (nchoose2(n) - nchoose2(i - 1) - nchoose2(n - i)) % MOD * i % MOD;
            ll tmp3 = nchoose2(i) % MOD * (n - i + 1) % MOD + i * (n - i) % MOD;
            ll tmp4 = (n + i + 1) * (n - i) / 2 % MOD * i % MOD + i * (i - 1) % MOD;
            ans = (ans + arr[i] * powmod((tmp1 + tmp2 + tmp3 + tmp4) % MOD * tmp % MOD, m) % MOD) % MOD;
        }
        cout << ans * powmod(sum, MOD - 2) % MOD;
    }
    else {
        ll tmp = powmod((nchoose2(n) % MOD * 3 + n) % MOD, MOD - 2);
        ans = n * (n + 1) / 2 % MOD;
        vector<ll> dp(n + 1);
        dp[0] = 1;
        dp[1] = 2;
        ll tmp1 = 0;
        for (i = 2; i <= n; i++) {
            dp[i] = (dp[i - 1] + fi[i]) % MOD;
            tmp1 = (tmp1 + f[i] * dp[i - 2] % MOD) % MOD;
        }
        ll tmp2 = n - 1;
        for (i = 2; i <= n - 1; i++) {
            tmp2 += i * i % MOD * powmod(i - 1, MOD - 2) % MOD * (powmod(i, n - i) - 1 + MOD) % MOD;
            tmp2 %= MOD;
        }
        ll tmp3 = 0;
        for (i = 2; i <= n; i++) {
            tmp3 += i * i % MOD * powmod(i - 1, MOD - 2) % MOD * (powmod(i, i - 1) - 1 + MOD) % MOD;
            tmp3 %= MOD;
        }
        ans = (ans + tmp1 + tmp2 + tmp3) % MOD * tmp % MOD;
        cout << powmod(ans, m);
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
