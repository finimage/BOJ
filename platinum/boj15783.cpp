#include<iostream>
#include<stack>
#include<vector>
using namespace std;

stack<int> st;
vector<int> graph[100001];
int n, m, num[100001], low[100001], cnt, cnt_, check[100001], pre[100001];
bool visited[100001];

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
			pre[check[iter]]++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, ans = 0; cin >> n >> m;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a + 1].push_back(b + 1);
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	checking();
	for (i = 1; i <= cnt_; i++) {
		if (!pre[i]) ans++;
	}
	cout << ans;
}
