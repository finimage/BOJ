#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int x, y;
};

int R, C, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
char cave[101][101];
bool visited[101][101];

bool breaking(int dir, int h) {
	bool tf = 0;
	if (dir) {
		for (int i = C - 1; i >= 0; i--) {
			if (cave[h][i] == 'x') {
				cave[h][i] = '.';
				tf = 1;
				break;
			}
		}
	}
	else {
		for (int i = 0; i < C; i++) {
			if (cave[h][i] == 'x') {
				cave[h][i] = '.';
				tf = 1;
				break;
			}
		}
	}
	return tf;
}

void change(vector<info> v) {
	int dif = 0, k = 0;
	for (auto& iter : v) {
		cave[iter.x][iter.y] = '.';
	}
	while (1) {
		k++;
		for (auto& iter : v) {
			if (iter.x + k == R || cave[iter.x + k][iter.y] == 'x') {
				dif = k - 1;
				break;
			}
		}
		if (dif) break;
	}
	for (auto& iter : v) cave[iter.x + dif][iter.y] = 'x';
}

bool bfs(int x, int y) {
	queue<info> q;
	vector<info> v;
	q.push({ x,y });
	v.push_back({ x,y });
	int a, b, i, h = x;
	while (!q.empty()) {
		a = q.front().x;
		b = q.front().y;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < R && 0 <= y && y < C) {
				if (visited[x][y]) continue;
				visited[x][y] = 1;
				if (cave[x][y] == 'x') {
					q.push({ x,y });
					v.push_back({ x,y });
					h = max(h, x);
				}
			}
		}
	}
	if (h < R - 1) {
		change(v);
		return 1;
	}
	return 0;
}

void init() {
	int i, j;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) visited[i][j] = 0;
	}
}

void search() {
	int i, j, tf = 0;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) {
			if (visited[i][j]) continue;
			visited[i][j] = 1;
			if (cave[i][j] == 'x') {
				if (bfs(i, j)) {
					tf = 1;
					break;
				}
			}
		}
		if (tf) break;
	}
	init();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, order, cnt; cin >> R >> C;
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) cin >> cave[i][j];
	}
	cin >> cnt;
	for (i = 0; i < cnt; i++) {
		cin >> order;
		if (!breaking(i % 2, R - order)) continue;
		search();
	}
	for (i = 0; i < R; i++) {
		for (j = 0; j < C; j++) cout << cave[i][j];
		cout << '\n';
	}
}
