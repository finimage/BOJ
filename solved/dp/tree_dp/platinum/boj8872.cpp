#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct info {
	int x, dis;
};

vector<info> graph[100001];
vector<int> rep;
int n, m, l, cnt, dist[2][100001], link[100001], dia = 0;
bool visited[100001];
queue<info> q;

info bfs(int ind, int tf) {
	int ans = ind, d = 0, x, dis;
	q.push({ ind,0 });
	visited[ind] = tf;
	while (!q.empty()) {
		x = q.front().x;
		dis = q.front().dis;
		q.pop();
		if (dis > d) {
			ans = x;
			d = dis;
		}
		for (auto& iter : graph[x]) {
			if (visited[iter.x] == tf) continue;
			visited[iter.x] = tf;
			dist[(tf + 1) % 2][iter.x] = dis + iter.dis;
			q.push({ iter.x,dis + iter.dis });
			if (!tf) link[iter.x] = x;
		}
	}
	return { ans,d };
}

void res(int start) {
	cnt++;
	info tem = bfs(start, 1);
	info temp = bfs(tem.x, 0);
	dia = max(dia, temp.dis);
	int k = temp.x, cmp = 1000000001, d1 = 0, d2 = 0;
	bfs(start, 1);
	while (link[k]) {
		if (cmp > max(dist[1][k], temp.dis - dist[1][k])) {
			cmp = max(dist[1][k], temp.dis - dist[1][k]);
			d1 = dist[1][k];
			d2 = temp.dis - dist[1][k];
		}
		k = link[k];
	}
	rep.push_back(max(d1, d2));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a, b, t, i; cin >> n >> m >> l;
	while (m--) {
		cin >> a >> b >> t;
		graph[a + 1].push_back({ b + 1,t });
		graph[b + 1].push_back({ a + 1,t });
	}
	for (i = 1; i <= n; i++) {
		if (visited[i]) continue;
		res(i);
	}
	if (cnt == 1) cout << dia;
	else if (cnt == 2) cout << max(rep[0] + rep[1] + l, dia);
	else {
		sort(rep.begin(), rep.end(), greater<>());
		rep[1] += l;
		rep[2] += l;
		sort(rep.begin(), rep.begin() + 3, greater<>());
		cout << max(rep[0] + rep[1], dia);
	}
}
