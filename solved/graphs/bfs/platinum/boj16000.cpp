#include<iostream>
#include<queue>
using namespace std;

int n, m, cnt = 0, cnt_ = 0, dx[8] = { 1,0,0,-1,1,1,-1,-1 }, dy[8] = { 0,1,-1,0,1,-1,1,-1 }, group[2][2001][2001] = { 0, }, check_[2000001] = { 0, };
char arr[2001][2001] = { 0, };
bool visited[2001][2001] = { 0, };

bool check(int x, int y, int k) {
	bool tf = 0;
	//k=5,6,7,8
	switch (k) {
	case 4:
		if (x + 1 < n && y + 1 < m) {
			if (group[1][x + 1][y] != group[1][x][y + 1]) tf = true;
		}
		break;
	case 5:
		if (x + 1 < n && y - 1 >= 0) {
			if (group[1][x + 1][y] != group[1][x][y - 1]) tf = true;
		}
		break;
	case 6:
		if (x - 1 >= 0 && y + 1 < m) {
			if (group[1][x - 1][y] != group[1][x][y + 1]) tf = true;
		}
		break;
	default:
		if (x - 1 >= 0 && y - 1 >= 0) {
			if (group[1][x - 1][y] != group[1][x][y - 1]) tf = true;
		}
		break;
	}
	return tf;
}

void i_bfs(int x, int y) {
	cnt_++;
	int i, a, b;
	queue<pair<int, int>> q;
	q.push({ x,y });
	group[1][x][y] = cnt_;
	visited[x][y] = true;
	while (!(q.empty())) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (visited[x][y]) continue;
				if (arr[x][y] == '#') {
					q.push({ x,y });
					visited[x][y] = true;
					group[1][x][y] = cnt_;
				}
			}
		}
	}
}

void w_bfs(int x, int y) {
	cnt++;
	int i, a, b;
	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;
	group[0][x][y] = cnt;
	while (!(q.empty())) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (visited[x][y]) continue;
				if (arr[x][y] == '.') {
					q.push({ x,y });
					visited[x][y] = true;
					group[0][x][y] = cnt;
				}
			}
		}
		for (i = 4; i < 8; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (visited[x][y]) continue;
				if (arr[x][y] == '.') {
					if (check(a, b, i)) {
						q.push({ x,y });
						visited[x][y] = true;
						group[0][x][y] = cnt;
					}
				}
			}
		}
	}
}

void i_bfs_new(int x, int y, int k) {
	int i, a, b, tf = 0, check = 0;
	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = false;
	while (!(q.empty())) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0<= x && x < n && 0 <= y && y < m) {
				if (!visited[x][y]) continue;
				if (group[1][x][y] == k) {
					q.push({ x,y });
					visited[x][y] = false;
				}
				if (group[0][x][y] == 1) check_[k] = 1;
			}
		}
	}
	if (check_[k] != 1) check_[k] = 2;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j;
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) cin >> arr[i][j];
	}
	for (i = 1; i < n - 1; i++) {
		for (j = 1; j < m - 1; j++) {
			if (visited[i][j]) continue;
			if (arr[i][j] == '#') i_bfs(i, j);
		}
	}
	w_bfs(0, 0);
	for (i = 1; i < n - 1; i++) {
		for (j = 1; j < m - 1; j++) {
			if (visited[i][j]) continue;
			if (arr[i][j] == '.') w_bfs(i, j);
		}
	}
	for (i = 1; i < n - 1; i++) {
		for (j = 1; j < m - 1; j++) {
			if (!visited[i][j]) continue;
			if (arr[i][j] == '#' && check_[group[1][i][j]] == 0) i_bfs_new(i, j, group[1][i][j]);
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (arr[i][j] == '.') cout << '.';
			else {
				if (check_[group[1][i][j]] == 1) cout << 'O';
				else cout << 'X';
			}
		}
		cout << '\n';
	}
}
