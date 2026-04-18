#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct Edge {
	int x, y, T, R;
};

struct cmp {
	bool operator()(const pll& a, const pll& b) {
		return a.y > b.y;
	}
};

int n, m, PT, PR;
vector<vector<pii>> g;
vector<Edge> edge;
vector<int> ans;
vector<ll> pt, ppt, pr, ppr;
vector<pil> dist;
priority_queue<pll, vector<pll>, cmp> pq;

void dijkstra() {
	int a; ll dis;
	dist[n].y = 0;
	pq.push({n,0});
	while (!pq.empty()) {
		a = pq.top().x;
		dis = pq.top().y;
		pq.pop();
		if (dist[a].y < dis) continue;
		for (auto& iter : g[a]) {
			if (dist[iter.x].y > dis + iter.y) {
				dist[iter.x] = {a,dis + iter.y};
				pq.push({iter.x,dist[iter.x].y});
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n >> m;
	g.resize(n + 1);
	edge.resize(m + 1);
	for (i = 1; i <= m; i++) {
		cin >> edge[i].x >> edge[i].y >> edge[i].T >> edge[i].R;
		g[edge[i].y].push_back({edge[i].x,edge[i].R});
	}
	cin >> PT;
	pt.resize(PT + 2);
	ppt.resize(PT + 1);
	for (i = 1; i <= PT; i++) {
		cin >> a >> b;
		pt[i] += pt[i - 1] + edge[a].T;
		pt[i + 1] += b;
		ppt[i] += ppt[i - 1] + edge[a].T;
	}
	pt[PT + 1] += pt[PT];
	cin >> PR;
	pr.resize(PR + 1);
	ppr.resize(PR + 1);
	ppr[0] = 1;
	for (i = 1; i <= PR; i++) {
		cin >> a;
		pr[i] += pr[i - 1] + edge[a].R;
		ppr[i] = edge[a].y;
	}
	dist.resize(n + 1, {0,20000000000002});
	dijkstra();
	for (i = 0; i < PR; i++) {
		int le = 0, ri = PT, mid, tmp;
		while (le <= ri) {
			mid = (le + ri) / 2;
			if (pt[mid] <= pr[i]) {
				le = mid + 1;
				tmp = mid;
			}
			else ri = mid - 1;
		}
		mid = tmp;
		if (pt[mid + 1] > pr[i] && dist[ppr[i]].x != ppr[i + 1] && pt[mid + 1] - pr[i] + ppt[PT] - ppt[mid + 1] >= dist[ppr[i]].y) ans.emplace_back(ppr[i]);
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (auto& iter : ans) cout << iter << ' ';
}
