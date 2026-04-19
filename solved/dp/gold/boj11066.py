#include<iostream>
using namespace std;

int arr[501], dp[501][501];

void solve() {
	int k, i, j, t; cin >> k;
	for (i = 1; i <= k; i++) {
		cin >> arr[i];
		arr[i] += arr[i - 1];
	}
	for (i = 1; i < k; i++) {
		for (j = 1; j <= k - i; j++) {
			dp[j][j + i] = dp[j][j] + dp[j + 1][j + i] + arr[j + i] - arr[j - 1];
			for (t = j + 1; t < j + i; t++) {
				dp[j][j + i] = min(dp[j][j + i], dp[j][t] + dp[t + 1][j + i] + arr[j + i] - arr[j - 1]);
			}
		}
	}
	cout << dp[1][k] << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
