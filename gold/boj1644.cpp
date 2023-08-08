#include<iostream>
#include<vector>
using namespace std;

bool check[4001000];
vector<int> v;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, j, le = 0, ri = 0, sum = 0, cnt = 0; cin >> n;
	for (i = 2; i <= 4001000; i++) check[i] = 1;
	for (i = 2; i <= 4001000; i++) {
		if (check[i]) {
			for (j = i * 2; j <= n; j += i) check[j] = 0;
			v.push_back(i);
		}
	}
	int l = v.size();
	while (le <= ri && ri < l) {
		if (sum >= n) {
			sum -= v[le];
			le++;
		}
		else {
			sum += v[ri];
			ri++;
		}
		if (sum == n) cnt++;
	}
	cout << cnt;
}
