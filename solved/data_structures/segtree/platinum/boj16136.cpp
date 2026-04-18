#include<bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> p;
int n, q, cnt[1000001];
ll arr[100001], tree[400004][2];

void update(int start, int end, int ind, int le, int ri, int k) {
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		if (k && tree[ind][1] <= 2) return;
		if (start == end) {
			if (k) arr[end] = cnt[arr[end]];
			tree[ind][0] = tree[ind][1] = arr[end];
			return;
		}
	}
	int mid = (start + end) / 2;
	update(start, mid, ind * 2, le, ri, k);
	update(mid + 1, end, ind * 2 + 1, le, ri, k);
	tree[ind][0] = tree[ind * 2][0] + tree[ind * 2 + 1][0];
	tree[ind][1] = max(tree[ind * 2][1], tree[ind * 2 + 1][1]);
}

ll res(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind][0];
	int mid = (start + end) / 2;
	return res(start, mid, ind * 2, le, ri) + res(mid + 1, end, ind * 2 + 1, le, ri);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, a, b, c; cin >> n >> q;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		update(1, n, 1, i, i, 0);
	}
	for (i = 1; i <= 1000000; i++) {
		for (j = 1; j * i <= 1000000; j++) cnt[j * i]++;
	}
	while (q--) {
		cin >> a >> b >> c;
		if (a == 1) update(1, n, 1, b, c, 1);
		else cout << res(1, n, 1, b, c) << '\n';
	}
}
