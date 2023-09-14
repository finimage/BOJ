#include<iostream>
#include<vector>
#define ll long long
using namespace std;

ll ans, sum_dis[300001];
int n, dis[300001], cnt[300001];
vector<int> g[300001];
bool visited[300001];

void dfs(int node) {
	visited[node] = 1;
	cnt[node]++;
	for (auto& iter : g[node]) {
		if (visited[iter]) continue;
		dis[iter] = dis[node] + 1;
		dfs(iter);
		cnt[node] += cnt[iter];
	}
	ll temp = cnt[node];
	for (auto& iter : g[node]) {
		if (visited[iter]) continue;
		sum_dis[node] += sum_dis[iter];
		ans += sum_dis[iter] * (ll)(cnt[node] - cnt[iter]) + (ll)dis[node] * (ll)cnt[iter] * (ll)(temp - cnt[iter] - 1);
		ans += (ll)dis[node] * (ll)cnt[iter];
		temp -= cnt[iter];
	}
	sum_dis[node] += cnt[node];
	visited[node] = 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n;
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	visited[1] = 1;
	dfs(1);
	cout << ans;
}
