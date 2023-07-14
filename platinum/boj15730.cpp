#include<iostream>
using namespace std;

int n, m, min_, ans = 0, arr[2][103][103], dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
bool visited[103][103];

void dfs(int a, int b, int state) {
	int i, x, y;
	for (i = 0; i < 4; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (0 <= x && x <= n + 1 && 0 <= y && y <= m + 1) {
			if (visited[x][y]) continue;
			if (arr[0][x][y] + arr[1][x][y] != state) {
				min_ = min(min_, arr[0][x][y] + arr[1][x][y]);
				continue;
			}
			visited[x][y] = true;
			dfs(x, y, state);
		}
	}
}

void dfs_(int a, int b, int state) {
	int i, x, y;
	visited[a][b] = false;
	for (i = 0; i < 4; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (0 <= x && x <= n + 1 && 0 <= y && y <= m + 1) {
			if (visited[x][y]) dfs_(x, y, state);
		}
	}
	arr[1][a][b] += (min_ > state) ? min_ - state : 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, t;
	cin >> n >> m;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) cin >> arr[0][i][j];
	}
	for (i = 0; i <= n + 1; i++) {
		arr[0][0][i] = -1;
		arr[0][n + 1][i] = -1;
	}
	for (i = 0; i <= m + 1; i++) {
		arr[0][i][0] = -1;
		arr[0][i][m + 1] = -1;
	}
	for (t = 0; t < 10000; t++) {
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= m; j++) {
				if (arr[0][i][j] + arr[1][i][j] != t) continue;
				min_ = 10001;
				dfs(i, j, arr[0][i][j] + arr[1][i][j]);
				dfs_(i, j, arr[0][i][j] + arr[1][i][j]);
			}
		}
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) ans += arr[1][i][j];
	}
	cout << ans;
}
