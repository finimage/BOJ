#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
#define ll long long
#define INF 998244353
using namespace std;

struct info {
	int x;
	ll dis;
};

struct cmp {
	bool operator()(const info& a, const info& b) {
		return a.dis > b.dis;
	}
};
queue<int> q;
vector<info> graph[100001];
vector<vector<int>> v;
priority_queue<info, vector<info>, cmp> pq;
unordered_map<int, info> new_graph[100001];
unordered_map<int, int> path_check[100001];
vector<int> temp;
vector<int> arr[100001];
stack<int> st;
bool visited[100001], cir_check[100001];
int N, M, check[100001], low[100001], num[100001], pre[100001], cnt, cnt_;
ll dis[100001], path_count[100001];

void SCC(int index) {
	cnt++;
	low[index] = num[index] = cnt;
	visited[index] = 1;
	st.push(index);
	for (auto& iter : graph[index]) {
		if (iter.dis > 0) continue;
		if (!num[iter.x]) {
			SCC(iter.x);
			low[index] = min(low[index], low[iter.x]);
		}
		else if (visited[iter.x]) low[index] = min(low[index], low[iter.x]);
	}
	if (low[index] == num[index]) {
		cnt_++;
		if (st.top() != index) {
			path_count[cnt_] = INF;
			cir_check[cnt_] = 1;
		}
		while (!st.empty()) {
			int k = st.top();
			check[k] = cnt_;
			visited[k] = 0;
			temp.push_back(k);
			st.pop();
			if (index == k) break;
		}
		v.push_back(temp);
		temp.clear();
	}
}

void make_new_graph() {
	for (int i = 0; i < cnt_; i++) {
		for (auto& itr : v[i]) {
			int k = check[itr];
			for (auto& iter : graph[itr]) {
				if (check[iter.x] == k) continue;
				if (new_graph[k].count(check[iter.x])) {
					if (new_graph[k][check[iter.x]].dis > iter.dis) {
						new_graph[k][check[iter.x]].x = 1;
						new_graph[k][check[iter.x]].dis = iter.dis;
					}
					else if (new_graph[k][check[iter.x]].dis == iter.dis) new_graph[k][check[iter.x]].x++;
				}
				else new_graph[k][check[iter.x]] = { 1,iter.dis };
			}
		}
	}
}

void init() {
	for (int i = 0; i <= N; i++) dis[i] = 200000000000001;
}

void bfs() {
	int x;
	q.push(check[1]);
	path_count[check[1]] = 1;
	while (!q.empty()) {
		x = q.front();
		q.pop();
		for (auto& iter : new_graph[x]) {
			if (!path_check[iter.first].count(x)) continue;
			pre[iter.first]--;
			if (path_count[x] == INF) path_count[iter.first] = INF;
			else if (path_count[iter.first] != INF) {
				path_count[iter.first] += iter.second.x % INF * path_count[x] % INF;
				path_count[iter.first] %= INF;
			}
			if (pre[iter.first] == 0) q.push(iter.first);
		}
	}
}

void ans() {
	for (int i = 1; i <= N; i++) {
		if (path_count[check[i]] == INF) cout << "-1\n";
		else cout << path_count[check[i]] << '\n';
	}
}

void dijkstra() {
	if (path_count[check[1]] == INF) {
		for (int i = 0; i < N; i++) cout << "-1\n";
		return;
	}
	init();
	pq.push({ check[1],0 });
	dis[check[1]] = 0;
	int x;
	ll dist;
	while (!pq.empty()) {
		x = pq.top().x;
		dist = pq.top().dis;
		pq.pop();
		if (dist > dis[x]) continue;
		for (auto& iter : new_graph[x]) {
			if (dis[iter.first] > iter.second.dis + dist) {
				dis[iter.first] = iter.second.dis + dist;
				pre[iter.first] = 1;
				arr[iter.first].clear();
				arr[iter.first].push_back(x);
				path_check[iter.first].clear();
				path_check[iter.first][x] = 1;
				pq.push({ iter.first, dis[iter.first] });
			}
			else if (dis[iter.first] == iter.second.dis + dist) {
				if (!path_check[iter.first].count(x)) {
					pre[iter.first]++;
					arr[iter.first].push_back(x);
					path_check[iter.first][x] = 1;
				}
			}
		}
	}
	bfs();
	ans();
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int a, b, i; cin >> N >> M;
	ll c;
	while (M--) {
		cin >> a >> b >> c;
		graph[a].push_back({ b,c });
	}
	for (i = 1; i <= N; i++) {
		if (!num[i]) SCC(i);
	}
	make_new_graph();
	dijkstra();
}
