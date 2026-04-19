#include<iostream>
#include<queue>
using namespace std;

int n, m, cheeze[101][101] = { 0, }, dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 }, cheeze_cnt = 0;
bool visited[101][101] = { 0, };
queue<pair<int, int>> q[2];

bool check(int x, int y) {
	int i, cnt = 0, a, b;
	for (i = 0; i < 4; i++) {
		a = x + dx[i];
		b = y + dy[i];
		if (0 <= a && a < n && 0 <= b && b < m) {
			if (visited[a][b] && cheeze[a][b] == 2) cnt++;
		}
	}
	if (cnt >= 2) return true;
	return false;
}

void bfs(int k1, int k2) {
	int i, a, b, x, y;
	while (!(q[k1].empty()) && cheeze_cnt) {
		a = q[k1].front().first;
		b = q[k1].front().second;
		q[k1].pop();
		if (cheeze[a][b] == 0) cheeze[a][b] = 2;
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (!visited[x][y]) {
					if (cheeze[x][y] == 0) {
						q[k1].push({x,y});
						visited[x][y] = true;
						continue;
					}
					if (check(x, y)) {
						q[k2].push({ x,y });
						visited[x][y] = true;
						cheeze[x][y] = 0;
						cheeze_cnt--;
					}
				}
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, time_ = 0, k1, k2;
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> cheeze[i][j];
			if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
				q[0].push({i,j});
				cheeze[i][j] = 2;
				visited[i][j] = true;
			}
			if (cheeze[i][j] == 1) cheeze_cnt++;
		}
	}
	while (cheeze_cnt) {
		k1 = time_ % 2;
		k2 = (time_ + 1) % 2;
		bfs(k1,k2);
		time_++;
	}
	cout << time_;
}
