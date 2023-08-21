#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int n, m, num[1000001], low[1000001], cnt, cnt_, check[1000001], pre[1000001];
stack<int> st;
vector<int> graph[1000001], new_graph[1000001];
bool visited[1000001];

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
			new_graph[cnt_].push_back(k);
			if (ind == k) break;
		}
	}
}

void checking() {
	for (int i = 1; i <= n; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			pre[check[iter]]++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, count = 0, ans = 0; cin >> n >> m;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	checking();
	for (i = 1; i <= cnt_; i++) {
		if (pre[i] == 0) {
			count++;
			ans = i;
		}
	}
	if (count == 1) {
		sort(new_graph[ans].begin(), new_graph[ans].end());
		cout << new_graph[ans].size() << '\n';
		for (auto& iter : new_graph[ans]) cout << iter << ' ';
	}
	else cout << 0 << '\n';
}
