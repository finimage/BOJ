#include<iostream>
#include<vector>
#include<queue>
using namespace std;

string ans;
int n, m, dis[1000001];
char S, E, alp[1000001], next_[1000001];
vector<int> graph[1000001], new_graph[1000001];
queue<int> Q, q[2];
bool visited[1000001];

void bfs1() {
	int a, tf = 0, dist = 0;
	while (!Q.empty()) {
		a = Q.front();
		Q.pop();
		if (tf) {
			if (dist < dis[a]) break;
			if (dist == dis[a] && alp[a] == S) {
				q[0].push(a);
				visited[a] = 1;
			}
			continue;
		}
		if (alp[a] == S) {
			tf = 1;
			dist = dis[a];
			q[0].push(a);
			visited[a] = 1;
			continue;
		}
		for (auto& iter : graph[a]) {
			if (dis[iter] > dis[a] + 1) {
				dis[iter] = dis[a] + 1;
				next_[iter] = alp[a];
				new_graph[iter].push_back(a);
				Q.push(iter);
			}
			else if (dis[iter] == dis[a] + 1) {
				if (next_[iter] > alp[a]) {
					next_[iter] = alp[a];
					new_graph[iter].clear();
					new_graph[iter].push_back(a);
				}
				else if (next_[iter] == alp[a]) new_graph[iter].push_back(a);
			}
		}
	}
}

void bfs2() {
	int dist = dis[q[0].front()] + 1, a;
	char cmp = S;
	while (dist--) {
		ans += cmp;
		cmp = 'Z' + 1;
		while (!q[0].empty()) {
			a = q[0].front();
			cmp = min(cmp, next_[a]);
			if (cmp == next_[a]) {
				for (auto& iter : new_graph[a]) {
					if (visited[iter]) continue;
					visited[iter] = 1;
					q[1].push(iter);
				}
			}
			q[0].pop();
		}
		while (!q[1].empty()) {
			a = q[1].front();
			if (cmp == alp[a]) q[0].push(a);
			q[1].pop();
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b; cin >> n >> m >> S >> E;
	for (i = 1; i <= n; i++) {
		cin >> alp[i];
		dis[i] = 1000001;
	}
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
		if (alp[a] == E) {
			Q.push(a);
			dis[a] = 0;
		}
		if (alp[b] == E) {
			Q.push(b);
			dis[b] = 0;
		}
	}
	bfs1();
	if (q[0].empty()) {
		cout << "Aaak!";
		return 0;
	}
	bfs2();
	cout << ans;
}
