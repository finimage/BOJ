#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int x, y, dis;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.dis > b.dis;
	}
};

struct co {
	int x, y;
};

int n, m, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
int graph[51][51], check[251];
int visited[51][51];
vector<co> v;
queue<info> q;
priority_queue<info, vector<info>, cmp> pq;

int bfs(int ind, int check) {
	co st = v[ind];
	q.push({ st.x,st.y,0 });
	visited[st.x][st.y] = check;
	int a, b, x, y, dis, i, cnt = 1;
	while (!q.empty()) {
		a = q.front().x;
		b = q.front().y;
		dis = q.front().dis;
		q.pop();
		for (i = 0; i < 4; i++) {
			x = a + dx[i];
			y = b + dy[i];
			if (0 <= x && x < n && 0 <= y && y < n) {
				if (visited[x][y] == check || graph[x][y] == -1) continue;
				visited[x][y] = check;
				q.push({ x,y,dis + 1 });
				if (graph[x][y] > 0) {
					cnt++;
					pq.push({ ind + 1, graph[x][y], dis + 1 });
				}
			}
		}
	}
	graph[st.x][st.y] = 0;
	return cnt;
}

int find_(int a) {
	if (a == check[a]) return a;
	return check[a] = find_(check[a]);
}

bool union_(int a, int b) {
	a = find_(a);
	b = find_(b);
	if (a == b) return 1;
	check[a] = b;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, cnt = 1, total = 0, x, y, dis; cin >> n >> m;
	char temp;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cin >> temp;
			if (temp == 'S' || temp == 'K') {
				graph[i][j] = cnt++;
				v.push_back({ i,j });
			}
			else if (temp == '1') graph[i][j] = -1;
			else if (temp == '0') graph[i][j] = 0;
		}
	}
	for (i = 0; i < m; i++) {
		check[i + 1] = i + 1;
		if (m - i + 1 != bfs(i, (i + 1) % 2)) {
			cout << -1;
			return 0;
		}
	}
	while (!pq.empty()) {
		x = pq.top().x;
		y = pq.top().y;
		dis = pq.top().dis;
		pq.pop();
		if (union_(x, y)) continue;
		total += dis;
	}
	cout << total;
}
