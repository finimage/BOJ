#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct info {
	int x, count;
};

vector<int> graph[100001], route[100001];
int ans = -1, tf, start_, end_, cnt[100001];
bool visited[2][100001];
queue<info> q;

int bfs() {
	int tf = 0, ans = -1, a, count;
	q.push({ start_, 0 });
	visited[0][start_] = 1;
	while (!q.empty()) {
		a = q.front().x;
		count = q.front().count;
		q.pop();
		for (auto& itr : graph[a]) {
			if (visited[1][itr]) continue;
			visited[1][itr] = 1;
			for (auto& iter : route[itr]) {
				if (visited[0][iter]) continue;
				visited[0][iter] = 1;
				if (iter == end_) {
					ans = count;
					tf = 1;
					break;
				}
				if (cnt[iter] > 1) q.push({ iter,count + 1 });
			}
			if (tf) break;
		}
		if (tf) break;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m, i, a; cin >> n >> m;
	for (i = 1; i <= m; i++) {
		while (1) {
			cin >> a;
			if (a == -1) break;
			route[i].push_back(a);
			graph[a].push_back(i);
			cnt[a]++;
		}
	}
	cin >> start_ >> end_;
	if (start_ == end_) {
		cout << 0;
		return 0;
	}
	cout << bfs();
}
