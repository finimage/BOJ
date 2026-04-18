#include<iostream>
#include<vector>
#define pii pair<int, int>
#define x first
#define dis second
using namespace std;

int n, q, dis[200001], r[200001][2];
pii dp[200001][5];
vector<int> g[200001];

void dfs(int a, int pre) {
	for (auto& iter : g[a]) {
		if (iter == pre) continue;
		dis[iter] = dis[a] + 1;
		dfs(iter, a);
		if (dp[a][2].dis < dp[iter][0].dis + 1) {
			dp[a][2] = { iter,dp[iter][0].dis + 1 };
		}
		if (dp[a][1].dis < dp[iter][0].dis + 1) {
			dp[a][2] = dp[a][1];
			dp[a][1] = { iter,dp[iter][0].dis + 1 };
		}
		if (dp[a][0].dis < dp[iter][0].dis + 1) {
			dp[a][1] = dp[a][0];
			dp[a][0] = { iter,dp[iter][0].dis + 1 };
		}
		if (dp[a][4].dis < r[iter][0]) {
			dp[a][4] = { iter,r[iter][0] };
		}
		if (dp[a][3].dis < r[iter][0]) {
			dp[a][4] = dp[a][3];
			dp[a][3] = { iter,r[iter][0] };
		}
	}
	r[a][0] = max(dp[a][0].dis + dp[a][1].dis, dp[a][3].dis);
}

void dfs_(int a, int pre, int cmp1, int cmp2) {
	for (auto& iter : g[a]) {
		if (iter == pre) continue;
		r[iter][1] = cmp2;
		int ncmp1 = 0, ncmp2 = 0;
		if (iter == dp[a][0].x) {
			ncmp1 = max(cmp1, dp[a][1].dis);
			r[iter][1] = max(r[iter][1], dp[a][1].dis + max(cmp1, dp[a][2].dis));
		}
		else {
			ncmp1 = max(cmp1, dp[a][0].dis);
			if (iter == dp[a][1].x) r[iter][1] = max(r[iter][1], dp[a][0].dis + max(cmp1, dp[a][2].dis));
			else r[iter][1] = max(r[iter][1], dp[a][0].dis + max(cmp1, dp[a][1].dis));
		}
		if (iter == dp[a][3].x) r[iter][1] = max(r[iter][1], dp[a][4].dis);
		else r[iter][1] = max(r[iter][1], dp[a][3].dis);
		ncmp2 = max(cmp2, r[iter][1]);
		dfs_(iter, a, ncmp1 + 1, ncmp2);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n >> q;
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, 1);
	for (auto& iter : g[1]) {
		int cmp1 = 0, cmp2 = 0;
		if (iter == dp[1][0].x) {
			cmp1 = dp[1][1].dis;
			if (iter == dp[1][3].x) cmp2 = max(dp[1][1].dis + dp[1][2].dis, dp[1][4].dis);
			else cmp2 = max(dp[1][1].dis + dp[1][2].dis, dp[1][3].dis);
		}
		else {
			cmp1 = dp[1][0].dis;
			if (iter == dp[1][1].x) {
				if (iter == dp[1][3].x) cmp2 = max(dp[1][0].dis + dp[1][2].dis, dp[1][4].dis);
				else cmp2 = max(dp[1][0].dis + dp[1][2].dis, dp[1][3].dis);
			}
			else {
				if (iter == dp[1][3].x) cmp2 = max(dp[1][0].dis + dp[1][1].dis, dp[1][4].dis);
				else cmp2 = max(dp[1][0].dis + dp[1][1].dis, dp[1][3].dis);
			}
		}
		r[iter][1] = cmp2;
		dfs_(iter, 1, cmp1 + 1, cmp2);
	}
	/*
	for (i = 1; i <= n; i++) {
		cout << "상위 트리 지름 : " << r[i][1] << " 하위 트리 지름 : " << r[i][0] << '\n';
	}
	for (i = 1; i <= n; i++) {
		cout << i << '\n';
		for (int j = 0; j < 5; j++) {
			cout << dp[i][j].x << " : " << dp[i][j].dis << '\n';
		}
		cout << '\n';
	}*/
	while (q--) {
		cin >> a >> b;
		if (dis[a] < dis[b]) a = b;
		cout << r[a][0] + r[a][1] + 1 << '\n';
	}
}
