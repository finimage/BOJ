#include<iostream>
#include<vector>
#define ll long long
using namespace std;

struct info {
	int t, b, c;
};

ll dp[100001], Max[100001];
vector<info> v;

int res(int k, int cmp) {
	int le = 0, ri = k, ans = -1;
	while (le <= ri) {
		int mid = (le + ri) / 2;
		if (v[mid].t < cmp) {
			ans = mid;
			le = mid + 1;
		}
		else ri = mid - 1;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i; cin >> n;
	v = vector<info>(n);
	for (i = 0; i < n; i++) cin >> v[i].t;
	for (i = 0; i < n; i++) cin >> v[i].b;
	for (i = 0; i < n; i++) cin >> v[i].c;
	ll ans = 0;
	for (i = 0; i < n; i++) {
		dp[i] = v[i].c;
		int k = res(i - 1, v[i].t - v[i].b);
		if (k >= 0) dp[i] += Max[k];
		ans = max(ans, dp[i]);
		Max[i] = max(dp[i], (i >= 1) ? Max[i - 1] : 0);
	}
	cout << ans;
}
