#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define x first
#define y second
#define INF 250000000001
using namespace std;

int n, m;
vector<pll> g[500001];
vector<ll> dis, path;
priority_queue<pll> pq;

void dijkstra() {
    ll x, y;
    dis.resize(n + 1, INF);
    path.resize(n + 1, INF);
	dis[1] = 0;
	pq.push({0,1});
	while (!pq.empty()) {
		x = pq.top().y;
		y = -pq.top().x;
		pq.pop();
		if (dis[x] < y) continue;
		for (auto& iter : g[x]) {
			if (dis[iter.x] > iter.y + y) {
				path[iter.x] = iter.y;
				dis[iter.x] = iter.y + y;
				pq.push({-dis[iter.x],iter.x});
			}
			else if (dis[iter.x] == iter.y + y && path[iter.x] > iter.y) path[iter.x] = iter.y;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll a, b, c, i, ans = 0; cin >> n >> m;
	while (m--) {
		cin >> a >> b >> c;
        pll tmp = {b,c};
		g[a].emplace_back(tmp);
        tmp.x = a;
		g[b].emplace_back(tmp);
	}
	dijkstra();
	for (i = 2; i <= n; i++) ans += path[i];
	cout << ans;
}
