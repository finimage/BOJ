#include<iostream>
#include<vector>
#include<queue>
#define ll long long
using namespace std;

priority_queue<pair<int, int>> pq;
vector<int> val;
vector<vector<int>> g;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
    int n, i, a; cin >> n;
	ll ans = 0;
	val = vector<int>(n + 1);
	g = vector<vector<int>>(n + 1);
	for (i = 2; i <= n; i++) {
		cin >> a;
		g[a].push_back(i);
	}
	for (i = 1; i <= n; i++) cin >> val[i];
	pq.push({ val[1],1 });
	while (!pq.empty()) {
		ans += pq.top().first;
		a = pq.top().second;
		pq.pop();
		for (auto& iter : g[a]) pq.push({ val[iter],iter });
		cout << ans <<'\n';
	}
}
