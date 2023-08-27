#include<iostream>
#include<queue>
using namespace std;

struct info {
	int x, y, num;
};

char arr[2001][2001];
int n, m, check[2001][2001], parent[2000001], dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
int cnt, fire_cnt, time_, ans_time, ans_fire;
bool visited[2001][2001];
queue<info> q[2];

void bfs_(int x, int y) {
	queue<pair<int, int>> Q;
	cnt++;
	fire_cnt++;
	visited[x][y] = 1;
	check[x][y] = cnt;
    parent[cnt] = cnt;
	Q.push({ x,y });
	q[0].push({ x,y,cnt });
	int a, b, i;
	while (!Q.empty()) {
		a = Q.front().first;
		b = Q.front().second;
		Q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (visited[x][y]) continue;
				visited[x][y] = 1;
				if (arr[x][y] == '0') {
					fire_cnt++;
					check[x][y] = cnt;
					Q.push({ x, y });
					q[0].push({ x,y,cnt });
				}
			}
		}
	}
}

int find_(int a) {
	if (a == parent[a]) return a;
	return parent[a] = find_(parent[a]);
}

bool union_(int a, int b) {
	a = find_(a);
	b = find_(b);
	if (a == b) return 1;
	parent[a] = b;
	return 0;
}

bool checking(int a, int b) {
	int x, y, i, res = 0;
	for (i = 0; i < 4; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (0 <= x && x < n && 0 <= y && y < m) {
			if (arr[x][y] != '0') continue;
			if (union_(check[x][y], check[a][b])) continue;
			res = 1;
			cnt--;
		}
	}
	return res;
}

void bfs(int t1, int t2) {
	int a, b, num, x, y, i, tf = 0;
	while (!q[t1].empty()) {
		a = q[t1].front().x;
		b = q[t1].front().y;
		num = q[t1].front().num;
		q[t1].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < m) {
				if (arr[x][y] == '1') {
					fire_cnt++;
					arr[x][y] = '0';
					check[x][y] = num;
					q[t2].push({ x,y,num });
					if (checking(x, y)) tf = 1;
				}
			}
		}
	}
	time_++;
	if (tf) {
		ans_time = time_;
		ans_fire = fire_cnt;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n >> m;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) cin >> arr[i][j];
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (visited[i][j]) continue;
			if (arr[i][j] == '0') bfs_(i, j);
		}
	}
	if (cnt == 0) {
		cout << "0 0";
		return 0;
	}
	if (cnt == 1) {
		cout << "0 " << fire_cnt;
		return 0;
	}
	ans_fire = fire_cnt;
	while (cnt != 1) {
		bfs(time_ % 2, (time_ + 1) % 2);
		if (q[time_ % 2].empty()) break;
	}
	cout << ans_time << ' ' << ans_fire;
}
