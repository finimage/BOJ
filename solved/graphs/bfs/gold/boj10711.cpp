#include<iostream>
#include<queue>
#define x first
#define y second
using namespace std;

queue<pair<int, int>> q[2];
int h, w, dx[8] = { 1,1,1,0,0,-1,-1,-1 }, dy[8] = { 1,0,-1,1,-1,1,0,-1 };
char g[1001][1001];
bool visited[1001][1001];

bool check(int a, int b) {
	int cnt = 0, i, x, y;	for (i = 0; i < 8; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (0 <= x && x < h && 0 <= y && y < w) {
			if (g[x][y] == '.') cnt++;
		}
	}
	return cnt >= (int)(g[a][b] - '0');
}

void bfs(int k1, int k2) {
	int a, b, x, y, i;
	while (!q[k1].empty()) {
		a = q[k1].front().x;
		b = q[k1].front().y;
		g[a][b] = '.';
		q[k1].pop();
		for (i = 0; i < 8; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (visited[x][y]) continue;
			if (0 <= x && x < h && 0 <= y && y < w) {
				if ('0' > g[x][y] || g[x][y] > '9') continue;
				if (check(x, y)) {
					q[k2].push({ x,y });
					visited[x][y] = 1;
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, ans = 0; cin >> h >> w;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) cin >> g[i][j];
	}
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if ('0' <= g[i][j] && g[i][j] <= '9') {
				if (check(i, j)) {
					q[0].push({ i,j });
					visited[i][j] = 1;
				}
			}
		}
	}
	while (1) {
		if (q[ans % 2].empty()) break;
		bfs(ans % 2, (ans + 1) % 2);
		ans++;
	}
	cout << ans;
}
