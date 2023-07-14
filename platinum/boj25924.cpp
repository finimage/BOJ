#include<iostream>
#include<vector>
using namespace std;

vector<int> graph[500001], ans;
int dis[500001], point[2], comp;
bool visited[500001], path[500001];

void dfs(int start, int cnt, int check) {
	dis[start] = cnt;
	if (comp < cnt) {
		comp = cnt;
		point[check] = start;
	}
	visited[start] = 1;
	for (auto iter = graph[start].begin(); iter != graph[start].end(); iter++) {
		if (visited[*iter]) continue;
		dfs(*iter, cnt + 1, check);
	}
	visited[start] = 0;
}

void find_path(int start, int end) {
	if (start == end) {
		path[start] = 1;
		return;
	}
	visited[start] = 1;
	for (auto iter = graph[start].begin(); iter != graph[start].end(); iter++) {
		if (visited[*iter]) continue;
		find_path(*iter, end);
		if (path[*iter]) path[start] = 1;
	}
	visited[start] = 0;
}

void ans1(int start, int cnt) {
	cout << start << '\n';
	if (cnt == 0) return;
	visited[start] = 1;
	for (auto iter = graph[start].begin(); iter != graph[start].end(); iter++) {
		if (visited[*iter]) continue;
		if (path[*iter]) ans1(*iter, cnt - 1);
	}
	visited[start] = 0;
}

void ans2(int start) {
	ans.push_back(start);
	if (!path[start]) comp--;
	int next = -1;
	visited[start] = 1;
	for (auto iter = graph[start].begin(); iter != graph[start].end(); iter++) {
		if (visited[*iter]) continue;
		if (!path[*iter] && comp) {
			ans2(*iter);
			ans.push_back(start);
		}
		if (path[*iter]) next = *iter;
	}
	if (next != -1) ans2(next);
	visited[start] = 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int N, K, i, a, b; cin >> N >> K;
	for (i = 1; i < N; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1,0,0);
	comp = 0;
	dfs(point[0], 0, 1);//지름 양 끝점
	find_path(point[0], point[1]);
	if (K <= dis[point[1]]) {
		cout << K + 1 << '\n' << K << '\n';
		ans1(point[0], K);
	}
	else {
		comp = (K - dis[point[1]]) / 2;
		ans2(point[0]);
		int l = ans.size();
		cout << dis[point[1]] + 1 + (l - dis[point[1]] - 1) / 2 << '\n' << l - 1 << '\n';
		for (auto iter = ans.begin(); iter != ans.end(); iter++) cout << *iter << '\n';
	}
}
