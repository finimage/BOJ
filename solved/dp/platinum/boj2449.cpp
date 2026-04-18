#include<iostream>
using namespace std;

int n, arr[201], dp[201][201];

void init() {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) continue;
			dp[i][j] = 201;
		}
	}
}

void solve(int le, int ri) {
	if (le == ri || dp[le][ri] < 201) return;
	for (int i = le; i < ri; i++) {
		solve(le, i);
		solve(i + 1, ri);
		dp[le][ri] = min(dp[le][ri], dp[le][i] + dp[i + 1][ri] + ((arr[le] == arr[i + 1]) ? 0 : 1));
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int k, i; cin >> n >> k;
	for (i = 0; i < n; i++) cin >> arr[i];
	init();
	solve(0, n - 1);
	cout << dp[0][n - 1];
}
