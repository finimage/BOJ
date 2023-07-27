#include<iostream>
#include<stack>
#include<vector>
using namespace std;

stack<int> st;
vector<int> graph[20001];
int n, m, num[20001], low[20001], check[20001], cnt, cnt_;
bool visited[20001];

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
			check[k] = cnt_;
			visited[k] = 0;
			if (index == k) break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, a, b, tf = 1; cin >> n >> m;
	for (i = 0; i < m; i++) {
		cin >> a >> b;
		graph[((a > 0) ? 10000 + a : -a)].push_back(((b > 0) ? b : 10000 - b));
		graph[((b > 0) ? 10000 + b : -b)].push_back(((a > 0) ? a : 10000 - a));
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 10001; i <= n + 10000; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= n; i++) {
		if (check[i] == check[10000 + i]) {
			tf = 0;
			break;
		}
	}
	cout << tf;
}
