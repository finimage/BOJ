#include<bits/stdc++.h>
#define ll long long
#define pil pair<int, ll>
#define x first
#define y second
using namespace std;

struct info {
	int num, x, y;
	ll cost;
};

struct info_ {
	int x;
	ll y, z;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.cost > b.cost;
	}
};

int n, m, dep[100001], parent[100001];
info_ anc[100001][20];
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
	anc[ind][0] = {pre,(cost % 2 == 1 ? cost : -1),(cost % 2 == 0 ? cost : -1)};
	int l = log2(dep[ind]), i;
	for (i = 1; i <= l; i++) {
		anc[ind][i].x = anc[anc[ind][i - 1].x][i - 1].x;
		anc[ind][i].y = max(anc[ind][i - 1].y, anc[anc[ind][i - 1].x][i - 1].y);
		anc[ind][i].z = max(anc[ind][i - 1].z, anc[anc[ind][i - 1].x][i - 1].z);
	}
	for (auto& iter : g[ind]) {
		if (iter.x == pre) continue;
		dfs(iter.x, ind, iter.y);
	}
}

ll find_edge(int a, int b, ll comp) {
	ll cost[2] = {-1,-1};
	if (dep[a] != dep[b]) {
		if (dep[a] < dep[b]) swap(a, b);
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (dep[anc[a][i].x] >= dep[b]) {
				cost[0] = max(cost[0], anc[a][i].y);
				cost[1] = max(cost[1], anc[a][i].z);
				a = anc[a][i].x;
			}
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i].x != anc[b][i].x) {
				cost[0] = max(cost[0], max(anc[a][i].y, anc[b][i].y));
				cost[1] = max(cost[1], max(anc[a][i].z, anc[b][i].z));
				a = anc[a][i].x;
				b = anc[b][i].x;
			}
		}
		cost[0] = max(cost[0], max(anc[a][0].y, anc[b][0].y));
		cost[1] = max(cost[1], max(anc[a][0].z, anc[b][0].z));
	}
	if (comp % 2) return cost[1];
	return cost[0];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
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
	ll mst = 0, mst_odd = -1, mst_even = -1, cost;
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
	dfs(1, 0, -1);
	ans[0] = 1;
	if (mst % 2) {
		mst_odd = mst;
		for (auto& iter : edge) {
			if (ans[iter.num]) continue;
			cost = find_edge(iter.x,iter.y,iter.cost);
			if (cost == -1) continue;
			if (mst_even == -1) mst_even = mst + iter.cost - cost;
			else mst_even = min(mst_even, mst + iter.cost - cost);
		}
	}
	else {
		mst_even = mst;
		for (auto& iter : edge) {
			if (ans[iter.num]) continue;
			cost = find_edge(iter.x,iter.y,iter.cost);
			if (cost == -1) continue;
			if (mst_odd == -1) mst_odd = mst + iter.cost - cost;
			else mst_odd = min(mst_odd, mst + iter.cost - cost);
		}
	}
	cout << mst_odd << ' ' << mst_even;
}
