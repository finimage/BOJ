#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int n, m, num[40001], low[40001], cnt, cnt_, check[40001];
vector<int> graph[40001];
bool visited[40001];
stack<int> st;

void init() {
	int i;
	for (i = 1; i <= m; i++) {
		graph[i].clear();
		graph[i + 20000].clear();
		num[i] = low[i] = check[i] = 0;
		num[i + 20000] = low[i + 20000] = check[i + 20000] = 0;
	}
	cnt = cnt_ = 0;
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

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, tf;
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		for (i = 0; i < n; i++) {
			cin >> a >> b;
			graph[(a > 0) ? (a + 20000) : -a].push_back((b > 0) ? b : -b + 20000);
			graph[(b > 0) ? (b + 20000) : -b].push_back((a > 0) ? a : -a + 20000);
		}
		for (i = 1; i <= m; i++) {
			if (!num[i]) scc(i);
		}
		for (i = 20001; i <= m + 20000; i++) {
			if (!num[i]) scc(i);
		}
		tf = 0;
		for (i = 1; i <= m; i++) {
			if (check[i] == check[i + 20000]) {
				tf = 1;
				break;
			}
		}
		if (tf) cout << "0\n";
		else cout << "1\n";
		init();
	}
}
