#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll res(ll a, ll b) {
    ll ret = 1;
	while (b && a > 1){
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n, m, T; cin >> T;
    while (T--) {
        cin >> n >> m;
        if (n == 1) cout << ((m - 2) >> 1) * ((m - 1) >> 1) * 2 % MOD * res((m - 2) * (m - 2) % MOD, MOD - 2) % MOD << '\n';
        else if (m & 1) cout << 500000004 * (1 + res(res(m - 2, n), MOD - 2)) % MOD << '\n';
        else cout << 500000004 << '\n';
    }
}
