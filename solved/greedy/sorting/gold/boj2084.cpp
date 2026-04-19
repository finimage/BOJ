#include<bits/stdc++.h>
using namespace std;

int n, g[2001][2001], degree[2001];
vector<int> v;

bool cmp(int a, int b) {
	return degree[a] > degree[b];
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, total = 0; cin >> n;
	v.resize(n);
	for (i = 1; i <= n; i++) {
		cin >> degree[i];
		total += degree[i];
		v[i - 1] = i;
	}
	if (total % 2) {
		cout << -1;
		return 0;
	}
	for (j = 0; j < n; j++) {
		sort(v.begin(), v.end(), cmp);
		for (i = 1; i < n; i++) {
			if (degree[v[0]] * degree[v[i]] == 0) break;
			degree[v[0]]--;
			degree[v[i]]--;
			g[v[0]][v[i]] = g[v[i]][v[0]] = 1;
		}
		if (degree[v[0]] > 0) {
			cout << -1;
			return 0;
		}
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) cout << g[i][j] << ' ';
		cout << '\n';
	}
}
