#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, t, check[100001], cnt[100001];
vector<int> graph[100001], ans;

void input() {
	int i, a, b; cin >> n >> m >> t;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[b].push_back(a);
	}
}

void dfs(int node, int chk) {
	cnt[node]++;
	for (auto& iter : graph[node]) {
		if (cnt[iter] > 1 || check[iter] == chk) continue;
		check[iter] = chk;
		dfs(iter, chk);
	}
}

void DFS() {
	for (auto& iter : graph[t]) {
		check[t] = iter;
		check[iter] = iter;
		dfs(iter, iter);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	DFS();
	for (auto& iter : graph[t]) {
		if (cnt[iter] < 2) ans.push_back(iter);
	}
	cout << ans.size() << '\n';
	sort(ans.begin(), ans.end());
	for (auto& iter : ans) cout << iter << '\n';
}
