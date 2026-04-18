#include<iostream>
#include<algorithm>
using namespace std;

int n, m, co[301] = { 0, }, dp[2][301][301] = { 0, };

void init() {
	int i, j, t;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 301; j++) {
			for (t = 0; t < 301; t++) dp[i][j][t] = -1;
		}
	}
}

int candy(int dir, int le, int ri, int cnt) {
	if (cnt == 0) return 0;
	if (dp[dir][le][ri] != -1) return dp[dir][le][ri];
	dp[dir][le][ri] = 2147483647;
	int temp;
	if (dir) temp = co[ri];
	else temp = co[le];
	if (le > 0) dp[dir][le][ri] = cnt * (temp - co[le - 1]) + candy(0, le - 1, ri, cnt - 1);
	if (ri < n - 1) dp[dir][le][ri] = min(dp[dir][le][ri], cnt * (co[ri + 1] - temp) + candy(1, le, ri + 1, cnt - 1));
	return dp[dir][le][ri];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, tf = 1, temp, ans = 0;
	cin >> n >> m;
	for (i = 0; i < n; i++) {
		cin >> co[i];
		if (co[i] == 0) tf = 0;
	}
	if (tf) {
		co[n] = 0;
		n++;
	}
	sort(co, co + n);
	temp = lower_bound(co, co + n, 0) - co;
	for (i = 0; i < n; i++) {
		init();
		ans = max(ans, m * i - candy(0, temp, temp, i));
	}
	if (tf == 0) ans += m;
	cout << ans;
}
