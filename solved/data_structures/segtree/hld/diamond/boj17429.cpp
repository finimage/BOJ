#include<bits/stdc++.h>
#define ll unsigned long long
#define MOD 4294967296
using namespace std;

int n, q, cnt;
vector<vector<int>> g;
vector<int> top, parent, stsize, dep, num;
vector<ll> tree, lazy[2];

void dfs1(int ind, int pre) {
	parent[ind] = pre;
	dep[ind] = dep[pre] + 1;
	stsize[ind]++;
	for (auto& iter : g[ind]) {
		if (iter == pre) continue;
		dfs1(iter, ind);
		stsize[ind] += stsize[iter];
		if (stsize[g[ind][0]] < stsize[iter]) swap(g[ind][0], iter);
	}
}

void dfs2(int ind, int pre) {
	num[ind] = ++cnt;
	for (auto& iter : g[ind]) {
		if (iter == pre) continue;
		top[iter] = iter == g[ind][0] ? top[ind] : iter;
		dfs2(iter, ind);
	}
}

void lazy_pro(int start, int end, int ind) {
	if (lazy[0][ind] == 1 && lazy[1][ind] == 0) return;
	ll a = lazy[0][ind], b = lazy[1][ind];
	lazy[0][ind] = 1;
	lazy[1][ind] = 0;
	tree[ind] = (tree[ind] * a % MOD + b * (end - start + 1) % MOD) % MOD;
	if (start == end) return;
	lazy[0][ind * 2] = lazy[0][ind * 2] * a % MOD;
	lazy[1][ind * 2] = (lazy[1][ind * 2] * a % MOD + b) % MOD;
	lazy[0][ind * 2 + 1] = lazy[0][ind * 2 + 1] * a % MOD;
	lazy[1][ind * 2 + 1] = (lazy[1][ind * 2 + 1] * a % MOD + b) % MOD;
}

void init(int start, int end, int ind) {
	lazy[0][ind] = 1;
	if (start == end) return;
	int mid = (start + end) / 2;
	init(start, mid, ind * 2);
	init(mid + 1, end, ind * 2 + 1);
}

void update(int start, int end, int ind, int le, int ri, ll v1, ll v2) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return;
	if (le <= start && end <= ri) {
		tree[ind] = (tree[ind] * v1 % MOD + v2 * (end - start + 1) % MOD) % MOD;
		if (start == end) return;
		lazy[0][ind * 2] = lazy[0][ind * 2] * v1 % MOD;
		lazy[1][ind * 2] = (lazy[1][ind * 2] * v1 % MOD + v2) % MOD;
		lazy[0][ind * 2 + 1] = lazy[0][ind * 2 + 1] * v1 % MOD;
		lazy[1][ind * 2 + 1] = (lazy[1][ind * 2 + 1] * v1 % MOD + v2) % MOD;
		return;
	}
	int mid = (start + end) / 2;
	update(start, mid, ind * 2, le, ri, v1, v2);
	update(mid + 1, end, ind * 2 + 1, le, ri, v1, v2);
	tree[ind] = (tree[ind * 2] + tree[ind * 2 + 1]) % MOD;
}

void update_path(int a, int b, ll v1, ll v2) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		update(1, n, 1, num[top[a]], num[a], v1, v2);
		a = parent[top[a]];
	}
	if (dep[a] > dep[b]) swap(a, b);
	update(1, n, 1, num[a], num[b], v1, v2);
}

ll res(int start, int end, int ind, int le, int ri) {
	lazy_pro(start, end, ind);
	if (ri < start || end < le) return 0;
	if (le <= start && end <= ri) return tree[ind];
	int mid = (start + end) / 2;
	return (res(start, mid, ind * 2, le, ri) + res(mid + 1, end, ind * 2 + 1, le, ri)) % MOD;
}

ll res_path(int a, int b) {
	ll sum = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		sum = (sum + res(1, n, 1, num[top[a]], num[a])) % MOD;
		a = parent[top[a]];
	}
	if (dep[a] > dep[b]) swap(a, b);
	return (sum + res(1, n, 1, num[a], num[b])) % MOD;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c, d; cin >> n >> q;
	g.resize(n + 1);
	top.resize(n + 1);
	parent.resize(n + 1);
	stsize.resize(n + 1);
	dep.resize(n + 1);
	num.resize(n + 1);
	tree.resize(4 * n + 4);
	lazy[0].resize(4 * n + 4);
	lazy[1].resize(4 * n + 4);
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	dfs1(1, 0);
	top[1] = 1;
	dfs2(1, 0);
	init(1, n, 1);
	while (q--) {
		cin >> a >> b;
		if (a == 1) {
			cin >> c;
			update(1, n, 1, num[b], num[b] + stsize[b] - 1, 1, c);
		}
		else if (a == 2) {
			cin >> c >> d;
			update_path(b, c, 1, d);
		}
		else if (a == 3) {
			cin >> c;
			update(1, n, 1, num[b], num[b] + stsize[b] - 1, c, 0);
		}
		else if (a == 4) {
			cin >> c >> d;
			update_path(b, c, d, 0);
		}
		else if (a == 5) {
			cout << res(1, n, 1, num[b], num[b] + stsize[b] - 1) << '\n';
		}
		else {
			cin >> c;
			cout << res_path(b, c) << '\n';
		}
	}
}
