#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 998244353
using namespace std;
 
ll powmod(ll a, ll b) {
    ll res = 1;
    while (b && a != 1) {
        if (b & 1) res = res * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return res;
}
 
void solve() {
    ll n, l, r; cin >> n >> l >> r;
    cout << (r > l ? (powmod((r - l + 1) % MOD, n) - powmod((r - l) % MOD, n) * 2 + powmod((r - l - 1) % MOD, n) + MOD + MOD) % MOD : 1) << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; cin >> T;
    while (T--) solve();
}
