#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

struct info {
	int num, x, y;
};

int n, h;
bool visited[500001];
vector<int> indegree, indeg;
vector<vector<info>> v;
vector<vector<int>> g;
queue<int> q;

int bfs(int ind) {
	int res = 0, x;
	q.push(ind);
	vector<int> tmp;
	while (!q.empty()) {
		x = q.front();
		res++;
		visited[x] = 1;
		q.pop();
		for (auto& iter : g[x]) {
			indegree[iter]--;
			if (!indeg[iter]) tmp.emplace_back(iter);
			indeg[iter]++;
			if (indegree[iter] == 0) q.push(iter);
		}
	}
	for (auto& iter : tmp) indegree[iter] += indeg[iter];
	return res;
}

bool cmp(info a, info b) {
	return a.x < b.x;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, t, H, L, R; cin >> n >> h;
	v.resize(h + 1);
	g.resize(n + 1);
	indegree.resize(n + 1);
	indeg.resize(n + 1);
	for (i = 1; i <= n; i++) {
		cin >> H >> L >> R;
		v[H].push_back({i,L,R});
	}
	for (i = 1; i <= h; i++) sort(v[i].begin(), v[i].end(), cmp);
	for (i = 2; i <= h; i++) {
		int lj = v[i - 1].size(), lt = v[i].size();
		j = t = 0;
		while (j < lj && t < lt) {
			if (v[i - 1][j].y <= v[i][t].x) j++;
			else if (v[i - 1][j].x >= v[i][t].y) t++;
			else {
				g[v[i - 1][j].num].emplace_back(v[i][t].num);
				indegree[v[i][t].num]++;
				if (j + 1 < lj && v[i - 1][j + 1].y > v[i][t].x && v[i - 1][j + 1].x < v[i][t].y) j++;
				else t++;
			}
		}
	}
	int ans = 0;
	for (i = 1; i <= h; i++) {
		for (auto& iter : v[i]) {
			if (!visited[iter.num]) ans = max(ans, bfs(iter.num));
		}
	}
	cout << ans;
}
