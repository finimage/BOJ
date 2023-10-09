#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int n, arr[51], check[51];
bool prime[2001], table[51][51], visited[51];
vector<int> g[51], ans;

int dfs(int node) {
	for (auto& iter : g[node]) {
		if (!table[node][iter]) continue;
		if (visited[iter]) continue;
		visited[iter] = 1;
		if (!check[iter]) {
			check[node] = iter;
			return check[iter] = node;
		}
		if (dfs(check[iter])) {
			check[node] = iter;
			return check[iter] = node;
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, cnt; cin >> n;
	for (i = 2; i <= 2000; i++) prime[i] = 1;
	for (i = 2; i <= 2000; i++) {
		if (prime[i]) {
			for (j = i * 2; j <= 2000; j += i) prime[j] = 0;
		}
	}
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		for (j = 1; j < i; j++) {
			if (prime[arr[i] + arr[j]]) {
				g[i].push_back(j);
				g[j].push_back(i);
				table[i][j] = table[j][i] = 1;
			}
		}
	}
	while (1) {
		cnt = 0;
		for (i = 1; i <= n; i++) {
			if (check[i]) cnt++;
			else if (dfs(i)) cnt++;
			memset(visited, 0, sizeof(visited));
		}
		if (cnt != n) break;
		else {
			table[1][check[1]] = table[check[1]][1] = 0;
			ans.push_back(arr[check[1]]);
		}
		memset(check, 0, sizeof(check));
	}
	if (ans.size()) {
		sort(ans.begin(), ans.end());
		for (auto& iter : ans) cout << iter << ' ';
	}
	else cout << -1;
}
