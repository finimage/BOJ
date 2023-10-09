#include<iostream>
#include<vector>
using namespace std;

int n, gcd_table[101][101], check[101], pre[2][101];

int gcd(int a, int b) {
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

void solve() {
	int i, j, ans = 0;
	vector<int> arr(n + 1);
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		pre[1][arr[i]] = check[arr[i]] = 1;
		for (j = 1; j <= 100; j++) {
			if (pre[0][j]) pre[1][gcd_table[arr[i]][j]] = check[gcd_table[arr[i]][j]] = 1;
		}
		for (j = 1; j <= 100; j++) {
			pre[0][j] = pre[1][j];
			pre[1][j] = 0;
		}
	}
	for (i = 1; i <= 100; i++) {
		ans += check[i];
		pre[0][i] = check[i] = 0;
	}
	cout << ans << '\n';
	arr.clear();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j;
	for (i = 1; i <= 99; i++) {
		gcd_table[i][i] = i;
		for (j = i + 1; j <= 100; j++) gcd_table[i][j]=gcd_table[j][i]= gcd(i, j);
	}
	while (1) {
		cin >> n;
		if (n == 0) break;
		solve();
	}
}
