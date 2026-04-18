#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, m, arr[1000001], f[1000001], fi[1000001];

ll res(ll a, ll b) {
	if (b == 1) return a % MOD;
	ll k = res(a, b / 2);
	return k * k % MOD * (b % 2 ? a : 1) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, sum = 0; cin >> n >> m;
    for (i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] = m - arr[i];
        sum += arr[i];
    }
    if (sum > m) {
        cout << 0;
        return 0;
    }
    arr[n] = m - sum;
    f[0] = f[1] = 1;
    for (i = 2; i <= 1000000; i++) f[i] = f[i - 1] * i % MOD;
    fi[1000000] = res(f[1000000], MOD - 2);
    for (i = 1000000; i >= 1; i--) fi[i - 1] = fi[i] * i % MOD;
    ll ans = f[m];
    for (i = 0; i <= n; i++) ans = ans * fi[arr[i]] % MOD;
    cout << ans;
}
