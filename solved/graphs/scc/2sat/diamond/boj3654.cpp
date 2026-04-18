#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int n, m, tab[502][502], cnt, cnt_, dx[4] = { 1,0,0,-1 }, dy[4] = { 0,1,-1,0 };
char table[501][501];
vector<vector<int>> g;
vector<int> num, low, check;
vector<bool> visited;
stack<int> st;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
	for (auto& iter : g[ind]) {
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

void init() {
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (tab[i][j]) {
				g[tab[i][j]].clear();
				tab[i][j] = 0;
			}
			table[i][j] = 0;
		}
	}
	cnt = cnt_ = 0;
	num.clear();
	low.clear();
	check.clear();
	visited.clear();
}

void solve() {
	int i, j, cntb = 0, cntw = 0; cin >> n >> m;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'B') {
				cntb++;
				tab[i][j] = cntb;
			}
			if (table[i][j] == 'W') cntw++;
		}
	}
	g = vector<vector<int>>(4 * cntb + 1);
	num = vector<int>(4 * cntb + 1);
	low = vector<int>(4 * cntb + 1);
	check = vector<int>(4 * cntb + 1);
	visited = vector<bool>(4 * cntb + 1);
	if (cntb * 2 != cntw) {
		init();
		cout << "NO\n";
		return;
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (table[i][j] == 'B') {
				int chk[4] = { 0, }, x, y;
				for (int t = 0; t < 4; t++) {
					x = i + dx[t];
					y = j + dy[t];
					if (table[x][y] == 'W') chk[t] = 1;
				}
				if ((!chk[0] && !chk[3]) || (!chk[1] && !chk[2])) {
					init();
					cout << "NO\n";
					return;
				}
				if (chk[0] && !chk[3]) g[tab[i][j] * 4 - 3].push_back(tab[i][j] * 4);
				if (!chk[0] && chk[3]) g[tab[i][j] * 4].push_back(tab[i][j] * 4 - 3);
				if (chk[1] && !chk[2]) g[tab[i][j] * 4 - 2].push_back(tab[i][j] * 4 - 1);
				if (!chk[1] && chk[2]) g[tab[i][j] * 4 - 1].push_back(tab[i][j] * 4 - 2);
			}
			if (table[i][j] == 'W') {
				int chk[4] = { 0, }, x, y;
				for (int t = 0; t < 4; t++) {
					x = i + dx[t];
					y = j + dy[t];
					if (table[x][y] == 'B') chk[t] = 1;
				}
				if (chk[0] + chk[1] + chk[2] + chk[3] == 0) {
					init();
					cout << "NO\n";
					return;
				}
				//0,4n : 하 / 1,4n-1 : 우 / 2,4n-2 : 좌 / 3,4n-3 : 상
				else if (chk[0] + chk[1] + chk[2] + chk[3] == 1) {
					if (chk[0]) g[tab[i + dx[0]][j + dy[0]] * 4].push_back(tab[i + dx[0]][j + dy[0]] * 4 - 3);
					if (chk[1]) g[tab[i + dx[1]][j + dy[1]] * 4 - 1].push_back(tab[i + dx[1]][j + dy[1]] * 4 - 2);
					if (chk[2]) g[tab[i + dx[2]][j + dy[2]] * 4 - 2].push_back(tab[i + dx[2]][j + dy[2]] * 4 - 1);
					if (chk[3]) g[tab[i + dx[3]][j + dy[3]] * 4 - 3].push_back(tab[i + dx[3]][j + dy[3]] * 4);
				}
				else {
					for (int t1 = 0; t1 < 4; t1++) {
						if (!chk[t1]) continue;
						int t3;
						if (t1 == 0) t3 = 3;
						if (t1 == 1) t3 = 2;
						if (t1 == 2) t3 = 1;
						if (t1 == 3) t3 = 0;
						for (int t2 = 0; t2 < 4; t2++) {
							if (t1 == t2) continue;
							if (!chk[t2]) continue;
							g[tab[i + dx[t1]][j + dy[t1]] * 4 - t3].push_back(tab[i + dx[t2]][j + dy[t2]] * 4 - t2);
						}
					}
				}
			}
		}
	}
	for (i = 1; i <= 4 * cntb; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= cntb; i++) {
		if (check[i * 4 - 3] == check[i * 4] || check[i * 4 - 2] == check[i * 4 - 1]) {
			init();
			cout << "NO\n";
			return;
		}
	}
	init();
	cout << "YES\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
