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
}
;
struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.cost > b.cost;
	}
};

int n, m, dep[50001], parent[50001];
info_ anc[50001][20];
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
	anc[ind][0] = {pre,cost,-1};
	int l = log2(dep[ind]), i;
	for (i = 1; i <= l; i++) {
		anc[ind][i].x = anc[anc[ind][i - 1].x][i - 1].x;
		ll tmp[4] = {anc[anc[ind][i - 1].x][i - 1].y,anc[ind][i - 1].y,anc[anc[ind][i - 1].x][i - 1].z,anc[ind][i - 1].z};
		sort(tmp, tmp + 4);
		anc[ind][i].y = tmp[3];
		if (tmp[3] == tmp[2]) {
			if (tmp[2] == tmp[1]) {
				if (tmp[1] == tmp[0]) anc[ind][i].z = 0;
				else anc[ind][i].z = tmp[0];
			}
			else anc[ind][i].z = tmp[1];
		}
		else anc[ind][i].z = tmp[2];
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
				if (cost[0] < anc[a][i].y) {
					cost[1] = cost[0];
					cost[0] = anc[a][i].y;
					if (cost[1] < anc[a][i].z) cost[1] = anc[a][i].z;
				}
				else if (cost[0] == anc[a][i].y) {
					if (cost[1] < anc[a][i].z) cost[1] = anc[a][i].z;
				}
				else if (cost[1] < anc[a][i].y) cost[1] = anc[a][i].y;
				a = anc[a][i].x;
			}
		}
	}
	if (a != b) {
		int l = log2(dep[a]), i;
		for (i = l; i >= 0; i--) {
			if (anc[a][i].x != anc[b][i].x) {
				if (cost[0] < anc[a][i].y) {
					cost[1] = cost[0];
					cost[0] = anc[a][i].y;
					if (cost[1] < anc[a][i].z) cost[1] = anc[a][i].z;
				}
				else if (cost[0] == anc[a][i].y) {
					if (cost[1] < anc[a][i].z) cost[1] = anc[a][i].z;
				}
				else if (cost[1] < anc[a][i].y) cost[1] = anc[a][i].y;
				if (cost[0] < anc[b][i].y) {
					cost[1] = cost[0];
					cost[0] = anc[b][i].y;
					if (cost[1] < anc[b][i].z) cost[1] = anc[b][i].z;
				}
				else if (cost[0] == anc[b][i].y) {
					if (cost[1] < anc[b][i].z) cost[1] = anc[b][i].z;
				}
				else if (cost[1] < anc[b][i].y) cost[1] = anc[b][i].y;
				a = anc[a][i].x;
				b = anc[b][i].x;
			}
		}
		if (cost[0] < anc[a][0].y) {
			cost[1] = cost[0];
			cost[0] = anc[a][0].y;
			if (cost[1] < anc[a][0].z) cost[1] = anc[a][0].z;
		}
		else if (cost[0] == anc[a][0].y) {
			if (cost[1] < anc[a][0].z) cost[1] = anc[a][0].z;
		}
		else if (cost[1] < anc[a][0].y) cost[1] = anc[a][0].y;
		if (cost[0] < anc[b][0].y) {
			cost[1] = cost[0];
			cost[0] = anc[b][0].y;
			if (cost[1] < anc[b][0].z) cost[1] = anc[b][0].z;
		}
		else if (cost[0] == anc[b][0].y) {
			if (cost[1] < anc[b][0].z) cost[1] = anc[b][0].z;
		}
		else if (cost[1] < anc[b][0].y) cost[1] = anc[b][0].y;
	}
	if (cost[1] != -1) return (cost[0] == comp ? cost[1] : cost[0]);
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
	ll mst = 0, mst2 = 10000000000, cost;
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
	for (i = 1; i < n; i++) {
		if (find_(i) != find_(i + 1)) {
			cout << -1;
			return 0;
		}
	}
	for (auto& iter : mst_edge) ans[iter] = mst;
	dfs(1, 0, 0);
	ans[0] = 1;
	for (auto& iter : edge) {
		if (ans[iter.num]) continue;
		cost = find_edge(iter.x,iter.y,iter.cost);
		ans[iter.num] = mst + iter.cost - cost;
	}
	for (i = 1; i <= m; i++) {
		if (mst < ans[i]) mst2 = min(mst2, ans[i]);
	}
	cout << (mst2 == 10000000000 ? -1 : mst2);
}
