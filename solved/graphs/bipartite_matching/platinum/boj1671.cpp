#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

struct Info {
	int s, v, i;
};

Info info[51];
vector<int> g[51];
int n, check[51];
bool visited[51];

int dfs(int node) {
	for (auto& iter : g[node]) {
		if (visited[iter]) continue;
		visited[iter] = 1;
		if (!check[iter]) return check[iter] = node;
		if (dfs(check[iter])) return check[iter] = node;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, ans = 0; cin >> n;
	for (i = 1; i <= n; i++) {
		cin >> info[i].s >> info[i].v >> info[i].i;
		for (j = 1; j < i; j++) {
			if (info[i].s >= info[j].s && info[i].v >= info[j].v && info[i].i >= info[j].i) g[i].push_back(j);
			if (info[i].s <= info[j].s && info[i].v <= info[j].v && info[i].i <= info[j].i) {
				if (info[i].s != info[j].s || info[i].v != info[j].v || info[i].i != info[j].i) g[j].push_back(i);
			}
		}
	}
	for (i = 1; i <= n; i++) {
		dfs(i);
		memset(visited, 0, sizeof(visited));
		dfs(i);
		memset(visited, 0, sizeof(visited));
	}
	for (i = 1; i <= n; i++) {
		if (!check[i]) ans++;
	}
	cout << ans;
}
