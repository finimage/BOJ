#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;

bool cmp(const pair<ll, ll>& a, const pair<ll, ll>& b) {
	if (a.first + a.second < b.first + b.second) return 1;
	else if (a.first + a.second == b.first + b.second) {
		if (a.second < b.second) return 1;
	}
	return 0;
}

priority_queue<int> pq;
vector<pair<ll, ll>> v;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, cnt = 1, i; cin >> n;
	ll l, d, state;
	for (i = 0; i < n; i++) {
		cin >> l >> d;
		v.push_back({ l,d });
	}
	sort(v.begin(), v.end(), cmp);
	state = v[0].second;
	pq.push(v[0].second);
	for (i = 1; i < n; i++) {
		l = v[i].first;
		d = v[i].second;
		if (state <= l) {
			cnt++;
			state += d;
			pq.push(d);
		}
		else if (state - pq.top() <= l && d <= pq.top()) {
			state += d - pq.top();
			pq.pop();
			pq.push(d);
		}
	}
	cout << cnt;
}
