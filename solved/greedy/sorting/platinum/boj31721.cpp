#include<bits/stdc++.h>
using namespace std;

vector<int> v, total;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int m, n, a, b, i, j, ans = 0, l; cin >> m >> n;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		if (a >= b) ans++;
		else v.push_back(a);
	}
	sort(v.begin(), v.end());
	l = v.size();
	total.resize(l, 0);
	for (i = 0; i < l; i++) {
		if (total[i] == v[i]) continue;
		ans++;
		int tmp = n - 1;
		for (j = i + 1; j < l; j++) {
			if (tmp >= v[j] - total[j]) {
				tmp -= v[j] - total[j];
				total[j] += v[j] - total[j];
			}
			else break;
		}
		if (j + 1 < l) total[j + 1] += tmp;
	}
	cout << ans;
}
