#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll f[5000001], fi[5000001], d[5000001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll n, m, i; cin >> n >> m;
    f[0] = f[1] = 1;
    for (i = 2; i <= 5000000; i++) f[i] = f[i - 1] * i % MOD;
    fi[5000000] = 255895843;
    for (i = 5000000; i >= 1; i--) fi[i - 1] = fi[i] * i % MOD;
    d[0] = 1;
    d[1] = m - n;
    for (i = 2; i <= n; i++) d[i] = (d[i - 2] * (i - 1) % MOD + d[i - 1] * (i - 1) % MOD + d[i - 1] * (m - n) % MOD) % MOD;
    for (i = 0; i <= n; i++) {
        ll k = f[n] * f[m - n] % MOD * fi[n - i] % MOD * fi[i] % MOD * fi[m] % MOD;
        cout << k * d[n - i] % MOD << ' ';
    }
}
