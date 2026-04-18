#include<iostream>
#include<vector>
#define INF 10000001
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, m, pre[16], dp[16][1 << 16], cmp, Min[16];
vector<pii> g[16];

int dfs(int node, int visit) {
	if (visit == cmp) return Min[node];
	if (dp[node][visit] != -1) return dp[node][visit];
	dp[node][visit] = INF;
	for (auto& iter : g[node]) {
		if ((1 << iter.x) & visit) continue;
		if (pre[iter.x] != 0) {
			if (((1 << pre[iter.x]) & visit)) dp[node][visit] = min(dp[node][visit], dfs(iter.x, visit | (1 << iter.x)) + iter.y);
		}
		else dp[node][visit] = min(dp[node][visit], dfs(iter.x, visit | (1 << iter.x)) + iter.y);
	}
	return dp[node][visit];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, a, b, c; cin >> n >> m;
	for (i = 1; i <= n; i++) {
		cin >> pre[i];
		if (pre[i] == i) pre[i] = 0;
		Min[i] = INF;
	}
	for (i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[a].push_back({ b,c });
		if (b == n + 1) Min[a] = min(Min[a], c);
	}
	cmp = (1 << (n + 2)) - 2;
	int k = (1 << 16);
	for (i = 1; i <= n + 1; i++) {
		for (j = 0; j < k; j++) dp[i][j] = -1;
	}
	k = dfs(n + 1, (1 << (n + 1)));
	if (k >= INF) cout << -1;
	else cout << k;
}
