#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

struct info {
	int x, v;
};

vector<info> graph[10001];
stack<int> ans;
int pre[10001], score[10001], path[10001];
queue<int> q;

void bfs() {
	q.push(1);
	int a;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		for (auto& iter : graph[a]) {
			pre[iter.x]--;
			if (score[iter.x] < score[a] + iter.v) {
				score[iter.x] = score[a] + iter.v;
				path[iter.x] = a;
			}
			if (!pre[iter.x]) {
				if (iter.x == 1) continue;
				q.push(iter.x);
			}
		}
	}
}

void dfs(int a) {
	ans.push(a);
	if (path[a] != 1) dfs(path[a]);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, a, b, c; cin >> n >> m;
	while (m--) {
		cin >> a >> b >> c;
		pre[b]++;
		graph[a].push_back({ b,c });
	}
	bfs();
	dfs(1);
	cout << score[1] << '\n' << 1 << ' ';
	while (!ans.empty()) {
		cout << ans.top() << ' ';
		ans.pop();
	}
}
