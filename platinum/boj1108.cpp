#include<iostream>
#include<unordered_map>
#include<vector>
#include<stack>
#include<queue>
#define ll long long
using namespace std;

ll grade[2501];
int n, num[2501], low[2501], check[2501], pre[2501], cnt, cnt_;
bool visited[2501];
stack<int> st;
unordered_map<string, int> um;
vector<int> graph[2501], new_graph[2501];
queue<int> q;

void scc(int index) {
	cnt++;
	num[index] = low[index] = cnt;
	st.push(index);
	visited[index] = 1;
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
			check[k] = cnt_;
			visited[k] = 0;
			if (k == index) break;
		}
	}
}

void make_new_graph(int count) {
	for (int i = 1; i <= count; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			pre[iter]++;
			new_graph[i].push_back(iter);
		}
	}
}

void bfs(int count) {
	int i, a;
	for (i = 1; i <= count; i++) {
		if (pre[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		a = q.front();
		q.pop();
		for (auto& iter : new_graph[a]) {
			pre[iter]--;
			grade[iter] += grade[a];
			if (pre[iter] == 0) q.push(iter);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, a, count = 0; cin >> n;
	string s1, s2;
	for (i = 0; i < n; i++) {
		cin >> s1 >> a;
		if (!um.count(s1)) {
			count++;
			um[s1] = count;
		}
		for (j = 0; j < a; j++) {
			cin >> s2;
			if (!um.count(s2)) {
				count++;
				um[s2] = count;
			}
			graph[um[s2]].push_back(um[s1]);
		}
	}
	for (i = 1; i <= count; i++) {
		if (!num[i]) scc(i);
		grade[i] = 1;
	}
	make_new_graph(count);
	bfs(count);
	cin >> s1;
	cout << grade[um[s1]];
}
