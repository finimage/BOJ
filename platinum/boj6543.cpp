#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int n, m, num[5001], low[5001], cnt, cnt_, check[5001], outdegree[5001];
vector<int> graph[5001], ans;
stack<int> st;
bool visited[5001];

void init() {
	for (int i = 1; i <= n; i++) {
		num[i] = low[i] = check[i] = outdegree[i] = 0;
		graph[i].clear();
	}
	cnt = cnt_ = 0;
	ans.clear();
}

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	st.push(ind);
	visited[ind] = 1;
	for (auto& iter : graph[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if(visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			visited[k] = 0;
			check[k] = cnt_;
			if (ind == k) break;
		}
	}
}

void checking() {
	for (int i = 1; i <= n; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			outdegree[check[i]]++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b;
	while (1) {
		cin >> n;
		if (n == 0) break;
		cin >> m;
		for (i = 0; i < m; i++) {
			cin >> a >> b;
			graph[a].push_back(b);
		}
		for (i = 1; i <= n; i++) {
			if (!num[i]) scc(i);
		}
		checking();
		for (i = 1; i <= n; i++) {
			if (!outdegree[check[i]]) ans.push_back(i);
		}
		for (auto& iter : ans) cout << iter << ' ';
		cout << '\n';
		init();
	}
}
