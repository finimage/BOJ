#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct Edge {
	int x, y;
	ll cost;
};

int n, q, dep[100001];
ll anc[100001][20], sum[100001][20], Max[100001][20];
vector<vector<pii>> g;
vector<Edge> edge;

void dfs(int ind, int pre, int num) {
	dep[ind] = dep[pre] + 1;
	anc[ind][0] = pre;
	sum[ind][0] = edge[num].cost;
	Max[ind][0] = num;
	int l = (int)log2(dep[ind]), i;
	for (i = 1; i <= l; i++) {
		anc[ind][i] = anc[anc[ind][i - 1]][i - 1];
		Max[ind][i] = edge[Max[ind][i - 1]].cost > edge[Max[anc[ind][i - 1]][i - 1]].cost ? Max[ind][i - 1] : Max[anc[ind][i - 1]][i - 1];
		sum[ind][i] = sum[ind][i - 1] + sum[anc[ind][i - 1]][i - 1];
	}
	for (auto& iter : g[ind]) {
		if (iter.x == pre) continue;
		dfs(iter.x, ind, iter.y);
	}
}

ll lca(int a, int b, int tf) {
	ll s = 0, m = 0;
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (dep[anc[a][i]] >= dep[b]) {
				m = edge[m].cost > edge[Max[a][i]].cost ? m : Max[a][i];
				s += sum[a][i];
				a = anc[a][i];
			}
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i] != anc[b][i]) {
				m = edge[m].cost > edge[Max[a][i]].cost ? m : Max[a][i];
				s += sum[a][i];
				a = anc[a][i];
				m = edge[m].cost > edge[Max[b][i]].cost ? m : Max[b][i];
				s += sum[b][i];
				b = anc[b][i];
			}
		}
		m = edge[m].cost > edge[Max[a][0]].cost ? m : Max[a][0];
		s += sum[a][0];
		a = anc[a][0];
		m = edge[m].cost > edge[Max[b][0]].cost ? m : Max[b][0];
		s += sum[b][0];
		b = anc[b][0];
	}
	if (tf) return m;
	return s;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, u, v, a, b, c; cin >> n >> q;
	g.resize(n + 1);
	edge.resize(n + 1);
	for (i = 1; i < n; i++) {
		cin >> a >> b >> c;
		edge[i] = {a,b,c};
		g[a].push_back({b,i});
		g[b].push_back({a,i});
	}
	dfs(1, 0, 0);
	while (q--) {
		cin >> u >> v >> c >> a >> b;
		int m = lca(u, v, 1);
		ll tmp[8];
		tmp[0] = lca(a, edge[m].x, 0);
		tmp[1] = lca(edge[m].x, b, 0);
		tmp[2] = lca(a, edge[m].y, 0);
		tmp[3] = lca(edge[m].y, b, 0);
		if (tmp[0] + tmp[1] == tmp[2] + tmp[3]) {
			tmp[4] = lca(edge[m].x, u, 0);
			tmp[5] = lca(edge[m].y, u, 0);
			if (tmp[0] + tmp[4] == tmp[2] + tmp[5]) {
				tmp[6] = lca(a, v, 0);
				tmp[7] = lca(u, b, 0);
			}
			else {
				tmp[6] = lca(a, u, 0);
				tmp[7] = lca(v, b, 0);
			}
			cout << tmp[6] + tmp[7] + c << '\n';
		}
		else cout << lca(a, b, 0) << '\n';
		//a,b의 경로를 봐야되므로 경우를 나누어야 함
		//영향을 받는 경우 -> 끊으려는 간선(u', v')이 포함됨
		//포함된다면 (a,u') + (u',b) == (a,v') + (v',b)
		// if (a,u') + (u',u) == (a,v') + (v',u)
		// ans = c + (a,v) + (u,b)
		// else
		// ans = c + (a,u) + (v,b)
		//받지 않는 경우
	}
}
