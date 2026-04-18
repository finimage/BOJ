#include<iostream>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, k, ans[2000001];
pii tree[8000004];

void lazy_pro(int start, int end, int ind) {
	if (start == end) return;
	int x = tree[ind].x, y = tree[ind].y;
	tree[ind] = { 0,100001 };
	tree[ind * 2].x = max(tree[ind * 2].x, x);
	tree[ind * 2].y = max(tree[ind * 2].y, x);
	tree[ind * 2 + 1].x = max(tree[ind * 2 + 1].x, x);
	tree[ind * 2 + 1].y = max(tree[ind * 2 + 1].y, x);
	tree[ind * 2].x = min(tree[ind * 2].x, y);
	tree[ind * 2].y = min(tree[ind * 2].y, y);
	tree[ind * 2 + 1].x = min(tree[ind * 2 + 1].x, y);
	tree[ind * 2 + 1].y = min(tree[ind * 2 + 1].y, y);
}

void update(int start, int end, int ind, int op, int le, int ri, int h) {
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		if (op == 1) {
			tree[ind].x = max(tree[ind].x, h);
			tree[ind].y = max(tree[ind].y, h);
		}
		else {
			tree[ind].x = min(tree[ind].x, h);
			tree[ind].y = min(tree[ind].y, h);
		}
		return;
	}
	lazy_pro(start, end, ind);
	int mid = (start + end) / 2;
	update(start, mid, ind * 2, op, le, ri, h);
	update(mid + 1, end, ind * 2 + 1, op, le, ri, h);
}

void fin(int start, int end, int ind) {
	lazy_pro(start, end, ind);
	if (start == end) {
		ans[start] = tree[ind].x;
		return;
	}
	int mid = (start + end) / 2;
	fin(start, mid, ind * 2);
	fin(mid + 1, end, ind * 2 + 1);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, op, le, ri, h; cin >> n >> k;
	while (k--) {
		cin >> op >> le >> ri >> h;
		update(1, n, 1, op, le + 1, ri + 1, h);
	}
	fin(1, n, 1);
	for (i = 1; i <= n; i++) cout << ans[i] << '\n';
}
