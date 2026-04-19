#include<iostream>
#include<vector>
using namespace std;

int n, m, dp[1001][10001];
vector<int> d, tmp;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, t, ans = -1; cin >> n >> m;
	d.resize(n + 1, 0);
	for (i = 0; i < n; i++) cin >> d[i];
	for (i = 0; i < n; i++) {
		tmp.resize(d[i] + 1, 0);
		for (j = 0; j < d[i]; j++) cin >> tmp[j];
		if (i == 0) {
			for (j = 0; j < d[i]; j++) {
				for (t = m; t > 0; t--) {
					if (dp[i][t] && t + tmp[j] <= m) dp[i][t + tmp[j]] = 1;
				}
				dp[i][tmp[j]] = 1;
			}
			continue;
		}
		for (j = 0; j < d[i]; j++) {
			for (t = m; t > 0; t--) {
				if (dp[i][t] && t + tmp[j] <= m) dp[i][t + tmp[j]] = 1;
				if (dp[i - 1][t] && t + tmp[j] <= m) dp[i][t + tmp[j]] = 1;
			}
		}
	}
	for (i = m; i > 0; i--) {
		if (dp[n - 1][i]) {
			ans = i;
			break;
		}
	}
	cout << ans;
}
