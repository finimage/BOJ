#include<iostream>
#include<algorithm>
using namespace std;

struct info {
	int a[3];
};

bool cmp(const info& a, const info& b) {
	return a.a[0] < b.a[0];
}

info arr[500001];
int tree[2000004];

void init(int start, int end, int ind) {
	tree[ind] = 500001;
	if (start == end) return;
	int mid = (start + end) / 2;
	init(start, mid, ind * 2);
	init(mid + 1, end, ind * 2 + 1);
}

int update(int start, int end, int ind, int i, int v) {
	if (i < start || end < i) return tree[ind];
	if (start == end) return tree[ind] = v;
	int mid = (start + end) / 2;
	return tree[ind] = min(update(start, mid, ind * 2, i, v), update(mid + 1, end, ind * 2 + 1, i, v));
}

int find_min(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 500001;
	if (le <= start && end <= ri) return tree[ind];
	int mid = (start + end) / 2;
	return min(find_min(start, mid, ind * 2, le, ri), find_min(mid + 1, end, ind * 2 + 1, le, ri));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, j, t, ans = 0; cin >> n;
	for (i = 0; i < 3; i++) {
		for (j = 1; j <= n; j++) {
			cin >> t;
			arr[t].a[i] = j;
		}
	}
	init(1, n, 1);
	sort(arr + 1, arr + n + 1, cmp);
	for (i = 1; i <= n; i++) {
		if (find_min(1, n, 1, 1, arr[i].a[1] - 1) > arr[i].a[2]) ans++;
		update(1, n, 1, arr[i].a[1], arr[i].a[2]);
	}
	cout << ans;
}
