#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

/*
https://github.com/rkm0959/Number_Theory_in_CP_PS/blob/main/6.%20Miller-Rabin%20%EC%86%8C%EC%88%98%20%ED%8C%90%EB%B3%84%20%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98%EA%B3%BC%20Pollard-Rho%20%EC%86%8C%EC%9D%B8%EC%88%98%EB%B6%84%ED%95%B4/BOJ_4149.cpp
이를 수정해서 사용함
*/
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll n;
vector<ll> prime;

ll gcd(ll a, ll b) {
    while (b) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ll modmul(ll a, ll b, ll mod) {
	__int128 c = (__int128)a * (__int128)b;
	return (ll)(c % (__int128)mod);
}

ll modexp(ll a, ll b, ll mod) {
    ll ret = 1;
    while (b) {
        if (b % 2) {
            ret = modmul(ret, a, mod);
            b--;
        }
        a = modmul(a, a, mod);
        b /= 2;
    }
    return ret;
}

bool trial(ll a, ll mod) {
	if (a % mod == 0) return 0;
	ll cnt = -1, d = a - 1;
	while (d % 2 == 0) d /= 2, cnt++;
	ll p = modexp(mod, d, a);
	if (p == 1 || p == a - 1) return 1;
	while (cnt--) {
		p = modmul(p, p, a);
		if (p == a - 1) return 1;
	}
	return 0;
}

bool is_prime(ll a) {
	if (a == 1) return 0;
	ll i, tc[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
	for (i = 0; i < 12; i++) {
		if (a == tc[i]) return 1;
		if (a > 40 && !trial(a, tc[i])) return 0;
	}
	if (a <= 40) return 0;
	return 1;
}

ll PollardRho(ll a) {
	ll x = rng() % (a - 2) + 2;
    ll y = x;
	ll c = rng() % (a - 1) + 1;
	while (1) {
		x = modmul(x, x, a) + c;
        if (x >= a) x -= a;
		y = modmul(y, y, a) + c;
        if (y >= a) y -= a;
		y = modmul(y, y, a) + c;
        if (y >= a) y -= a;
		ll d = gcd(abs(x - y), a);
		if (d == 1) continue;
		if (!is_prime(d)) return PollardRho(d);
		else return d;
	}
}

void getFactor(ll a) {
    if (a % 2 == 0) prime.emplace_back(2);
	while (a % 2 == 0) a /= 2;
	while (a != 1 && !is_prime(a)) {
		ll d = PollardRho(a);
        if (a % d == 0) prime.emplace_back(d);
		while (a % d == 0) a /= d;
	}
	if (a != 1) prime.emplace_back(a);
}

ll res(ll a, ll b) {
    ll ret = 1;
	while (b){
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

ll vp(ll p, ll val) {
    ll ret = 0;
    while (val % p == 0) {
        val /= p;
        ret++;
    }
    return ret;
}

void solve() {
    cin >> n;
    getFactor(n);
    sort(prime.begin(), prime.end());
    for (auto& iter : prime) {
        while (n % iter == 0) {
            cout << iter << '\n';
            n /= iter;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
