#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, m, cnt, cnt_;
vector<pii> edge;
vector<vector<int>> g, gg;
vector<int> num, low, check, visited;
vector<unordered_set<int>> ggg;
stack<int> st;

void init() {
	g.clear(); g.resize(2 * m + 2);
    gg.clear(); gg.resize(2 * m + 2);
	ggg.clear(); ggg.resize(2 * m + 2);
	num.clear(); num.resize(2 * m + 2);
	low.clear(); low.resize(2 * m + 2);
	check.clear(); check.resize(2 * m + 2);
	visited.clear(); visited.resize(2 * m + 2);
	edge.resize(m + 1);
	cnt = cnt_ = 0;
}

void scc(int ind) {
	num[ind] = low[ind] = ++cnt;
	st.push(ind);
	visited[ind] = 1;
	for (auto& iter : g[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if (visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			visited[k] = 0;
			check[k] = cnt_;
			if (k == ind) break;
		}
	}
}

void make_g() {
	for (int i = 1; i <= n; i++) {		if (gg[i].size() == 1) continue;
		for (auto& iter : gg[i]) {
			if (gg[i].size() > 2) {
				for (auto& itr : gg[i]) {
					if (iter == itr) continue;
					g[edge[iter].x == i ? 2 * iter - 1 : 2 * iter].push_back(edge[itr].x == i ? 2 * itr : 2 * itr - 1);
				}
			}
			for (auto& itr : gg[i]) {
				if (iter == itr) continue;
				int b = i, a = edge[iter].x == i ? edge[iter].y : edge[iter].x, c = edge[itr].x == i ? edge[itr].y : edge[itr].x;
				if (ggg[a].size() >= 3 || (ggg[a].size() == 2 && !ggg[a].count(c))) {
				    if (edge[iter].x == i && edge[itr].x == i) {
				        g[itr * 2 - 1].push_back(iter * 2 - 1);
				        g[iter * 2].push_back(itr * 2);
				    }
				    else if (edge[iter].x == i && edge[itr].x != i) {
				        g[iter * 2].push_back(itr * 2 - 1);
				        g[itr * 2].push_back(iter * 2 - 1);
				    }
				    else if (edge[iter].x != i && edge[itr].x == i) {
				        g[iter * 2 - 1].push_back(itr * 2);
				        g[itr * 2 - 1].push_back(iter * 2);
				    }
				    else {
				        g[iter * 2 - 1].push_back(itr * 2 - 1);
				        g[itr * 2].push_back(iter * 2);
				    }
				}
			}
		}
	}
}

void solve() {
	int i, a, b, tf = 0; cin >> n >> m;
	init();
	for (i = 1; i <= m; i++) {
		cin >> a >> b;
		edge[i] = {a,b};
		gg[a].emplace_back(i);
		gg[b].emplace_back(i);
		ggg[a].insert(b);
		ggg[b].insert(a);
	}
	make_g();
	for (i = 1; i <= 2 * m; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= m; i++) {
		if (check[2 * i - 1] == check[2 * i]) tf = 1;
	}
	if (tf) {
		cout << "-1\n";
		return;
	}
	for (i = 1; i <= m; i++) {
		if (check[2 * i - 1] < check[2 * i]) cout << "0 ";
		else cout << "1 ";
	}
	cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; cin >> T;
    while (T--) solve();
}
