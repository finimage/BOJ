#include<iostream>
#define INF 16000001
using namespace std;

int n, w[16][16], dp[16][1 << 16], cmp;

int dfs(int node, int visit) {
	if (visit == cmp) return (w[node][0] ? w[node][0] : INF);
	if (dp[node][visit] != -1) return dp[node][visit];
	dp[node][visit] = INF;
	for (int i = 0; i < n; i++) {
		if ((1 << i) & visit) continue;
		if (!w[node][i]) continue;
		dp[node][visit] = min(dp[node][visit], dfs(i, visit | (1 << i)) + w[node][i]);
	}
	return dp[node][visit];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) cin >> w[i][j];
	}
	cmp = (1 << n) - 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j <= cmp; j++) dp[i][j] = -1;
	}
	cout << dfs(0, 1);
}
