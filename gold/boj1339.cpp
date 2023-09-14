#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#define ll long long
using namespace std;

unordered_map<char, ll> um;
vector<ll> ans;

void change_(string s) {
	int l = s.size(), i;
	ll a = 1;
	for (i = 1; i < l; i++) a *= 10;
	for (i = 0; i < l; i++) {
		if (um.count(s[i])) um[s[i]] += a;
		else um[s[i]] = a;
		a /= 10;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i; cin >> n;
	string s;
	for (i = 0; i < n; i++) {
		cin >> s;
		change_(s);
	}
	for (auto& iter : um) ans.push_back(iter.second);
	sort(ans.begin(), ans.end(), greater<>());
	ll res = 0, t = 9;
	for (auto& iter : ans) {
		res += t * iter;
		t--;
	}
	cout << res;
}
