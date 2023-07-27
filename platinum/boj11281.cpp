#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<unordered_map>
using namespace std;

stack<int> st;
vector<int> graph[20001], new_graph[20001], temp;
vector<vector<int>> v;
int n, m, num[20001], low[20001], check[20001], pre[20001], ans[20001], cnt, cnt_;
bool visited[20001];
queue<int> q;
unordered_map<int, int> um;

void scc(int index) {
	cnt++;
	num[index] = low[index] = cnt;
	visited[index] = 1;
	st.push(index);
	for (auto& iter : graph[index]) {
		if (!num[iter]) {
			scc(iter);
			low[index] = min(low[index], low[iter]);
		}
		else if (visited[iter]) low[index] = min(low[index], low[iter]);
	}
	if (num[index] == low[index]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			temp.push_back(k);
			check[k] = cnt_;
			visited[k] = 0;
			if (index == k) break;
		}
		v.push_back(temp);
		temp.clear();
	}
}

void make_new_graph() {
	for (int i = 0; i < cnt_; i++) {
		for (auto& itr : v[i]) {
			for (auto& iter : graph[itr]) {
				if (check[itr] == check[iter]) continue;
				pre[check[iter]]++;
				new_graph[check[itr]].push_back(check[iter]);
			}
		}
	}
}

void bfs() {
	int i, a;
	for (i = 1; i <= cnt_; i++) {
		if (!pre[i]) q.push(i);
	}
	while (!q.empty()) {
		a = q.front();
		q.pop();
		if (ans[a]) continue;
		ans[a] = -1;
		ans[um[a]] = 1;
		for (auto& iter : new_graph[a]) {
			pre[iter]--;
			if (!pre[iter]) q.push(iter);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, tf = 0; cin >> n >> m;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[((a > 0) ? 10000 + a : -a)].push_back(((b > 0) ? b : 10000 - b));
		graph[((b > 0) ? 10000 + b : -b)].push_back(((a > 0) ? a : 10000 - a));
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 10001; i <= n + 10000; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= n; i++) {
		if (check[i] == check[i + 10000]) {
			tf = 1;
			break;
		}
		else {
			um[check[i]] = check[i + 10000];
			um[check[i + 10000]] = check[i];
		}
	}
	if (tf) {
		cout << 0;
		return 0;
	}
	make_new_graph();
	bfs();
	cout << 1 << '\n';
	for (i = 1; i <= n; i++) {
		if (ans[check[i]] == -1) cout << 0 << ' ';
		if (ans[check[i]] == 1) cout << 1 << ' ';
	}
}
