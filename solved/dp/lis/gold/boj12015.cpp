#include<iostream>
using namespace std;

int arr[1000001], dp[1000001], dp_[1000001];

int search(int le, int ri, int v) {
	int res = 0, mid;
	while (le <= ri) {
		mid = (le + ri) / 2;
		if (v > dp_[mid]) {
			res = mid;
			le = mid + 1;
		}
		else {
			ri = mid - 1;
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, ans = 0; cin >> n;
	for (i = 1; i <= 1000000; i++) dp_[i] = 1000001;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		dp[i] = search(0, ans, arr[i]) + 1;
		dp_[dp[i]] = min(dp_[dp[i]], arr[i]);
		ans = max(ans, dp[i]);
	}
	cout << ans;
}
