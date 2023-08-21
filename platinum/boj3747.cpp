#include<iostream>
#include<stack>
#include<vector>
using namespace std;

int n, m, num[2001], low[2001], cnt, cnt_, check[2001];
vector<int> graph[2001];
bool visited[2001];
stack<int> st;

void init() {
	int i;
	for (i = 1; i <= n; i++) {
		graph[i].clear();
		graph[i + 1000].clear();
		num[i] = low[i] = check[i] = 0;
		num[i + 1000] = low[i + 1000] = check[i + 1000] = 0;
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
	char c1, c2;
	while (cin >> n >> m) {
		for (i = 0; i < m; i++) {
			cin >> c1 >> a >> c2 >> b;
			if (c1 == '+') {
				if (c2 == '+') {
					graph[a + 1000].push_back(b);
					graph[b + 1000].push_back(a);
				}
				else {
					graph[a + 1000].push_back(b + 1000);
					graph[b].push_back(a);
				}
			}
			else {
				if (c2 == '+') {
					graph[a].push_back(b);
					graph[b + 1000].push_back(a + 1000);
				}
				else {
					graph[a].push_back(b + 1000);
					graph[b].push_back(a + 1000);
				}
			}
		}
		for (i = 1; i <= n; i++) {
			if (!num[i]) scc(i);
		}
		for (i = 1001; i <= n + 1000; i++) {
			if (!num[i]) scc(i);
		}
		tf = 0;
		for (i = 1; i <= n; i++) {
			if (check[i] == check[i + 1000]) {
				tf = 1;
				break;
			}
		}
		if (tf) cout << "0\n";
		else cout << "1\n";
		init();
	}
}
