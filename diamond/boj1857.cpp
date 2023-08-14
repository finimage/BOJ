#include<iostream>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

int m, n, arr[31][31], start_, end_, dx[8] = { 2,2,-2,-2,1,1,-1,-1 }, dy[8] = { 1,-1,1,-1,2,-2,2,-2 }, dis[901];
vector<int> graph[901];
queue<int> q;
bool visited[901];
ll cnt[901];

void init() {
	for (int i = 0; i < m * n; i++) visited[i] = 0;
}

void dfs(int node, int link, int a, int b) {
	visited[link] = 1;
	if (arr[a][b] == 2) return;
	if (node != link && arr[a][b] != 1) {
		graph[node].push_back(link);
		return;
	}
	int i, x, y;
	for (i = 0; i < 8; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (0 <= x && x < m && 0 <= y && y < n) {
			if (visited[x * n + y]) continue;
			dfs(node, x * n + y, x, y);
		}
	}
}

void bfs() {
	dis[start_] = 1;
	cnt[start_] = 1;
	q.push(start_);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (auto& iter : graph[x]) {
			if (!dis[iter]) {
				dis[iter] = dis[x] + 1;
				cnt[iter] = cnt[x];
				q.push(iter);
			}
			else if (dis[iter] == dis[x] + 1) cnt[iter] += cnt[x];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> m >> n;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 3) start_ = i * n + j;
			if (arr[i][j] == 4) end_ = i * n + j;
		}
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (arr[i][j] == 2) continue;
			init();
			dfs(i * n + j, i * n + j, i, j);
		}
	}
	bfs();
	if (!dis[end_]) cout << -1;
	else cout << dis[end_] - 2 << '\n' << cnt[end_];
}
