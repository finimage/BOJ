#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> dp[2], arr, ans, check[2];
vector<vector<int>> g;

void dfs(int node) {
	dp[1][node] += arr[node];
	for (auto& iter : g[node]) {
		dfs(iter);
		if (dp[0][iter] < dp[1][iter] && dp[1][iter] > 0) {
			dp[0][node] += dp[1][iter];
			check[0][iter] = 1;
		}
		if (dp[0][iter] >= dp[1][iter] && dp[0][iter] > 0) {
			dp[0][node] += dp[0][iter];
			check[0][iter] = 0;
		}
		if (dp[0][iter] > 0) {
			dp[1][node] += dp[0][iter];
			check[1][iter] = 0;
		}
	}
}

void dfs_(int node, int state) {
	if (state) ans.push_back(node);
	for (auto& iter : g[node]) dfs_(iter, check[state][iter]);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, a; cin >> n;
	arr = vector<int>(n + 1);
	check[0] = vector<int>(n + 1);
	check[1] = vector<int>(n + 1);
	dp[0] = vector<int>(n + 1);
	dp[1] = vector<int>(n + 1);
	g = vector<vector<int>>(n + 1);
	for (i = 1; i <= n; i++) cin >> arr[i];
	for (i = 2; i <= n; i++) {
		cin >> a;
		g[a].push_back(i);
	}
	dfs(1);
	cout << dp[1][1] << ' ' << dp[0][1] << '\n';
	dfs_(1, 1);
	sort(ans.begin(), ans.end());
	for (auto& iter : ans) cout << iter << ' ';
	cout << "-1\n";
	ans.clear();
	dfs_(1, 0);
	sort(ans.begin(), ans.end());
	for (auto& iter : ans) cout << iter << ' ';
	cout << "-1";
}
