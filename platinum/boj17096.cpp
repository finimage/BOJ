#include<iostream>
#include<vector>
#include<queue>
#define ll long long
#define INF 250000000001
using namespace std;

struct info {
	int x;
	ll dis;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.dis > b.dis;
	}
};

vector<info> graph[500001];
priority_queue<info, vector<info>, cmp> pq;
ll dis[500001], path[500001];
int N, M, path_cnt[500001];

void init() {
	for (int i = 1; i <= N; i++) dis[i] = INF;
}

void dijkstra() {
	init();
	int x;
	ll dist;
	dis[1] = 0;
	pq.push({ 1,0 });
	while (!pq.empty()) {
		x = pq.top().x;
		dist = pq.top().dis;
		pq.pop();
		if (dist > dis[x]) continue;
		for (auto& iter : graph[x]) {
			if (dis[iter.x] > iter.dis + dist) {
				path[iter.x] = iter.dis;
				dis[iter.x] = iter.dis + dist;
				pq.push({ iter.x,dis[iter.x] });
			}
			else if (dis[iter.x] == iter.dis + dist && path[iter.x] > iter.dis) path[iter.x] = iter.dis;
		}
	}
}

void ans() {
	ll answer = 0;
	for (int i = 2; i <= N; i++) answer += path[i];
	cout << answer;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a, b; cin >> N >> M;
	ll c;
	while (M--) {
		cin >> a >> b >> c;
		graph[a].push_back({ b,c });
		graph[b].push_back({ a,c });
	}
	dijkstra();
	ans();
}
