#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
#define x first
#define y second
using namespace std;

int r, s, cnt, cnt_, tab[101][101], dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
char table[101][101];
vector<vector<int>> tower;
vector<vector<pair<int, int>>> clone;
vector<int> check, num, low;
stack<int> st;
vector<bool> visited;
unordered_map<int, pair<int, int>> um;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
	for (auto& iter : tower[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if(visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			check[k] = cnt_;
			visited[k] = 0;
			if (k == ind) break;
		}
	}
}

void add_edge(int dir, int k) {
	if (dir == 0) tower[4 * k - 2].push_back(4 * k - 3);
	if (dir == 1) tower[4 * k].push_back(4 * k - 1);
	if (dir == 2) tower[4 * k - 1].push_back(4 * k);
	if (dir == 3) tower[4 * k - 3].push_back(4 * k - 2);
}

void checking(int a, int b) {
	int i, x, y;
	for (i = 0; i < 4; i++) {
		x = a + dx[i];
		y = b + dy[i];
		while (0 <= x && x < r && 0 <= y && y < s) {
			if (table[x][y] == 'T') {
				add_edge(i, tab[a][b]);
				break;
			}
			if (table[x][y] == 'n') clone[tab[x][y]].push_back({ tab[a][b],i });
			if (table[x][y] == '#') break;
			x += dx[i];
			y += dy[i];
		}
	}
}

void checking_(int k) {
	if (clone[k].size() == 1) {
		int t = clone[k][0].y;
		if (t == 0) t = 3;
		else if (t == 1) t = 2;
		else if (t == 2) t = 1;
		else if (t == 3) t = 0;
		add_edge(t, clone[k][0].x);
	}
	else {
		int t1 = clone[k][0].y, t2 = clone[k][1].y, t3, t4;
		if (t1 == 0) t1 = 2;
		else if (t1 == 1) t1 = 0;
		else if (t1 == 2) t1 = 1;
		else if (t1 == 3) t1 = 3;
		if (t1 == 0) t3 = 1;
		else if (t1 == 1) t3 = 0;
		else if (t1 == 2) t3 = 3;
		else if (t1 == 3) t3 = 2;
		if (t2 == 0) t2 = 2;
		else if (t2 == 1) t2 = 0;
		else if (t2 == 2) t2 = 1;
		else if (t2 == 3) t2 = 3;
		if (t2 == 0) t4 = 1;
		else if (t2 == 1) t4 = 0;
		else if (t2 == 2) t4 = 3;
		else if (t2 == 3) t4 = 2;
		tower[4 * clone[k][0].x - t3].push_back(4 * clone[k][1].x - t2);
		tower[4 * clone[k][1].x - t4].push_back(4 * clone[k][0].x - t1);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, n = 0, m = 0; cin >> r >> s;
	for (i = 0; i < r; i++) {
		for (j = 0; j < s; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'T') {
				n++;
				tab[i][j] = n;
				um[n] = { i,j };
			}
			if (table[i][j] == 'n') {
				m++;
				tab[i][j] = m;
			}
		}
	}
	tower = vector<vector<int>>(4 * n + 1);
	clone = vector<vector<pair<int, int>>>(m + 1);
	check = vector<int>(4 * n + 1, 0);
	num = vector<int>(4 * n + 1, 0);
	low = vector<int>(4 * n + 1, 0);
	visited = vector<bool>(4 * n + 1, 0);
	for (i = 1; i <= n; i++) checking(um[i].x, um[i].y);
	for (i = 1; i <= m; i++) checking_(i);
	for (i = 1; i <= 4 * n; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 0; i < r; i++) {
		for (j = 0; j < s; j++) {
			if (table[i][j] == 'T') {
				int k = tab[i][j], dir[2] = { 0, };
				if (check[4 * k - 3] < check[4 * k - 2]) dir[0] = 1;
				else dir[0] = 0;
				if (check[4 * k - 1] < check[4 * k]) dir[1] = 1;
				else dir[1] = 0;
				if (dir[0] && dir[1]) cout << 4;
				if (!dir[0] && dir[1]) cout << 1;
				if (dir[0] && !dir[1]) cout << 3;
				if (!dir[0] && !dir[1]) cout << 2;
			}
			else cout << table[i][j];
		}
		cout << '\n';
	}
}
