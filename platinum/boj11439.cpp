#include<iostream>
#include<vector>
#define ll long long
using namespace std;

bool prime_check[4000001];
vector<int> prime;

int div_(int a, int b) {
	int ret = 0;
	while (a) {
		ret += a / b;
		a /= b;
	}
	return ret;
}

ll res(ll a, ll b, ll mod) {
	if (b == 0) return 1;
	if (b == 1) return a % mod;
	ll k = res(a, b / 2, mod);
	return k * k % mod * (b % 2 ? a : 1) % mod;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, m, i, j; cin >> n >> k >> m;
	ll ans = 1;
	for (i = 2; i <= n; i++) prime_check[i] = 1;
	for (i = 2; i <= n; i++) {
		if (prime_check[i]) {
			prime.push_back(i);
			for (j = i; j <= n; j += i) prime_check[j] = 0;
		}
	}
	for (auto& iter : prime) {
		ans *= res(iter, (ll)(div_(n, iter) - div_(n - k, iter) - div_(k, iter)), m);
		ans %= (ll)m;
	}
	cout << ans;
}
