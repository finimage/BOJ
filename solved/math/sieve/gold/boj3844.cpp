#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

ll n;
bool sieve[10000001];
vector<int> prime;

void preprocess() {
    for (int i = 2; i < 10000000; i++) {
        if (!sieve[i]) {
            for (ll j = (ll)i * i; j < 10000000; j += i) sieve[j] = 1;
            prime.emplace_back(i);
        }
    }
}

ll powmod(ll a, ll b) {
    if (b == 0) return 1;
    ll tmp = powmod(a, b / 2);
    return tmp * tmp % MOD * (b % 2 ? a : 1) % MOD;
}

void solve() {
    cin >> n;
    while (n) {
        ll ans = 1;
        for (int i = 0; i < prime.size() && prime[i] < n; i++) {
            ll k = n, res = 0;
            while (k) {
                res += k / prime[i];
                k /= prime[i];
            }
            ans = ans * powmod(prime[i], res / 2 * 2) % MOD;
        }
        cout << ans << '\n';
        cin >> n;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    preprocess();
    while (T--) solve();
}
