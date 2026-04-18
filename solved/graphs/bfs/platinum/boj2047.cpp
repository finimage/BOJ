#include<iostream>
#include<queue>
#include<cstring>
#define x first
#define y second
using namespace std;

int h, w, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
char g[97][97];
bool visited[97][97];
queue<pair<int, int>> q;

void input() {
	int i, j; cin >> h >> w;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			cin >> g[i][j];
			if (g[i][j] == 's') q.push({ i,j });
		}
	}
}

void solve() {
	input();
	int a, b, x, y, i, ans = 0;
	while (!q.empty()) {
		a = q.front().x;
		b = q.front().y;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < h && 0 <= y && y < w) {
				if (visited[x][y] || g[x][y] != '.') continue;
				ans++;
				visited[x][y] = 1;
				q.push({ x,y });
			}
		}
	}
	cout << ans + 1 << ".00\n";
	memset(visited, 0, sizeof(visited));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
