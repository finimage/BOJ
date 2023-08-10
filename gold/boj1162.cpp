#include<iostream>
#include<queue>
#include<vector>
#define ll long long
using namespace std;

struct info {
	int x, cnt;
	ll dis;
};

struct cmp {
	bool operator()(const info& a, const info& b){
		return a.dis > b.dis;
	}
};

priority_queue<info, vector<info>, cmp> pq;
vector<info> graph[10001];
ll dist[10001][21];
int n, m, k;

void input() {
	int i, a, b; cin >> n >> m >> k;
	ll c;
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		graph[a].push_back({ b,0,c });
		graph[b].push_back({ a,0,c });
	}
}

void init() {
	int i, j;
	for (i = 2; i <= n; i++) {
		for (j = 0; j <= k; j++) dist[i][j] = 50000000001;
	}
}

void dijkstra() {
	pq.push({ 1,0,0 });
	int x, cnt;
	ll dis;
	while (!pq.empty()) {
		x = pq.top().x;
		cnt = pq.top().cnt;
		dis = pq.top().dis;
		pq.pop();
		if (dist[x][cnt] < dis) continue;
		for (auto& iter : graph[x]) {
			if (dist[iter.x][cnt] > dist[x][cnt] + iter.dis) {
				dist[iter.x][cnt] = dist[x][cnt] + iter.dis;
				pq.push({ iter.x,cnt,dist[iter.x][cnt] });
			}
			if (cnt < k && dist[iter.x][cnt + 1] > dist[x][cnt]) {
				dist[iter.x][cnt + 1] = dist[x][cnt];
				pq.push({ iter.x,cnt + 1,dist[iter.x][cnt + 1] });
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	init();
	dijkstra();
	ll ans = 50000000001;
	for (int i = 0; i <= k; i++) ans = min(ans, dist[n][i]);
	cout << ans;
}
