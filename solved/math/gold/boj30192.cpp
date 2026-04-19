#include<bits/stdc++.h>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, k, ans;
vector<int> check;
vector<pii> v;
string s;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, cnt = 1; cin >> n >> k >> s;
	check.resize(n + 1);
	check[0] = 1;
	for (i = 1; i < n; i++) {
		if (s[i] == s[i - 1]) cnt++;
		else cnt = 1;
		check[i] = cnt;
	}
	for (i = n - 1; i >= 0; i--) {
		if (check[i] >= k) {
			if (v.empty() || v.back().x > i) v.push_back({i - check[i] + 1,i});
		}
	}
	for (i = 1; i <= n; i++) {
		int tf = 1;
		for (auto& iter : v) {
			if (iter.x / i == iter.y / i) {
				tf = 0;
				break;
			}
			else {
				if (iter.y / i - iter.x / i >= 2) {
					if (i >= k) {
						tf = 0;
						break;
					}
				}
				else {
					if (i - iter.x % i >= k || iter.y - iter.x + 1 - i + iter.x % i >= k) {
						tf = 0;
						break;
					}
				}
			}
		}
		if (tf) ans = i;
	}
	cout << ans;
}
