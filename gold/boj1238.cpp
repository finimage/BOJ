#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int x, dis;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.dis > b.dis;
	}
};

vector<info> g[2][1001];
priority_queue<info, vector<info>, cmp> pq;
int n, m, x, dist[2][1001];

void dijkstra(int t) {
	pq.push({ x,0 });
	dist[t][x] = 0;
	int x, dis;
	while (!pq.empty()) {
		x = pq.top().x;
		dis = pq.top().dis;
		pq.pop();
		if (dis > dist[t][x]) continue;
		for (auto& iter : g[t][x]) {
			if (dist[t][iter.x] > dis + iter.dis) {
				dist[t][iter.x] = dis + iter.dis;
				pq.push({ iter.x,dist[t][iter.x] });
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c, ans = 0; cin >> n >> m >> x;
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[0][a].push_back({ b,c });
		g[1][b].push_back({ a,c });
	}
	for (i = 1; i <= n; i++) dist[0][i] = dist[1][i] = 1000001;
	dijkstra(0);
	dijkstra(1);
	for (i = 1; i <= n; i++) ans = max(ans, dist[0][i] + dist[1][i]);
	cout << ans;
}
