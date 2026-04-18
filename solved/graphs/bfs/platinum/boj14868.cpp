#include<iostream>
#include<queue>
using namespace std;

struct info {
	int x, y, num;
};

int n, k, check[2001][2001], parent[2000001], cnt, time_, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
bool visited[2001][2001];
queue<info> q[2];
queue<pair<int, int>> Q_;

void bfs_(int a, int b) {
	int x, y, i;
	cnt++;
	queue<pair<int, int>> q_;
	visited[a][b] = 0;
	check[a][b] = cnt;
	parent[cnt] = cnt;
	q_.push({ a,b });
	q[0].push({ a,b,cnt });
	while (!q_.empty()) {
		a = q_.front().first;
		b = q_.front().second;
		q_.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 < x && x <= n && 0 < y && y <= n) {
				if (!visited[x][y]) continue;
				visited[x][y] = 0;
				check[x][y] = cnt;
				q_.push({ x,y });
				q[0].push({ x,y,cnt });
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

void checking(int a, int b) {
	int x, y, i;
	for (i = 0; i < 4; i++) {
		x = a + dx[i];
		y = b + dy[i];
		if (0 < x && x <= n && 0 < y && y <= n) {
			if (!check[x][y]) continue;
			if (union_(check[x][y], check[a][b])) continue;
			cnt--;
		}
	}
}

void bfs(int t1, int t2) {
	int a, b, num, x, y, i;
	while (!q[t1].empty()) {
		a = q[t1].front().x;
		b = q[t1].front().y;
		num = q[t1].front().num;
		q[t1].pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 < x && x <= n && 0 < y && y <= n) {
				if (check[x][y]) continue;
				check[x][y] = num;
				q[t2].push({ x,y,num });
				checking(x, y);
			}
		}
	}
	time_++;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n >> k;
	for (i = 0; i < k; i++) {
		cin >> a >> b;
		visited[a][b] = 1;
		Q_.push({ a,b });
	}
	while (!Q_.empty()) {
		a = Q_.front().first;
		b = Q_.front().second;
		Q_.pop();
		if (!visited[a][b]) continue;
		bfs_(a, b);
	}
	while (cnt != 1) bfs(time_ % 2, (time_ + 1) % 2);
	cout << time_;
}
