#include<iostream>
#include<queue>
#include<vector>
#define INF 100000000
using namespace std;

struct info {
	int x, d;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.d > b.d;
	}
};

struct cmp_ {
	bool operator()(const info& a, const info& b) {
		return a.d < b.d;
	}
};

int n, m, dist[1001], dp[1001];
bool visited[1001];
vector<vector<info>> g;
priority_queue<info, vector<info>, cmp> pq;
priority_queue<info, vector<info>, cmp_> pq_;

void init() {
	for (int i = 1; i <= n; i++) dist[i] = INF;
}

void dijkstra() {
	init();
	pq.push({ 2,0 });
	dist[2] = 0;
	int x, dis;
	while (!pq.empty()) {
		x = pq.top().x;
		dis = pq.top().d;
		pq.pop();
		if (dis > dist[x]) continue;
		for (auto& iter : g[x]) {
			if (dist[iter.x] > dis + iter.d) {
				dist[iter.x] = dis + iter.d;
				pq.push({ iter.x,dist[iter.x] });
			}
		}
	}
}

void searching() {
	pq_.push({ 1,dist[1] });
	int x, dis;
	dp[1] = 1;
	while (!pq_.empty()) {
		x = pq_.top().x;
		dis = pq_.top().d;
		pq_.pop();
		if (visited[x]) continue;
		visited[x] = 1;
		for (auto& iter : g[x]) {
			if (dis > dist[iter.x]) {
				dp[iter.x] += dp[x];
				pq_.push({ iter.x,dist[iter.x] });
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c; cin >> n >> m;
	g = vector<vector<info>>(n + 1);
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[a].push_back({ b,c });
		g[b].push_back({ a,c });
	}
	dijkstra();
	searching();
	cout << dp[2];
}
