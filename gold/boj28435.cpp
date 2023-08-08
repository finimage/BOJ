#include<iostream>
#define ll long long
#define Mod 1000000007
using namespace std;

int cnt[100001];
ll check[100001];

ll process(int a) {
	ll k = 1;
	while (a--) {
		k *= 2;
		k %= Mod;
	}
	return k - 1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, i, a; cin >> n >> k;
	ll ans = 1;
	for (i = 0; i < n; i++) {
		cin >> a;
		cnt[a % k]++;
	}
	for (i = 0; i <= k / 2; i++) {
		check[i] = process(cnt[i]) + process(cnt[k - i]) + 1;
		if (i == 0) check[i] = cnt[i] + 1;
		if (k % 2 == 0 && i == k / 2) check[i] = cnt[i] + 1;
	}
	for (i = 0; i <= k / 2; i++) {
		ans *= check[i];
		ans %= Mod;
	}
	cout << (ans + Mod - n - 1) % Mod;
}
