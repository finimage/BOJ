#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, cap[103][103], flow[103][103], pre[103];
vector<int> g[103];
queue<int> q;

int max_flow() {
	for (int i = 1; i <= 102; i++) pre[i] = 0;
	q = queue<int>();
	q.push(101);
	int a, res = 10000, tf = 1;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		if (a == 102) {
			tf = 0;
			break;
		}
		for (auto& iter : g[a]) {
			if (!pre[iter] && cap[a][iter] > flow[a][iter]) {
				pre[iter] = a;
				q.push(iter);
			}
		}
	}
	if (tf) return 0;
	a = 102;
	while (pre[a]) {
		res = min(res, cap[pre[a]][a] - flow[pre[a]][a]);
		a = pre[a];
	}
	a = 102;
	while (pre[a]) {
		flow[pre[a]][a] += res;
		flow[a][pre[a]] -= res;
		a = pre[a];
	}
	return 1;
}

bool check(int k) {
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 51; j <= n + 50; j++) {
			cap[i][j] = k;
			flow[i][j] = flow[j][i] = 0;
		}
		flow[101][i] = flow[i + 50][102] = 0;
	}
	while (1) {
		if (!max_flow()) break;
	}
	for (i = 1; i <= n; i++) {
		if (flow[101][i] != cap[101][i]) return 0;
		if (flow[i + 50][102] != cap[i + 50][102]) return 0;
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, le = 0, ri = 10000, mid, ans = 0; cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> cap[101][i];
		g[101].push_back(i);
	}
	for (i = 51; i <= n + 50; i++) {
		cin >> cap[i][102];
		g[i].push_back(102);
	}
	for (i = 1; i <= n; i++) {
		for (j = 51; j <= n + 50; j++) {
			g[i].push_back(j);
			g[j].push_back(i);
		}
	}
	while (le < ri) {
		mid = (le + ri) / 2;
		if (check(mid)) {
			ans = mid;
			ri = mid;
		}
		else le = mid + 1;
	}
	cout << ans << '\n';
	check(ans);
	for (i = 1; i <= n; i++) {
		for (j = 51; j <= n + 50; j++) cout << flow[i][j] << ' ';
		cout << '\n';
	}
}
