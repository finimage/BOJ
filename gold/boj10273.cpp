#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int x, cost;
};

int n, e, v[20001], indegree[20001], dp[20001], link[20001], ans, cnt, end_node;
vector<info> graph[20001];
queue<int> q;
vector<int> path, temp;

void init() {
	for (int i = 1; i <= n; i++) {
		v[i] = indegree[i] = link[i] = 0;
		dp[i] = -2000000001;
		graph[i].clear();
	}
	path.clear();
	ans = -2000000001;
	cnt = end_node = 0;
}

void searching() {
	q.push(1);
	dp[1] = v[1];
	end_node = 1;
	ans = dp[1];
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (auto& iter : graph[x]) {
			indegree[iter.x]--;
			if (dp[iter.x] < dp[x] - iter.cost + v[iter.x]) {
				dp[iter.x] = dp[x] - iter.cost + v[iter.x];
				link[iter.x] = x;
				if (ans < dp[iter.x]) {
					ans = dp[iter.x];
					end_node = iter.x;
				}
			}
			if (!indegree[iter.x]) q.push(iter.x);
		}
	}
}

void find_path() {
	int k = end_node;
	while (link[k]) {
		temp.push_back(k);
		k = link[k];
	}
	path.push_back(1);
	cnt = 1;
	while (!temp.empty()) {
		cnt++;
		path.push_back(temp.back());
		temp.pop_back();
	}
}

void solve() {
	int i, a, b, c; cin >> n >> e;
	init();
	for (i = 1; i <= n; i++) cin >> v[i];
	for (i = 0; i < e; i++) {
		cin >> a >> b >> c;
		graph[a].push_back({ b,c });
		indegree[b]++;
	}
	searching();
	find_path();
	cout << ans << ' ' << cnt << '\n';
	for (auto& iter : path) cout << iter << ' ';
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
