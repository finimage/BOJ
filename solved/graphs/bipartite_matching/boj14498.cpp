#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

struct info {
	int ind, a, b;
};

int n, m, k, check[513];
vector<info> A, B;
vector<int> g[513];
bool visited[513];

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
	int i, a, b, c, ans = 0; cin >> n >> m >> k;
	for (i = 1; i <= k; i++) {
		cin >> a >> b >> c;
		if (c) B.push_back({ i,a,b });
		else A.push_back({ i,a,b });
	}
	for (auto& iter1 : A) {
		for (auto& iter2 : B) {
			if (iter1.a == iter2.a || iter1.b == iter2.b) g[iter1.ind].push_back(iter2.ind);
		}
	}
	for (auto& iter : A) {
		if (dfs(iter.ind)) ans++;
		memset(visited, 0, sizeof(visited));
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T = 1;
	while (T--) solve();
}
