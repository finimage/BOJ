#include<bits/stdc++.h>
#define ll long long
#define pil pair<int, ll>
#define x first
#define y second
using namespace std;

int n, dep[100001];
pil anc[100001][20];
vector<vector<pil>> g;

void dfs(int ind, int pre, int cost) {
	dep[ind] = dep[pre] + 1;
	anc[ind][0] = {pre,cost};
	int l = log2(dep[ind]), i;
	for (i = 1; i <= l; i++) anc[ind][i] = {anc[anc[ind][i - 1].x][i - 1].x,anc[ind][i - 1].y + anc[anc[ind][i - 1].x][i - 1].y};
	for (auto& iter : g[ind]) {
		if (iter.x == pre) continue;
		dfs(iter.x, ind, iter.y);
	}
}

ll res1(int a, int b) {
	ll ans = 0;
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (dep[anc[a][i].x] >= dep[b]) {
				ans += anc[a][i].y;
				a = anc[a][i].x;
			}
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i].x != anc[b][i].x) {
				ans += anc[a][i].y + anc[b][i].y;
				a = anc[a][i].x;
				b = anc[b][i].x;
			}
		}
		ans += anc[a][0].y + anc[b][0].y;
	}
	return ans;
}

int res2(int u, int v, int k) {
	int a = u, b = v, ans = u;
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (dep[anc[a][i].x] >= dep[b]) a = anc[a][i].x;
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i].x != anc[b][i].x) {
				a = anc[a][i].x;
				b = anc[b][i].x;
			}
		}
		a = anc[a][0].x;
	}
	if (dep[u] - dep[a] + 1 >= k) {
		int l = log2(dep[u]), i, t;
		k--;
		t = (1 << l);
		for (i = l; i >= 0; i--) {
			if (k >= t) {
				k -= t;
				u = anc[u][i].x;
			}
			t >>= 1;
		}
		return u;
	}
	else {
		k = dep[u] - dep[a] + dep[v] - dep[a] + 1 - k;
		int l = log2(dep[v]), i, t;
		t = (1 << l);
		for (i = l; i >= 0; i--) {
			if (k >= t) {
				k -= t;
				v = anc[v][i].x;
			}
			t >>= 1;
		}
		return v;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c, d, q; cin >> n;
	g.resize(n + 1);
	for (i = 1; i < n; i++) {
		cin >> a >> b >> c;
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	dfs(1, 0, 0);
	cin >> q;
	while (q--) {
		cin >> a >> b >> c;
		if (a == 1) cout << res1(b, c) << '\n';
		else {
			cin >> d;
			cout << res2(b, c, d) << '\n';
		}
	}
}
