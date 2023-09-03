#include<iostream>
#include<queue>
#define x first
#define y second
using namespace std;

int n, m, k, t, dx[8] = { 2,2,-2,-2,1,1,-1,-1 }, dy[8] = { 1,-1,1,-1,2,-2,2,-2 };
int graph[301][301][2];
queue<pair<int, int>> q[2];

void bfs(int t1) {
	int a, b, x, y, i, tf;
	while (!q[t1].empty()) {
		a = q[t1].front().x;
		b = q[t1].front().y;
		q[t1].pop();
		tf = 1;
		for (i = 0; i < 8; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 < x && x <= n && 0 < y && y <= n) {
				tf = 0;
				if (graph[x][y][t1] != -1) continue;
				graph[x][y][t1] = graph[a][b][t1] + 1;
				q[t1].push({ x,y });
			}
		}
		if (tf) graph[a][b][t1] = -1;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, a, b, temp; cin >> n >> m >> k >> t;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) graph[i][j][0] = graph[i][j][1] = -1;
	}
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		if ((a + b) % 2 == 0) {
			graph[a][b][0] = 0;
			q[0].push({a,b});
		}
		else {
			graph[a][b][1] = 0;
			q[1].push({ a,b });
		}
	}
	bfs(0);
	bfs(1);
	for (i = 0; i < k; i++) {
		cin >> a >> b;
		temp = graph[a][b][0];
		if (temp != -1 && temp <= t && (t - temp) % 2 == 0) {
			cout << "YES";
			return 0;
		}
		temp = graph[a][b][1];
		if (temp != -1 && temp <= t && (t - temp) % 2 == 0) {
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
}
