#include<iostream>
using namespace std;

int arr[500001], sum[500001], ans = -2000000001;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, k, i, Min = 2000000001; cin >> n >> k >> arr[0];
	sum[0] = arr[0] - k;
	for (i = 1; i < n; i++) {
		cin >> arr[i];
		sum[i] = arr[i] - k * (i + 1);
		Min = min(Min, sum[i - 1]);
		ans = max(ans, sum[i] - Min);
	}
	sum[n - 1] = arr[n - 1] - k;
	Min = 2000000001;
	for (i = n - 2; i >= 0; i--) {
		sum[i] = arr[i] - k * (n - i);
		Min = min(Min, sum[i + 1]);
		ans = max(ans, sum[i] - Min);
	}
	cout << ans;
}
