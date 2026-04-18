#include<iostream>
#include<queue>
using namespace std;

struct info{
	int k, p, s;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.k < b.k;
	}
};

int dp[101002];
priority_queue<info, vector<info>, cmp> pq;

void ans(int ind) {
	int n, p, s, i, j, ans_ = 0;
	for (i = 0; i < 101002; i++) dp[i] = 0;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> p >> s;
		pq.push({ p + s,p,s });
	}
	while (!pq.empty()) {
		p = pq.top().p;
		s = pq.top().s;
		pq.pop();
		for (j = 0; j <= p; j++) {
			dp[j] = max(dp[j], s + dp[j + s]);
			ans_ = max(ans_, dp[j]);
		}
	}
	cout << "Case #" << ind << ": " << ans_ << '\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int t, i;
	cin >> t;
	for (i = 1; i <= t; i++) ans(i);
}
