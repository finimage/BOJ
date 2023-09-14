#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

vector<int> g[201];
bool visited[201];
int arr[201], dp[2][201];
unordered_set<int> us;

void dfs(int node) {
	dp[1][node] += arr[node];
	visited[node] = 1;
	for (auto& iter : g[node]) {
		if (visited[iter]) continue;
		dfs(iter);
		dp[1][node] += dp[0][iter];
		dp[0][node] += max(dp[0][iter], dp[1][iter]);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, j, a; cin >> n >> m;
	for (i = 1; i <= n; i++) cin >> arr[i];
	for (i = 0; i < m; i++) {
		cin >> a;
		us.insert(a);
	}
	for (i = 1; i < n; i++) {
		for (j = i + 1; j <= n; j++) {
			if (us.count(abs(arr[i] - arr[j]))) {
				g[j].push_back(i);
				g[i].push_back(j);
			}
		}
	}
	dfs(1);
	cout << max(dp[0][1], dp[1][1]);
}
