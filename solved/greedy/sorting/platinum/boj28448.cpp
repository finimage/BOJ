#include<iostream>
#include<queue>
#define ll long long
using namespace std;

struct info {
	int k, t;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		if (a.k < b.k) return 1;
		else if (a.k == b.k && a.t < b.t) return 1;
		return 0;
	}
};

priority_queue<info,vector<info>,cmp> pq;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, k, t, L, state = 0, temp_k = -1, temp_t = 0; cin >> n >> L;
	ll total = 0;
	for (i = 0; i < n; i++) {
		cin >> k >> t;
		if (t <= 5) total += t;
		else pq.push({ k,t });
	}
	while (!pq.empty()) {
		k = pq.top().k;
		t = pq.top().t;
		pq.pop();
		if (state + k*t > L) {
			total += (ll)(state + k * t - L);
			state = L - k * t;
		}
		state += k * t;
		state -= k * 5;
		total += t;
	}
	cout << total;
}
