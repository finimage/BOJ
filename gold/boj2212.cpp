#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int arr[10001];
vector<int> v;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k, i, ans; cin >> n >> k;
	for (i = 0; i < n; i++) cin >> arr[i];
	sort(arr, arr + n);
	ans = arr[n - 1] - arr[0];
	for (i = 1; i < n; i++) v.push_back(arr[i] - arr[i - 1]);
	sort(v.begin(), v.end(), greater<>());
	k--;
	for (auto& iter : v) {
		if (!k) break;
		ans -= iter;
		k--;
	}
	cout << ans;
}
