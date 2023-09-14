#include<iostream>
#include<vector>
using namespace std;

vector<bool> visited;
vector<int> dp[2], arr;
vector<vector<int>> g;

void dfs(int node, int v) {
	visited[node] = 1;
	dp[0][node] = 0;
	for (auto& iter : g[node]) {
		if (visited[iter]) continue;
		dfs(iter, v);
		dp[0][node] += min(dp[0][iter], dp[1][iter]);
	}
	if (!dp[1][node]) {
		for (auto& iter : g[node]) {
			if (visited[iter]) continue;
			dfs(iter, arr[node]);
			dp[1][node] += min(dp[0][iter], dp[1][iter]);
		}
		dp[1][node] += arr[node];
	}
	dp[0][node] += arr[node] - v;
	visited[node] = 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, start, i, a, b, ans; cin >> n >> start;
	g = vector<vector<int>>(n + 1);
	visited = vector<bool>(n + 1);
	dp[0] = vector<int>(n + 1);
	dp[1] = vector<int>(n + 1);
	arr = vector<int>(n + 1);
	for (i = 1; i <= n; i++) cin >> arr[i];
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	ans = arr[start];
	visited[start] = 1;
	for (auto& iter : g[start]) {
		dfs(iter, arr[start]);
		ans += min(dp[0][iter], dp[1][iter]);
	}
	cout << ans;
}
