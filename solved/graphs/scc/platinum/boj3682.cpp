#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int n, m, cnt, cnt_;
vector<int> num, low, visited, check, indegree, outdegree;
stack<int> st;
vector<vector<int>> g;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
	for (auto& iter : g[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if (visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			check[k] = cnt_;
			visited[k] = 0;
			if (k == ind) break;
		}
	}
}

void solve() {
	int i, a, b, s1 = 0, s2 = 0; cin >> n >> m;
	num = vector<int>(n + 1, 0);
	low = vector<int>(n + 1, 0);
	visited = vector<int>(n + 1, 0);
	check = vector<int>(n + 1, 0);
	g = vector<vector<int>>(n + 1, vector<int>(0));
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		g[a].push_back(b);
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	indegree = vector<int >(cnt_ + 1, 0);
	outdegree = vector<int>(cnt_ + 1, 0);
	for (i = 1; i <= n; i++) {
		for (auto& iter : g[i]) {
			if (check[i] != check[iter]) {
				outdegree[check[i]]++;
				indegree[check[iter]]++;
			}
		}
	}
	for (i = 1; i <= cnt_; i++) {
		if (indegree[i] == 0) s1++;
		if (outdegree[i] == 0) s2++;
	}
	if (cnt_ == 1) cout << 0 << '\n';
	else cout << max(s1, s2) << '\n';
	for (i = 1; i <= n; i++) g[i].clear();
	num.clear();
	low.clear();
	visited.clear();
	check.clear();
	indegree.clear();
	outdegree.clear();
	g.clear();
	cnt = cnt_ = 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
