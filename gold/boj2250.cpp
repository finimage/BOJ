#include<iostream>
#include<queue>
using namespace std;

struct node {
	int le, ri;
};

struct info {
	int a, lev;
};

node graph[10001], level[10001];
int col[10001], ans[2] = { 1,1 }, dep;
bool check[10001];
queue<info> q;

node dfs(int a, int v, int depth) {
	col[a] = v;
	node temp = { v,v };
	dep = max(dep, depth);
	if (graph[a].le != -1) {
		node temp_ = dfs(graph[a].le, v, depth + 1);
		col[a] = temp_.ri + 1;
		temp = { temp_.le,temp_.ri + 1 };
	}
	if (graph[a].ri != -1) {
		node temp_ = dfs(graph[a].ri, col[a] + 1, depth + 1);
		temp.ri = temp_.ri;
	}
	return temp;
}

void bfs(int k) {
	q.push({ k,1 });
	int a, lev;
	while (!q.empty()) {
		a = q.front().a;
		lev = q.front().lev;
		q.pop();
		if (graph[a].le != -1) q.push({ graph[a].le,lev + 1});
		if (graph[a].ri != -1) q.push({ graph[a].ri,lev + 1});
		level[lev].le = min(level[lev].le, col[a]);
		level[lev].ri = max(level[lev].ri, col[a]);
		int temp = level[lev].ri - level[lev].le + 1;
		if (temp > ans[1]) {
			ans[1] = temp;
			ans[0] = lev;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, a; cin >> n;
	for (i = 0; i < n; i++) {
		cin >> a;
		cin >> graph[a].le >> graph[a].ri;
		check[graph[a].le] = 1;
		check[graph[a].ri] = 1;
	}
	for (i = 1; i <= n; i++) {
		if (!check[i]) {
			a = i;
			break;
		}
	}
	dfs(a, 1, 1);
	for (i = 1; i <= dep; i++) {
		level[i].le = 10002;
		level[i].ri = 0;
	}
	bfs(a);
	cout << ans[0] << ' ' << ans[1];
}
