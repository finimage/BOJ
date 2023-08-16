#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<queue>
using namespace std;

//r=>-1, b=>1

stack<int> st;
vector<int> graph[10001], new_graph[10001];
int k, n, num[10001], low[10001], cnt, cnt_, check[10001], pre[10001], ans[10001];
bool visited[10001];
unordered_map<int, int> um;
queue<int> q;

void put_graph(int a, int b, int c, char A, char B, char C) {
	if (A == 'B') {
		graph[a + 5000].push_back((B == 'B') ? b : b + 5000);
		graph[a + 5000].push_back((C == 'B') ? c : c + 5000);
	}
	else {
		graph[a].push_back((B == 'B') ? b : b + 5000);
		graph[a].push_back((C == 'B') ? c : c + 5000);
	}
}

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
			visited[k] = 0;
			if (ind == k) break;
		}
	}
}

void make_new_graph() {
	int i;
	for (i = 1; i <= k; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			new_graph[check[i]].push_back(check[iter]);
			pre[check[iter]]++;
		}
	}
	for (i = 5001; i <= k + 5000; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			new_graph[check[i]].push_back(check[iter]);
			pre[check[iter]]++;
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
	int i, j, a[3]; cin >> k >> n;
	char b[3];
	for (i = 0; i < n; i++) {
		for (j = 0; j < 3; j++) cin >> a[j] >> b[j];
		put_graph(a[0], a[1], a[2], b[0], b[1], b[2]);
		put_graph(a[1], a[0], a[2], b[1], b[0], b[2]);
		put_graph(a[2], a[1], a[0], b[2], b[1], b[0]);
	}
	for (i = 1; i <= k; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 5001; i <= k + 5000; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= k; i++) {
		if (check[i] == check[i + 5000]) {
			cout << -1;
			return 0;
		}
		else {
			um[check[i]] = check[i + 5000];
			um[check[i + 5000]] = check[i];
		}
	}
	make_new_graph();
	bfs();
	for (i = 1; i <= k; i++) cout << ((ans[check[i]] == 1) ? 'B' : 'R');
}
