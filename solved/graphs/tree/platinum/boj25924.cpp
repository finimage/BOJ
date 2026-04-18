#include<bits/stdc++.h>
using namespace std;

vector<int> ans, dis;
vector<vector<int>> g;
int n, k, point[2], comp;
bool visited[500001], path[500001];

void dfs(int ind, int cnt, int check) {
	dis[ind] = cnt;
	if (comp < cnt) {
		comp = cnt;
		point[check] = ind;
	}
	visited[ind] = 1;
	for (auto& iter : g[ind]) {
		if (visited[iter]) continue;
		dfs(iter, cnt + 1, check);
	}
	visited[ind] = 0;
}

void find_path(int ind, int end) {
	if (ind == end) {
		path[ind] = 1;
		return;
	}
	visited[ind] = 1;
	for (auto& iter : g[ind]) {
		if (visited[iter]) continue;
		find_path(iter, end);
		if (path[iter]) path[ind] = 1;
	}
	visited[ind] = 0;
}

void ans1(int ind, int cnt) {
	cout << ind << '\n';
	if (cnt == 0) return;
	visited[ind] = 1;
	for (auto& iter : g[ind]) {
		if (visited[iter]) continue;
		if (path[iter]) ans1(iter, cnt - 1);
	}
	visited[ind] = 0;
}

void ans2(int ind) {
	ans.emplace_back(ind);
	if (!path[ind]) comp--;
	int next = -1;
	visited[ind] = 1;
	for (auto& iter : g[ind]) {
		if (visited[iter]) continue;
		if (!path[iter] && comp) {
			ans2(iter);
			ans.emplace_back(ind);
		}
		if (path[iter]) next = iter;
	}
	if (next != -1) ans2(next);
	visited[ind] = 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int i, a, b; cin >> n >> k;
	g.resize(n + 1);
	dis.resize(n + 1);
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	dfs(1, 0, 0);
	comp = 0;
	dfs(point[0], 0, 1);
	find_path(point[0], point[1]);
	if (k <= dis[point[1]]) {
		cout << k + 1 << '\n' << k << '\n';
		ans1(point[0], k);
	}
	else {
		comp = (k - dis[point[1]]) / 2;
		ans2(point[0]);
		int l = ans.size();
		cout << dis[point[1]] + 1 + (l - dis[point[1]] - 1) / 2 << '\n' << l - 1 << '\n';
		for (auto& iter : ans) cout << iter << '\n';
	}
}
