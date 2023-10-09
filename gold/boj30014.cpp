#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;

int n, p[2001];
deque<int> dq;

int main() {
	ios_base::sync_with_stdio(0);
	int i, ans = 0; cin >> n;
	for (i = 0; i < n; i++) cin >> p[i];
	sort(p, p + n, greater<>());
	dq.push_back(p[0]);
	for (i = 1; i < n - 1; i++) {
		if (dq.front() > dq.back()) {
			ans += p[i] * dq.front();
			dq.push_front(p[i]);
		}
		else {
			ans += p[i] * dq.back();
			dq.push_back(p[i]);
		}
	}
	ans += p[n - 1] * (dq.front() + dq.back());
	dq.push_back(p[n - 1]);
	cout << ans << '\n';
	while (!dq.empty()) {
		cout << dq.front() << ' ';
		dq.pop_front();
	}
}
