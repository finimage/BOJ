#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n, q;
ll arr[100001], tree[400004][2], lazy[400004];

ll gcd(ll a, ll b) {
	while (b) {
		ll r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void lazy_pro(int start, int end, int ind) {
	if (lazy[ind]) {
		ll k = lazy[ind];
		lazy[ind] = 0;
		if (start == end) {
			tree[ind][0] += k;
			return;
		}
		lazy[ind * 2] += k;
		lazy[ind * 2 + 1] += k;
	}
}

ll init(int start, int end, int ind) {
	if (start == end) {
		tree[ind][0] = arr[start];
		return tree[ind][1] = abs(arr[start] - arr[start - 1]);
	}
	int mid = (start + end) / 2;
	return tree[ind][1] = gcd(init(start, mid, ind * 2), init(mid + 1, end, ind * 2 + 1));
}

void update(int start, int end, int ind, int le, int ri, ll v) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		if (start == end) {
			tree[ind][0] += v;
			return;
		}
		lazy[ind * 2] += v;
		lazy[ind * 2 + 1] += v;
		return;
	}
	int mid = (start + end) / 2;
	update(start, mid, ind * 2, le, ri, v);
	update(mid + 1, end, ind * 2 + 1, le, ri, v);
}

ll update_gcd(int start, int end, int ind, int i, ll v) {
	if (i < start || end < i) return tree[ind][1];
	if (start == end) return tree[ind][1] = v;
	int mid = (start + end) / 2;
	return tree[ind][1] = gcd(update_gcd(start, mid, ind * 2, i, v), update_gcd(mid + 1, end, ind * 2 + 1, i, v));
}

ll range_gcd(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind][1];
	int mid = (start + end) / 2;
	return gcd(range_gcd(start, mid, ind * 2, le, ri), range_gcd(mid + 1, end, ind * 2 + 1, le, ri));
}

ll val(int start, int end, int ind, int i) {
	lazy_pro(start, end, ind);
	if (i < start || end < i) return 0;
	if (start == end) return tree[ind][0];
	int mid = (start + end) / 2;
	return val(start, mid, ind * 2, i) + val(mid + 1, end, ind * 2 + 1, i);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, t, a, b; cin >> n;
	for (i = 1; i <= n; i++) cin >> arr[i];
	init(1, n, 1);
	cin >> q;
	while (q--) {
		cin >> t >> a >> b;
		if (t) {
			update(1, n, 1, a, b, t);
			ll tmp = abs(val(1, n, 1, a) - val(1, n, 1, a - 1));
			update_gcd(1, n, 1, a, tmp);
			if (b != n) {
				tmp = abs(val(1, n, 1, b + 1) - val(1, n, 1, b));
				update_gcd(1, n, 1, b + 1, tmp);
			}
		}
		else {
			cout << gcd(val(1, n, 1, a), range_gcd(1, n, 1, a + 1, b)) << '\n';
		}
	}
}
