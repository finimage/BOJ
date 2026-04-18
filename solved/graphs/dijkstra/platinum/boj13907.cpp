#include<iostream>
#include<queue>
#include<vector>
#define INF 33000001
using namespace std;

struct info {
	int x, dis, cnt;
};

struct g_info {
	int x, dis;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.dis > b.dis;
	}
};

priority_queue<info, vector<info>, cmp> pq;
vector<g_info> graph[1001];
int N, M, K, start_, end_, dis_with_cnt[1001][1001], dist[1001][2];

void dijkstra() {
	pq.push({ start_,0,0 });
	int x, dis, cnt;
	while (!pq.empty()) {
		x = pq.top().x;
		dis = pq.top().dis;
		cnt = pq.top().cnt;
		pq.pop();
		if (dis > dis_with_cnt[cnt][x]) continue;
		for (auto& iter : graph[x]) {
			if (dist[iter.x][0] < cnt + 1 && dist[iter.x][1] < dis + iter.dis) continue;
			if (dis_with_cnt[cnt + 1][iter.x] > dis + iter.dis) {
				dis_with_cnt[cnt + 1][iter.x] = dis + iter.dis;
				pq.push({ iter.x,dis_with_cnt[cnt + 1][iter.x],cnt + 1 });
				if (dist[iter.x][1] > dis + iter.dis) {
					dist[iter.x][1] = dis + iter.dis;
					dist[iter.x][0] = cnt + 1;
				}
			}
		}
	}
}

void init() {
	int i, j;
	for (i = 0; i <= N; i++) {
		if (i == start_) continue;
		for (j = 0; j <= N; j++) dis_with_cnt[j][i] = dist[j][0] = dist[j][1] = INF;
	}
}

void input() {
	int a, b, c;
	while (M--) {
		cin >> a >> b >> c;
		graph[a].push_back({ b,c });
		graph[b].push_back({ a,c });
	}
}

void solve() {
	int tax, i, ans = INF;
	for (i = 1; i <= N; i++) {
		if (dis_with_cnt[i][end_] == INF) continue;
		ans = min(ans, dis_with_cnt[i][end_]);
	}
	cout << ans << '\n';
	while (K--) {
		cin >> tax;
		ans = INF;
		for (i = 1; i <= N; i++) {
			if (dis_with_cnt[i][end_] == INF) continue;
			dis_with_cnt[i][end_] += i * tax;
			ans = min(ans, dis_with_cnt[i][end_]);
		}
		cout << ans << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M >> K >> start_ >> end_;
	input();
	init();
	dijkstra();
	solve();
}
