#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<unordered_set>
using namespace std;

vector<vector<int>> graph, new_graph;
int n, start, num[100001], low[100001], cnt, cnt_, check[100001], indegree[100001], dp[2][100001];
bool visited[100001];
stack<int> st;
queue<int> q;
unordered_set<int> us[100001];

void input() {
	int i, a; cin >> n;
	graph = vector<vector<int>>(n + 1);
	for (i = 1; i <= n; i++) {
		cin >> a;
		if (i - a >= 1) graph[i].push_back(i - a);
		if (i + a <= n) graph[i].push_back(i + a);
	}
	cin >> start;
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
			visited[k] = 0;
			check[k] = cnt_;
			dp[0][cnt_]++;
			if (ind == k) break;
		}
	}
}

void SCC() {
	for (int i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
}

void make_new_graph() {
	new_graph = vector<vector<int>>(cnt_ + 1);
	for (int i = 1; i <= n; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			if (us[check[i]].count(check[iter])) continue;
			us[check[i]].insert(check[iter]);
			new_graph[check[i]].push_back(check[iter]);
		}
	}
}

void topological_sort() {
	q.push(check[start]);
	visited[check[start]] = 1;
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (auto& iter : new_graph[a]) {
			indegree[iter]++;
			if (visited[iter]) continue;
			visited[iter] = 1;
			q.push(iter);
		}
	}
}

void search() {
	int a, ans = 0;
	q.push(check[start]);
	dp[1][check[start]] = dp[0][check[start]];
	while (!q.empty()) {
		a = q.front();
		q.pop();
		ans = max(ans, dp[1][a]);
		for (auto& iter : new_graph[a]) {
			indegree[iter]--;
			dp[1][iter] = max(dp[1][iter], dp[0][iter] + dp[1][a]);
			ans = max(ans, dp[1][iter]);
			if (!indegree[iter]) q.push(iter);
		}
	}
	cout << ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	SCC();
	make_new_graph(); 
	topological_sort();
	search();
}
