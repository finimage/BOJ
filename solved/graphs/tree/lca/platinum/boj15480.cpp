#include<bits/stdc++.h>
using namespace std;

int n, q, dep[100001], anc[100001][20];
vector<vector<int>> g;

void dfs(int ind, int pre) {
	dep[ind] = dep[pre] + 1;
	anc[ind][0] = pre;
	int l = log2(dep[ind]), i;
	for (i = 1; i <= l; i++) anc[ind][i] = anc[anc[ind][i - 1]][i - 1];
	for (auto& iter : g[ind]) {
		if (iter == pre) continue;
		dfs(iter, ind);
	}
}

int lca(int a, int b) {
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (dep[anc[a][i]] >= dep[b]) a = anc[a][i];
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i] != anc[b][i]) {
				a = anc[a][i];
				b = anc[b][i];
			}
		}
		a = anc[a][0];
		b = anc[b][0];
	}
	return a;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, r, u, v; cin >> n;
	g.resize(n + 1);
	for (i = 1; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	cin >> q;
	while (q--) {
		cin >> r >> u >> v;
		cout << (lca(u, v) ^ lca(u, r) ^ lca(v, r)) << '\n';
	}
}
