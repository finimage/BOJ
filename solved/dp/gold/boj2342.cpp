#include<iostream>
using namespace std;

int dp[100002][5], arr[100002];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int ind = 1, i, ans = 400001; cin >> arr[1];
	for (i = 1; i <= 4; i++) dp[0][i] = 400001;
	while (arr[ind]) {
		for (i = 0; i <= 4; i++) dp[ind][i] = 400001;
		if (dp[ind - 1][0] < 400001) {
			dp[ind][arr[ind - 1]] = min(dp[ind][arr[ind - 1]], dp[ind - 1][0] + 2);
			if (arr[ind - 1]) {
				if (abs(arr[ind - 1] - arr[ind]) == 2) dp[ind][0] = min(dp[ind][0], dp[ind - 1][0] + 4);
				else if (arr[ind - 1] == arr[ind]) dp[ind][0] = min(dp[ind][0], dp[ind - 1][0] + 1);
				else dp[ind][0] = min(dp[ind][0], dp[ind - 1][0] + 3);
			}
		}
		for (i = 1; i <= 4; i++) {
			if (dp[ind - 1][i] < 400001) {
				if (abs(arr[ind] - i) == 2) dp[ind][arr[ind - 1]] = min(dp[ind][arr[ind - 1]], dp[ind - 1][i] + 4);
				else if (arr[ind] == i) dp[ind][arr[ind - 1]] = min(dp[ind][arr[ind - 1]], dp[ind - 1][i] + 1);
				else dp[ind][arr[ind - 1]] = min(dp[ind][arr[ind - 1]], dp[ind - 1][i] + 3);
				if (abs(arr[ind] - arr[ind - 1]) == 2) dp[ind][i] = min(dp[ind][i], dp[ind - 1][i] + 4);
				else if (arr[ind] == arr[ind - 1]) dp[ind][i] = min(dp[ind][i], dp[ind - 1][i] + 1);
				else dp[ind][i] = min(dp[ind][i], dp[ind - 1][i] + 3);
			}
		}
		ind++;
		cin >> arr[ind];
	}
	for (i = 0; i <= 4; i++) ans = min(ans, dp[ind - 1][i]);
	cout << ans;
}
