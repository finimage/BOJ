#include<iostream>
#include<queue>
using namespace std;

char graph[103][103];
int n, m, co[3][2], dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 }, dis[3][103][103];
bool visited[3][103][103];

struct info {
	int cnt, x, y;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.cnt > b.cnt;
	}
};

void dijkstra(int a, int b, int c) {
	priority_queue<info, vector<info>, cmp> pq;
	pq.push({ 0,a,b });
	dis[c][a][b] = 0;
	visited[c][a][b] = 1;
	int x, y, cnt, i;
	while (!pq.empty()) {
		a = pq.top().x;
		b = pq.top().y;
		cnt = pq.top().cnt;
		pq.pop();
		if (dis[c][a][b] < cnt) continue;
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x <= n + 1 && 0 <= y && y <= m + 1) {
				if (graph[x][y] == '*' || visited[c][x][y]) continue;
				visited[c][x][y] = 1;
				if (graph[x][y] == '.' && dis[c][x][y] > cnt) {
					dis[c][x][y] = cnt;
					pq.push({ cnt,x,y });
				}
				if (graph[x][y] == '#' && dis[c][x][y] > cnt + 1) {
					dis[c][x][y] = cnt + 1;
					pq.push({ cnt + 1,x,y });
				}
			}
		}
	}
}

void solve() {
	int i, j, ans = 30003;
	for (i = 0; i < 3; i++) dijkstra(co[i][0], co[i][1], i);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (graph[i][j] == '*') continue;
			if (graph[i][j] == '.') ans = min(ans, dis[0][i][j] + dis[1][i][j] + dis[2][i][j]);
			if (graph[i][j] == '#') ans = min(ans, dis[0][i][j] + dis[1][i][j] + dis[2][i][j] - 2);
		}
	}
	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T, i, j, tf; cin >> T;
	while (T--) {
		tf = 0;
		cin >> n >> m;
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				cin >> graph[i][j];
				if (graph[i][j] == '$') {
					graph[i][j] = '.';
					co[tf][0] = i, co[tf][1] = j;
					tf++;
				}
				dis[0][i][j] = dis[1][i][j] = dis[2][i][j] = 30003;
				visited[0][i][j] = visited[1][i][j] = visited[2][i][j] = 0;
			}
		}
		for (i = 0; i <= m + 1; i++) {
			dis[0][0][i] = dis[1][0][i] = dis[2][0][i] = 30003;
			dis[0][n + 1][i] = dis[1][n + 1][i] = dis[2][n + 1][i] = 30003;
			visited[0][0][i] = visited[1][0][i] = visited[2][0][i] = 0;
			visited[0][n + 1][i] = visited[1][n + 1][i] = visited[2][n + 1][i] = 0;
			graph[0][i] = graph[n + 1][i] = '.';
		}
		for (i = 0; i <= n + 1; i++) {
			dis[0][i][0] = dis[1][i][0] = dis[2][i][0] = 30003;
			dis[0][i][m + 1] = dis[1][i][m + 1] = dis[2][i][m + 1] = 30003;
			visited[0][i][0] = visited[1][i][0] = visited[2][i][0] = 0;
			visited[0][i][m + 1] = visited[1][i][m + 1] = visited[2][i][m + 1] = 0;
			graph[i][0] = graph[i][m + 1] = '.';
		}
		solve();
	}
}
