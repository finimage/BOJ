#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int x, y;
};

int n, arr[16][16], cnt, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
char graph[16][16];
bool visited[16][16], tf;
queue<info> q[2];

void bfs(int k) {
	int i, j, a, b, x, y;
	bool check[626] = { 0, };
	while (!q[k].empty()) {
		a = q[k].front().x;
		b = q[k].front().y;
		q[k].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < n) {
				if (visited[x][y]) continue;
				visited[x][y] = 1;
				check[arr[x][y]] = 1;
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (check[arr[i][j]]) {
				visited[i][j] = 1;
				q[(k + 1) % 2].push({ i,j });
			}
		}
	}
	if (q[(k + 1) % 2].empty()) tf = 1;
}

void init() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) visited[i][j] = 0;
	}
}

void make_group(int a, int b, char cmp) {
	queue<pair<int, int>> q;
	q.push({ a,b });
	visited[a][b] = 1;
	cnt++;
	arr[a][b] = cnt;
	int x, y, i;
	while (!q.empty()) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < n) {
				if (visited[x][y]) continue;
				if (graph[x][y] == cmp) {
					visited[x][y] = 1;
					arr[x][y] = cnt;
					q.push({ x,y });
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, t, ans = 1000, temp; cin >> n;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) cin >> graph[i][j];
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (visited[i][j]) continue;
			make_group(i, j, graph[i][j]);
		}
	}
	init();
	for (i = 1; i <= cnt; i++) {
		temp = 0;
		tf = 0;
		for (j = 0; j < n; j++) {
			for (t = 0; t < n; t++) {
				if (arr[j][t] == i) {
					q[0].push({ j,t });
					visited[j][t] = 1;
				}
			}
		}
		while (1) {
			bfs(temp % 2);
			if (tf) break;
			temp++;
		}
		ans = min(ans, temp);
		init();
	}
	cout << ans;
}
