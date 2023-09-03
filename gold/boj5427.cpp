#include<iostream>
#include<queue>
#define x first
#define y second
using namespace std;

int w, h, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 }, check;
char arr[1001][1001];
bool visited[1001][1001];
queue<pair<int, int>> fire[2], q[2];

void fire_bfs(int t1, int t2) {
	int a, b, x, y, i;
	while (!fire[t1].empty()) {
		a = fire[t1].front().x;
		b = fire[t1].front().y;
		fire[t1].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < h && 0 <= y && y < w) {
				if (visited[x][y] || arr[x][y] == '#') continue;
				visited[x][y] = 1;
				arr[x][y] = '*';
				fire[t2].push({ x,y });
			}
		}
	}
}

void bfs(int t1, int t2) {
	int a, b, x, y, i;
	while (!q[t1].empty()) {
		a = q[t1].front().x;
		b = q[t1].front().y;
		q[t1].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < h && 0 <= y && y < w) {
				if (visited[x][y] || arr[x][y] == '#' || arr[x][y] == '*') continue;
				visited[x][y] = 1;
				q[t2].push({ x,y });
			}
			else check = 2;
		}
	}
}

void init() {
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) visited[i][j] = arr[i][j] = 0;
	}
	q[0] = queue<pair<int, int>>();
	q[1] = queue<pair<int, int>>();
	fire[0] = queue<pair<int, int>>();
	fire[1] = queue<pair<int, int>>();
}

void solve() {
	int i, j, time = 0; cin >> w >> h;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == '*') {
				visited[i][j] = 1;
				fire[0].push({i,j});
			}
			if (arr[i][j] == '@') {
				arr[i][j] = '*';
				visited[i][j] = 1;
				q[0].push({ i,j });
			}
		}
	}
	check = 0;
	while (1) {
		fire_bfs(time % 2, (time + 1) % 2);
		bfs(time % 2, (time + 1) % 2);
		time++;
		if (check == 2 || q[time % 2].empty()) break;
	}
	if (check == 2) cout << time << '\n';
	else cout << "IMPOSSIBLE\n";
	init();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
