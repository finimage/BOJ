#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, m, f[5000001], f_i[5000001];

ll res(ll a, ll b) {
	if (b == 0) return 1;
	ll k = res(a, b / 2);
	return k * k % MOD * (b % 2 ? a : 1) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, a; cin >> n >> m;
    f[0] = 1;
    for (i = 1; i <= 5000000; i++) f[i] = f[i - 1] * i % MOD;
    f_i[5000000] = res(f[5000000], MOD - 2);
    for (i = 5000000; i >= 1; i--) f_i[i - 1] = f_i[i] * i % MOD;
    ll ans = res(2, n - m) * f[n] % MOD;
    for (i = 1; i <= m; i++) {
        cin >> a;
        ans = ans * f_i[a] % MOD;
    }
    cout << ans;
}
