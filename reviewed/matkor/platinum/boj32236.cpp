#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, m;

ll res(ll a, ll b) {
	ll res = 1;
	while (b){
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll i; cin >> n >> m;
    ll ans = 1;
    cout << ans << ' ';
    for (i = 2; i <= n; i++) {
        ans = (ans + res(res(i, MOD - 2), m))% MOD;
        cout << ans << ' ';
    }
}
