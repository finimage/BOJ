#include<bits/stdc++.h>
#define ll long long
#define pil pair<int, ll>
#define x first
#define y second
using namespace std;

struct info {
	int num, x, y, cost;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.cost > b.cost;
	}
};

int n, m, dep[200001], parent[200001];
pil anc[200001][20];
vector<info> edge;
vector<ll> ans;
vector<int> mst_edge;
vector<vector<pil>> g;
priority_queue<info, vector<info>, cmp> pq;

int find_(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find_(parent[a]);
}

bool union_(int a, int b) {
	a = find_(a);
	b = find_(b);
	if (a == b) return 1;
	parent[a] = b;
	return 0;
}

void dfs(int ind, int pre, ll cost) {
	dep[ind] = dep[pre] + 1;
	anc[ind][0] = {pre,cost};
	int l = log2(dep[ind]), i;
	for (i = 1; i <= l; i++) anc[ind][i] = {anc[anc[ind][i - 1].x][i - 1].x,max(anc[anc[ind][i - 1].x][i - 1].y,anc[ind][i - 1].y)};
	for (auto& iter : g[ind]) {
		if (iter.x == pre) continue;
		dfs(iter.x, ind, iter.y);
	}
}

ll find_edge(int a, int b) {
	ll cost = 0;
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (dep[anc[a][i].x] >= dep[b]) {
				cost = max(cost, anc[a][i].y);
				a = anc[a][i].x;
			}
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i].x != anc[b][i].x) {
				cost = max(cost, max(anc[a][i].y, anc[b][i].y));
				a = anc[a][i].x;
				b = anc[b][i].x;
			}
		}
		cost = max(cost, max(anc[a][0].y, anc[b][0].y));
	}
	return cost;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int i, a, b, num; cin >> n >> m;
	g.resize(n + 1);
	edge.resize(m + 1);
	ans.resize(m + 1, 0);
	for (i = 1; i <= m; i++) {
		cin >> edge[i].x >> edge[i].y >> edge[i].cost;
		edge[i].num = i;
		pq.push(edge[i]);
	}
	for (i = 1; i <= n; i++) parent[i] = i;
	ll mst = 0, cost;
	while (!pq.empty()) {
		num = pq.top().num;
		a = pq.top().x;
		b = pq.top().y;
		cost = pq.top().cost;
		pq.pop();
		if (union_(a, b)) continue;
		mst += cost;
		mst_edge.push_back(num);
		g[a].push_back({b,cost});
		g[b].push_back({a,cost});
	}
	for (auto& iter : mst_edge) ans[iter] = mst;
	dfs(1, 0, 0);
	for (auto& iter : edge) {
		if (ans[iter.num]) continue;
		cost = find_edge(iter.x,iter.y);
		ans[iter.num] = mst + iter.cost - cost;
	}
	for (i = 1; i <= m; i++) cout << ans[i] << '\n';
}
