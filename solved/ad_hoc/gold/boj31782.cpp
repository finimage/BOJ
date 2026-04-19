#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, m, k, ans, dx[4] = {1,0,0,-1}, dy[4] = {0,1,-1,0};
char g[2001][2001];
bool visited[2001][2001];

queue<pii> q;

bool check(int a, int b) {
	int i, x, y, cnt = 0;
	for (i = 0; i < 4; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (1 <= x && x <= n && 1 <= y && y <= m) {
			cnt += g[x][y] == 'O';
		}
	}
	return cnt >= 2;
}

void bfs() {
	int a, b, x, y, i;
	while (!q.empty()) {
		a = q.front().x;
		b = q.front().y;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (1 <= x && x <= n && 1 <= y && y <= m) {
				if (g[x][y] == '.') {
					if (check(x, y)) {
						g[x][y] = 'O';
						q.push({x,y});
					}
				}
			}
		}
	}
}

pii find_(int a, int b) {
	int x = a, y = b, i, j;
	while (x <= n) {
		if (g[x][b] == '.') break;
		x++;
	}
	while (y <= m) {
		if (g[a][y] == '.') break;
		y++;
	}
	for (i = a; i < x; i++) {
		for (j = b; j < y; j++) visited[i][j] = 1;
	}
	return {x - a,y - b};
}

void find_rec() {
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (!visited[i][j] && g[i][j] == 'O') {
				pii tmp = find_(i, j);
				if (tmp.x > k && tmp.y > k) ans += tmp.x * tmp.y;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n >> m >> k;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> g[i][j];
			if (g[i][j] == 'O') q.push({i,j});
		}
	}
	bfs();
	find_rec();
	cout << ans;
}
