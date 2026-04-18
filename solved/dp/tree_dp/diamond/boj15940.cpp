#include<iostream>
#include<vector>
#define ll long long
#define pii pair<int, ll>
#define x first
#define dis second
using namespace std;

struct info {
	int a, b;
	ll c;
};

int n, dis[200001];
ll r[200001][2];
pii dp[200001][5];
vector<pii> g[200001];
info edge[200001];

void dfs(int a, int pre) {
	for (auto& iter : g[a]) {
		if (iter.x == pre) continue;
		dis[iter.x] = dis[a] + 1;
		dfs(iter.x, a);
		if (dp[a][2].dis < dp[iter.x][0].dis + iter.dis) dp[a][2] = { iter.x,dp[iter.x][0].dis + iter.dis };
		if (dp[a][1].dis < dp[iter.x][0].dis + iter.dis) {
			dp[a][2] = dp[a][1];
			dp[a][1] = { iter.x,dp[iter.x][0].dis + iter.dis };
		}
		if (dp[a][0].dis < dp[iter.x][0].dis + iter.dis) {
			dp[a][1] = dp[a][0];
			dp[a][0] = { iter.x,dp[iter.x][0].dis + iter.dis };
		}
		if (dp[a][4].dis < r[iter.x][0]) {
			dp[a][4] = { iter.x,r[iter.x][0] };
		}
		if (dp[a][3].dis < r[iter.x][0]) {
			dp[a][4] = dp[a][3];
			dp[a][3] = { iter.x,r[iter.x][0] };
		}
	}
	r[a][0] = max(dp[a][0].dis + dp[a][1].dis, dp[a][3].dis);
}

void dfs_(int a, int pre, ll cmp1, ll cmp2) {
	for (auto& iter : g[a]) {
		if (iter.x == pre) continue;
		r[iter.x][1] = cmp2;
		ll ncmp1 = 0, ncmp2 = 0;
		if (iter.x == dp[a][0].x) {
			ncmp1 = max(cmp1, dp[a][1].dis);
			r[iter.x][1] = max(r[iter.x][1], dp[a][1].dis + max(cmp1, dp[a][2].dis));
		}
		else {
			ncmp1 = max(cmp1, dp[a][0].dis);
			if (iter.x == dp[a][1].x) r[iter.x][1] = max(r[iter.x][1], dp[a][0].dis + max(cmp1, dp[a][2].dis));
			else r[iter.x][1] = max(r[iter.x][1], dp[a][0].dis + max(cmp1, dp[a][1].dis));
		}
		if (iter.x == dp[a][3].x) r[iter.x][1] = max(r[iter.x][1], dp[a][4].dis);
		else r[iter.x][1] = max(r[iter.x][1], dp[a][3].dis);
		ncmp2 = max(cmp2, r[iter.x][1]);
		dfs_(iter.x, a, ncmp1 + iter.dis, ncmp2);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, c; cin >> n;
	for (i = 1; i < n; i++) {
		cin >> a >> b >> c;
		g[a].push_back({ b,c });
		g[b].push_back({ a,c });
		edge[i] = { a,b,c };
	}
	dfs(1, 1);
	for (auto& iter : g[1]) {
		ll cmp1 = 0, cmp2 = 0;
		if (iter.x == dp[1][0].x) {
			cmp1 = dp[1][1].dis;
			if (iter.x == dp[1][3].x) cmp2 = max(dp[1][1].dis + dp[1][2].dis, dp[1][4].dis);
			else cmp2 = max(dp[1][1].dis + dp[1][2].dis, dp[1][3].dis);
		}
		else {
			cmp1 = dp[1][0].dis;
			if (iter.x == dp[1][1].x) {
				if (iter.x == dp[1][3].x) cmp2 = max(dp[1][0].dis + dp[1][2].dis, dp[1][4].dis);
				else cmp2 = max(dp[1][0].dis + dp[1][2].dis, dp[1][3].dis);
			}
			else {
				if (iter.x == dp[1][3].x) cmp2 = max(dp[1][0].dis + dp[1][1].dis, dp[1][4].dis);
				else cmp2 = max(dp[1][0].dis + dp[1][1].dis, dp[1][3].dis);
			}
		}
		r[iter.x][1] = cmp2;
		dfs_(iter.x, 1, cmp1 + iter.dis, cmp2);
	}
	ll ans = 0;
	for (i = 1; i < n; i++) {
		if (dis[edge[i].a] < dis[edge[i].b]) edge[i].a = edge[i].b;
		ans = max(ans, edge[i].c + r[edge[i].a][0] + r[edge[i].a][1]);
	}
	cout << ans;
}
