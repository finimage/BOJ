#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

char map_[53][53] = { 0, };
bool visited[53][53] = { 0, };
int n, m, cnt = 0, group[53][53] = { 0, }, dx[8] = { 1,0,0,-1,-1,-1,1,1 }, dy[8] = { 0,1,-1,0,1,-1,1,-1 }, land[625] = { 0, }, ans[20] = { 0, };
vector<int> v[625];

void i_bfs(int a, int b) {
	int x, y, i;
	cnt++;
	queue<pair<int, int>> q;
	q.push({ a,b });
	visited[a][b] = true;
	group[a][b] = cnt;
	while (!(q.empty())) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 8; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 < x && x <= n && 0 < y && y <= m) {
				if (visited[x][y]) continue;
				if (map_[x][y] == 'x') {
					q.push({ x,y });
					visited[x][y] = true;
					group[x][y] = cnt;
				}
			}
		}
	}
}

void w_bfs(int a, int b) {
	int x, y, i;
	queue<pair<int, int>> q;
	q.push({ a,b });
	visited[a][b] = true;
	while (!(q.empty())) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x <= n + 1 && 0 <= y && y <= m + 1) {
				if (visited[x][y]) continue;
				if (map_[x][y] == '.') {
					q.push({ x,y });
					visited[x][y] = true;
				}
				else if (map_[x][y] == 'x') {
					i_bfs(x, y);
					v[0].push_back(cnt);
				}
			}
		}
	}
}

void w_bfs2(int a, int b) {
	int x, y, i, l, tf = 0;
	queue<pair<int, int>> q;
	vector<int> temp;
	q.push({ a,b });
	visited[a][b] = true;
	while (!(q.empty())) {
		a = q.front().first;
		b = q.front().second;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x <= n + 1 && 0 <= y && y <= m + 1) {
				if (visited[x][y]) {
					if (tf) continue;
					if (map_[x][y] == 'x') {
						temp.push_back(group[x][y]);
						tf = 1;
					}
					continue;
				}
				if (map_[x][y] == '.') {
					q.push({ x,y });
					visited[x][y] = true;
				}
				else if (map_[x][y] == 'x') {
					i_bfs(x, y);
					temp.push_back(cnt);
				}
			}
		}
	}
	sort(temp.begin(), temp.end());
	l = temp.size();
	for (i = 1; i < l; i++) {
		v[temp[0]].push_back(temp[i]);
	}
}

void dfs(int k) {
	int i, l = v[k].size(), t = 0;
	for (i = 0; i < l; i++) {
		dfs(v[k][i]);
		t = max(t, land[v[k][i]]);
	}
	land[k] = t + 1;
	ans[land[k]]++;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, tf = 1, l;
	cin >> n >> m;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> map_[i][j];
			if (map_[i][j] == 'x') tf = 0;
		}
	}
	if (tf) {
		cout << -1;
		return 0;
	}
	for (i = 0; i <= m + 1; i++) {
		map_[0][i] = '.';
		map_[n + 1][i] = '.';
	}
	for (i = 0; i <= n + 1; i++) {
		map_[i][0] = '.';
		map_[i][m + 1] = '.';
	}
	w_bfs(0, 0);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (map_[i][j] == '.' && visited[i][j] == 0) w_bfs2(i, j);
		}
	}
	l = v[0].size();
	for (i = 0; i < l; i++) dfs(v[0][i]);
	for (i = 1; i < 20; i++) {
		if (ans[i] == 0) break;
		cout << ans[i] << ' ';
	}
}
