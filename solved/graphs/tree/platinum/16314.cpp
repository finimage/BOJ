#include<iostream>
#include<vector>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n, h, degree[100001];
vector<int> g[100001], d1[100001], temp;
vector<pii> v;

void dfs(int node, int pre) {
	if (degree[node] == 1) {
		d1[pre].push_back(node);
		return;
	}
	for (auto& iter : g[node]) {
		if (iter == pre) continue;
		dfs(iter, node);
		if (d1[node].size() >= 3) {
			v.push_back({ d1[node][0],d1[node].back() });
			for (int i = 1; i + 1 < d1[node].size(); i++) temp.push_back(d1[node][i]);
			d1[node] = temp;
			temp.clear();
		}
	}
	for (auto& iter : d1[node]) d1[pre].push_back(iter);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, root; cin >> n >> h;
	for (i = 1; i < n; i++) {
		cin >> a >> b;
		a++;
		b++;
		g[a].push_back(b);
		g[b].push_back(a);
		degree[a]++;
		degree[b]++;
        if (degree[a] >= 2) root = a;
        if (degree[b] >= 2) root = b;
	}
	if (n == 2) {
		cout << "1\n0 1";
		return 0;
	}
	dfs(root, 0);
	if (d1[0].size() == 2) v.push_back({ d1[0][0],d1[0][1] });
	else v.push_back({ root,d1[0][0] });
	cout << v.size() << '\n';
	for (auto& iter : v) cout << iter.x - 1 << ' ' << iter.y - 1 << '\n';
}
