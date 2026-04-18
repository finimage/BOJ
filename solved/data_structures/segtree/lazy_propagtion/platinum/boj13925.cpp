#include<iostream>
#define ll long long
#define MOD 1000000007
using namespace std;

ll arr[100001], tree[400004], lazy[400004][2];

ll init(int start, int end, int ind) {
	lazy[ind][1] = 1;
	if (start == end) return tree[ind] = arr[start];
	int mid = (start + end) / 2;
	return tree[ind] = (init(start, mid, ind * 2) + init(mid + 1, end, ind * 2 + 1)) % MOD;
}

void lazy_pro(int start, int end, int ind) {
	if (lazy[ind][1] == 1 && lazy[ind][0] == 0) return;
	ll k1 = lazy[ind][1], k2 = lazy[ind][0];
	lazy[ind][1] = 1, lazy[ind][0] = 0;
	tree[ind] = (tree[ind] * k1 % MOD + k2 * (ll)(end - start + 1) % MOD) % MOD;
	if (start == end) return;
	lazy[ind * 2][1] = (lazy[ind * 2][1] * k1) % MOD;
	lazy[ind * 2][0] = (lazy[ind * 2][0] * k1 % MOD + k2) % MOD;
	lazy[ind * 2 + 1][1] = (lazy[ind * 2 + 1][1] * k1) % MOD;
	lazy[ind * 2 + 1][0] = (lazy[ind * 2 + 1][0] * k1 % MOD + k2) % MOD;
}

void update_add(int start, int end, int ind, int le, int ri, ll v) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		tree[ind] = (tree[ind] + v * (ll)(end - start + 1) % MOD) % MOD;
		if (start == end) return;
		lazy[ind * 2][0] = (lazy[ind * 2][0] + v) % MOD;
		lazy[ind * 2 + 1][0] = (lazy[ind * 2 + 1][0] + v) % MOD;
		return;
	}
	int mid = (start + end) / 2;
	update_add(start, mid, ind * 2, le, ri, v);
	update_add(mid + 1, end, ind * 2 + 1, le, ri, v);
	tree[ind] = (tree[ind * 2] + tree[ind * 2 + 1]) % MOD;
}

void update_mul(int start, int end, int ind, int le, int ri, ll v) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		tree[ind] = tree[ind] * v % MOD;
		if (start == end) return;
		lazy[ind * 2][1] = lazy[ind * 2][1] * v % MOD;
		lazy[ind * 2][0] = lazy[ind * 2][0] * v % MOD;
		lazy[ind * 2 + 1][1] = lazy[ind * 2 + 1][1] * v % MOD;
		lazy[ind * 2 + 1][0] = lazy[ind * 2 + 1][0] * v % MOD;
		return;
	}
	int mid = (start + end) / 2;
	update_mul(start, mid, ind * 2, le, ri, v);
	update_mul(mid + 1, end, ind * 2 + 1, le, ri, v);
	tree[ind] = (tree[ind * 2] + tree[ind * 2 + 1]) % MOD;
}

void change(int start, int end, int ind, int le, int ri, ll v) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		tree[ind] = v * (ll)(end - start + 1) % MOD;
		if (start == end) return;
		lazy[ind * 2][1] = 0;
		lazy[ind * 2][0] = v;
		lazy[ind * 2 + 1][1] = 0;
		lazy[ind * 2 + 1][0] = v;
		return;
	}
	int mid = (start + end) / 2;
	change(start, mid, ind * 2, le, ri, v);
	change(mid + 1, end, ind * 2 + 1, le, ri, v);
	tree[ind] = (tree[ind * 2] + tree[ind * 2 + 1]) % MOD;
}

ll sum(int start, int end, int ind, int le, int ri) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind];
	int mid = (start + end) / 2;
	return (sum(start, mid, ind * 2, le, ri) + sum(mid + 1, end, ind * 2 + 1, le, ri)) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, a, x, y; cin >> n;
	ll v;
	for (i = 1; i <= n; i++) cin >> arr[i];
	init(1, n, 1);
	cin >> m;
	while (m--) {
		cin >> a >> x >> y;
		if (a == 4) cout << sum(1, n, 1, x, y) << '\n';
		else {
			cin >> v;
			if (a == 1) update_add(1, n, 1, x, y, v);
			else if (a == 2) update_mul(1, n, 1, x, y, v);
			else change(1, n, 1, x, y, v);
		}
	}
}
