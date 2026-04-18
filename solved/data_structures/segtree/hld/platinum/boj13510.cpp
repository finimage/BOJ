#include<bits/stdc++.h>
using namespace std;

struct info {
	int x, y, num;
};

int n, q, cnt;
vector<vector<info>> g;
vector<int> dep, parent, stsize, top, num[2], tree, val;

void dfs1(int ind, int pre) {
	dep[ind] = dep[pre] + 1;
	parent[ind] = pre;
	stsize[ind]++;
	for (auto& iter : g[ind]) {
		if (iter.x == pre) continue;
		dfs1(iter.x, ind);
		stsize[ind] += stsize[iter.x];
		if (stsize[g[ind][0].x] < stsize[iter.x]) swap(g[ind][0], iter);
	}
}

void dfs2(int ind, int pre, int v, int k) {
	num[0][k] = num[1][ind] = ++cnt;
	val[cnt] = v;
	for (auto& iter : g[ind]) {
		if (iter.x == pre) continue;
		top[iter.x] = iter.x == g[ind][0].x ? top[ind] : iter.x;
		dfs2(iter.x, ind, iter.y, iter.num);
	}
}

int init(int start, int end, int ind) {
	if (start == end) return tree[ind] = val[end];
	int mid = (start + end) / 2;
	return tree[ind] = max(init(start, mid, ind * 2), init(mid + 1, end, ind * 2 + 1));
}

int Max(int start, int end, int ind, int le, int ri) {
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind];
	int mid = (start + end) / 2;
	return max(Max(start, mid, ind * 2, le, ri), Max(mid + 1, end, ind * 2 + 1, le, ri));
}

int update(int start, int end, int ind, int i, int v) {
	if (i < start || end < i) return tree[ind];
	if (start == end) return tree[ind] = v;
	int mid = (start + end) / 2;
	return tree[ind] = max(update(start, mid, ind * 2, i, v), update(mid + 1, end, ind * 2 + 1, i, v));
}

int res(int a, int b) {
	int maxval = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		maxval = max(maxval, Max(1, n, 1, num[1][top[a]], num[1][a]));
		a = parent[top[a]];
	}
	if (dep[a] > dep[b]) swap(a, b);
	return max(maxval, Max(1, n, 1, num[1][a] + 1, num[1][b]));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a, b, c, i; cin >> n;
	g.resize(n + 1);
	dep.resize(n + 1);
	parent.resize(n + 1);
	stsize.resize(n + 1);
	top.resize(n + 1);
	num[0].resize(n + 1);
	num[1].resize(n + 1);
	tree.resize(4 * n + 4);
	val.resize(n + 1);
	for (i = 1; i < n; i++) {
		cin >> a >> b >> c;
		g[a].push_back({b,c,i});
		g[b].push_back({a,c,i});
	}
	dfs1(1, 0);
    top[1] = 1;
	dfs2(1, 0, 0, 0);
	init(1, n, 1);
	cin >> q;
	while (q--) {
		cin >> a >> b >> c;
		if (a == 1) update(1, n, 1, num[0][b], c);
		else cout << res(b, c) << '\n';
	}
}
