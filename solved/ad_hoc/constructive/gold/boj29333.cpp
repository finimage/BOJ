#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>
#define x first
#define y second
using namespace std;

int n, m, s, e, ans[300001], link[200001], num[200001];
vector<pair<int, int>> graph[200001], v;
bool visited[200001];
queue<int> q;
unordered_set<int> us;

bool bfs() {
	q.push(s);
	visited[s] = 1;
	int a, tf = 0;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		if (a == e) {
			tf = 1;
			break;
		}
		for (auto& iter : graph[a]) {
			if (visited[iter.x]) continue;
			link[iter.x] = a;
			visited[iter.x] = 1;
			num[iter.x] = iter.y;
			q.push({ iter.x });
		}
	}
	return tf;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> s >> e;
	v = vector<pair<int, int>>(m);
	for (int i = 0; i < m; i++) {
		cin >> v[i].x >> v[i].y;
		graph[v[i].x].push_back({ v[i].y,i });
		graph[v[i].y].push_back({ v[i].x,i });
	}
	if (bfs()) {
		int k = e;
		while (link[k]) {
			for (auto& iter : graph[k]) {
				if (us.count(iter.x)) continue;
				if (v[iter.y].x == k) ans[iter.y] = 1;
			}
			if (v[num[k]].x == k) ans[num[k]] = 1;
			else ans[num[k]] = 0;
			us.insert(k);
			k = link[k];
		}
		for (auto& iter : graph[s]) {
			if (us.count(iter.x)) continue;
			if (v[iter.y].x == s) ans[iter.y] = 1;
		}
		for (int i = 0; i < m; i++) cout << ans[i] << ' ';
	}
	else cout << -1;
}
