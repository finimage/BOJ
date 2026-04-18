#include<iostream>
#define ll long long
using namespace std;

ll arr[100001], tree[400004], lazy[400004];

void lazy_(int start, int end, int index) {
	ll k = lazy[index];
	if (k == 0) return;
	lazy[index] = 0;
	tree[index] += k * (ll)(end - start + 1);
	if (start == end) return;
	lazy[index * 2] += k;
	lazy[index * 2 + 1] += k;
}

ll init(int start, int end, int index) {
	if (start == end) {
		if (start == 1) return tree[index] = arr[1];
		return tree[index] = arr[start] - arr[start - 1];
	}
	int mid = (start + end) / 2;
	return tree[index] = init(start, mid, index * 2) + init(mid + 1, end, index * 2 + 1);
}

ll update(int start, int end, int index, int le, int ri, ll v) {
	lazy_(start, end, index);
	if (ri < start || end < le) return tree[index];
	if (le <= start && end <= ri) {
		tree[index] += (ll)(end - start + 1) * v;
		if (start != end) {
			lazy[index * 2]++;
			lazy[index * 2 + 1]++;
		}
		return tree[index];
	}
	int mid = (start + end) / 2;
	return tree[index] = update(start, mid, index * 2, le, ri, v) + update(mid + 1, end, index * 2 + 1, le, ri, v);
}

ll res(int start, int end, int index, int le, int ri) {
	lazy_(start, end, index);
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[index];
	int mid = (start + end) / 2;
	return res(start, mid, index * 2, le, ri) + res(mid + 1, end, index * 2 + 1, le, ri);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, a, b, c; cin >> n;
	for (i = 1; i <= n; i++) cin >> arr[i];
	init(1, n, 1);
	cin >> m;
	while (m--) {
		cin >> a >> b;
		if (a == 1) {
			cin >> c;
			update(1, n, 1, b, c, 1);
			update(1, n, 1, c + 1, c + 1, (ll)(b - c - 1));
		}
		else cout << res(1, n, 1, 1, b) << '\n';
	}
}
