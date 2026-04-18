#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

vector<int> g[1001];
int check[1001];
bool visited[1001];

int dfs(int node) {
	for (auto& iter : g[node]) {
		if (visited[iter]) continue;
		visited[iter] = 1;
		if (!check[iter]) return check[iter] = node;
		if (dfs(check[iter])) return check[iter] = node;
	}
	return 0;
}

void solve() {
	int n, m, a, b, i, ans = 0; cin >> n >> m;
	while (m--) {
		cin >> a >> b;
		g[a + 1].push_back(b + 1);
	}
	for (i = 1; i <= n; i++) {
		if (dfs(i)) ans++;
		memset(visited, 0, sizeof(visited));
	}
	cout << ans << '\n';
	for (i = 1; i <= n; i++) {
		g[i].clear();
		check[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
