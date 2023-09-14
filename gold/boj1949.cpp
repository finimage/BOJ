#include<iostream>
#include<vector>
using namespace std;

int n, p[10001], dp[2][10001];
bool visited[10001];
vector<vector<int>> graph;

void dfs(int node) {
	visited[node] = 1;
	dp[0][node] += p[node];
	for (auto& iter : graph[node]) {
		if (visited[iter]) continue;
		dfs(iter);
		dp[0][node] += dp[1][iter];
		dp[1][node] += max(dp[0][iter], dp[1][iter]);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n;
	graph = vector<vector<int>>(n + 1);
	for (i = 1; i <= n; i++) cin >> p[i];
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1);
	cout << max(dp[0][1], dp[1][1]);
}
