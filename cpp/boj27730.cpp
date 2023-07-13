#include<iostream>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

struct info {
	int x;
	ll dis;
};

vector<info> graph[2][100001];
int node[2];
ll n[2], res[2][100001], dp[2][100001], cnt[2][100001], ans[2];
bool visited[2][100001];
queue<int> q;

void input(int t) {
	int i, a, b; ll c;
	for (i = 1; i < n[t]; i++) {
		cin >> a >> b >> c;
		graph[t][a].push_back({ b,c });
		graph[t][b].push_back({ a,c });
	}
}

void dfs(int t, int a) {
	visited[t][a] = 1;
	cnt[t][a] = 1;
	for (auto& iter : graph[t][a]) {
		if (visited[t][iter.x]) continue;
		dfs(t, iter.x);
		cnt[t][a] += cnt[t][iter.x];
		dp[t][a] += dp[t][iter.x] + iter.dis * cnt[t][iter.x];
	}
	visited[t][a] = 0;
}

void find_min(int t, int a) {
	q.push(a);
	ans[t] = res[t][a] = dp[t][a];
	node[t] = 1;
	visited[t][a] = 1;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		for (auto& iter : graph[t][a]) {
			if (visited[t][iter.x]) {
				res[t][a] = res[t][iter.x] + iter.dis * (n[t] - 2 * cnt[t][a]);
				if (ans[t] > res[t][a]) {
					ans[t] = res[t][a];
					node[t] = a;
				}
			}
			else q.push(iter.x);
			visited[t][iter.x] = 1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	for (int i = 0; i < 2; i++) {
		cin >> n[i];
		input(i);
		dfs(i, 1);
		find_min(i, 1);
	}
	cout << node[0] << ' ' << node[1] << '\n' << ans[0] * n[1] + ans[1] * n[0] + n[0] * n[1];
}
