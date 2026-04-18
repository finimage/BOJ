#include<iostream>
#include<vector>
#include<stack>
#include<unordered_set>
#include<queue>
using namespace std;

stack<int> st;
vector<int> graph[500001], temp;
vector<vector<int>> v;
unordered_set<int> new_graph[500001];
int N, M, S, P, num[500001], low[500001], check[500001], money[500001], pre[500001], new_money[500001], cnt, cnt_, ans;
bool visited[500001], restaurant[500001];
queue<int> q;

void input_graph() {
	int a, b;
	while (M--) {
		cin >> a >> b;
		graph[a].push_back(b);
	}
}

void scc(int index) {
	cnt++;
	num[index] = low[index] = cnt;
	visited[index] = 1;
	st.push(index);
	for (auto& iter : graph[index]) {
		if (!num[iter]) {
			scc(iter);
			low[index] = min(low[index], low[iter]);
		}
		else if(visited[iter]) low[index] = min(low[index], low[iter]);
	}
	if (num[index] == low[index]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			visited[k] = 0;
			temp.push_back(k);
			check[k] = cnt_;
			if (k == index) break;
		}
		v.push_back(temp);
		temp.clear();
	}
}

void SCC() {
	for (int i = 1; i <= N; i++) {
		if (!num[i]) scc(i);
	}
}

void make_new_graph() {
	for (int i = 0; i < cnt_; i++) {
		for (auto& itr : v[i]) {
			for (auto& iter : graph[itr]) {
				if (i + 1 == check[iter]) continue;
				if (new_graph[i + 1].count(check[iter])) continue;
				new_graph[i + 1].insert(check[iter]);
			}
		}
	}
}

void input_money() {
	int i, a;
	for (i = 1; i <= N; i++) {
		cin >> a;
		money[check[i]] += a;
	}
}

void input_restaurant() {
	int a;
	while (P--) {
		cin >> a;
		restaurant[check[a]] = 1;
	}
}

void pre_bfs() {
	q.push(check[S]);
	visited[check[S]] = 1;
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (auto& iter : new_graph[a]) {
			pre[iter]++;
			if (visited[iter]) continue;
			q.push(iter);
			visited[iter] = 1;
		}
	}
}

void bfs() {
	pre_bfs();
	q.push(check[S]);
	if (restaurant[check[S]]) ans = max(ans, money[check[S]]);
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (auto& iter : new_graph[a]) {
			pre[iter]--;
			new_money[iter] = max(new_money[iter], money[a] + money[iter]);
			if (pre[iter] == 0) {
				money[iter] = new_money[iter];
				q.push(iter);
				if (restaurant[iter]) ans = max(ans, money[iter]);
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	input_graph();
	SCC();
	make_new_graph();
	input_money();
	cin >> S >> P;
	input_restaurant();
	bfs();
	cout << ans;
}
