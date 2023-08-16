#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<unordered_set>
using namespace std;

stack<int> st;
vector<int> graph[10001], new_graph[10001];
int n, m, S, T, num[10001], low[10001], cnt, cnt_, check[10001], check_cnt[10001], pre[10001], visit_sum[10001];
bool visited[10001];
unordered_set<int> us[10001];
queue<int> q;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
	for (auto& iter : graph[ind]) {
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
			check_cnt[cnt_]++;
			visited[k] = 0;
			if (ind == k) break;
		}
	}
}

void make_new_graph() {
	for (int i = 1; i <= n; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			if (us[check[i]].count(check[iter])) continue;
			us[check[i]].insert(check[iter]);
			new_graph[check[i]].push_back(check[iter]);
		}
	}
}

void topological_sorting() {
	q.push(check[S]);
	visited[check[S]] = 1;
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (auto& iter : new_graph[a]) {
			pre[iter]++;
			if (visited[iter]) continue;
			visited[iter] = 1;
			q.push(iter);
		}
	}
}

void bfs() {
	q.push(check[S]);
	visit_sum[check[S]] = check_cnt[check[S]];
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (auto& iter : new_graph[a]) {
			pre[iter]--;
			visit_sum[iter] = max(visit_sum[iter], visit_sum[a] + check_cnt[iter]);
			if (!pre[iter]) q.push(iter);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n >> m >> S >> T;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	make_new_graph();
	topological_sorting();
	bfs();
	cout << visit_sum[check[T]];
}
