#include<iostream>
#include<vector>
#define ll long long
#define MOD 1000000007
using namespace std;

struct info {
	int x;
	ll dis;
};

int n; ll ans = 0;
vector<bool> visited;
vector<ll> dp[2];
vector<vector<info>> g;

void dfs(int node) {
	visited[node] = 1;
	for (auto& iter : g[node]) {
		if (visited[iter.x]) continue;
		dfs(iter.x);
		dp[1][node] += iter.dis * (1 + dp[1][iter.x]);
		dp[0][node] += dp[0][iter.x] + dp[1][iter.x];
		dp[0][node] %= MOD;
	}
	ll temp = dp[1][node];
	for (auto& iter : g[node]) {
		if (visited[iter.x]) continue;
		temp = (temp - (iter.dis * (1 + dp[1][iter.x])) % MOD + MOD) % MOD;
		ans += iter.dis * (1 + dp[1][iter.x]) % MOD * temp;
		ans %= MOD;
	}
	dp[1][node] %= MOD;
	visited[node] = 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n;
	ll c;
	g = vector<vector<info>>(n + 1);
	visited = vector<bool>(n + 1);
	dp[0] = vector<ll>(n + 1);
	dp[1] = vector<ll>(n + 1);
	for (i = 1; i < n; i++) {
		cin >> a >> b >> c;
		g[a].push_back({ b,c });
		g[b].push_back({ a,c });
	}
	dfs(1);
	cout << (dp[0][1] + dp[1][1] + ans) % MOD;
}
