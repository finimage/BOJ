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

int find_mid(int u, int v) {
	int a = u, b = v, dis = 0;
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
	}
	dis = dep[u] - dep[a] + dep[v] - dep[a];
	if (dis % 2 == 1) return -1;
	dis /= 2;
	if (dep[u] - dep[a] < dis) {
		int l = log2(dep[v]), i, t;
		t = (1 << l);
		for (i = l; i >= 0; i--) {
			if (t <= dis) {
				dis -= t;
				v = anc[v][i];
			}
			t >>= 1;
		}
		return v;
	}
	else {
		int l = log2(dep[u]), i, t;
		t = (1 << l);
		for (i = l; i >= 0; i--) {
			if (t <= dis) {
				dis -= t;
				u = anc[u][i];
			}
			t >>= 1;
		}
		return u;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c, tmp[3]; cin >> n;
	g.resize(n + 1);
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, 0);
	cin >> q;
	while (q--) {
		cin >> a >> b >> c;
		tmp[0] = find_mid(a, b);
		tmp[1] = find_mid(b, c);
		tmp[2] = find_mid(c, a);
		sort(tmp, tmp + 3);
		if (tmp[0] == -1) cout << -1 << '\n';
		else if (tmp[0] == tmp[1]) cout << tmp[0] << '\n';
		else if (tmp[1] == tmp[2]) cout << tmp[1] << '\n';
		else cout << -1 << '\n';
	}
}
