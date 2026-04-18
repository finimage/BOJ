#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, m, k, cap[2003][2003], flow[2003][2003], ans;
vector<int> g[2003];
queue<int> q;

void bfs(int st) {
	int a, tf = 1;
	q.push(st);
	vector<int> pre = vector<int>(2003);
	pre[st] = -1;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		if (a == 2002) {
			tf = 0;
			break;
		}
		for (auto& iter : g[a]) {
			if (pre[iter]) continue;
			if (flow[a][iter] < cap[a][iter]) {
				pre[iter] = a;
				q.push(iter);
			}
		}
	}
	if (tf) return;
	a = 2002;
	while (pre[a] != -1) {
		flow[pre[a]][a]++;
		flow[a][pre[a]]--;
		a = pre[a];
	}
	ans++;
	q = queue<int>();
}

void Flow() {
	for (int i = 1; i <= n; i++) bfs(i * 2 - 1);
	while (k--) {
		int K = ans;
		bfs(2001);
		if (K == ans) break;
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, cnt; cin >> n >> m >> k;
	for (i = 1; i <= n; i++) {
		cin >> cnt;
		g[2001].push_back(i * 2 - 1);
		g[i * 2 - 1].push_back(2001);
		cap[2001][i * 2 - 1] = k;
		while (cnt--) {
			cin >> a;
			g[i * 2 - 1].push_back(a * 2);
			g[a * 2].push_back(i * 2 - 1);
			cap[i * 2 - 1][a * 2] = 1;
		}
	}
	for (i = 1; i <= m; i++) {
		g[2002].push_back(i * 2);
		g[i * 2].push_back(2002);
		cap[i * 2][2002] = 1;
	}
	Flow();
}
