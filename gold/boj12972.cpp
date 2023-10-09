#include<iostream>
#include<map>
#include<vector>
using namespace std;

map<int, int> arr;
vector<int> ans;

int gcd(int a, int b) {
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, a; cin >> n;
	for (i = 0; i < n * n; i++) {
		cin >> a;
		if (arr.count(-a)) arr[-a]++;
		else arr[-a] = 1;
	}
	for (auto& iter : arr) {
		while (iter.second) {
			iter.second--;
			if (ans.size()) {
				for (auto& itr : ans) arr[-gcd(itr, -iter.first)] -= 2;
			}
			ans.push_back(-iter.first);
		}
	}
	for (auto& iter : ans) cout << iter << ' ';
}
