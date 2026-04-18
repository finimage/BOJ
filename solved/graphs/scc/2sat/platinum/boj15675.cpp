#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int n, m, num[4001], low[4001], cnt, cnt_, check[4001];
bool visited[4001];
char arr[1001][1001];
stack<int> st;
vector<vector<int>> g;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	st.push(ind);
	visited[ind] = 1;
	for (auto& iter : g[ind]) {
		if (!num[iter]) {
			scc(iter);
			low[ind] = min(low[ind], low[iter]);
		}
		else if(visited[iter]) low[ind] = min(low[ind], low[iter]);
	}
	if (num[ind] == low[ind]) {
		cnt_++;
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			check[k] = cnt_;
			visited[k] = 0;
			if (ind == k) break;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n >> m;
	g = vector<vector<int>>((n + m) * 2 + 1);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == '*') {
				g[i * 2 - 1].push_back((n + j) * 2);
				g[(n + j) * 2 - 1].push_back(i * 2);
				g[i * 2].push_back((n + j) * 2 - 1);
				g[(n + j) * 2].push_back(i * 2 - 1);
			}
			if (arr[i][j] == '#') {
				g[i * 2 - 1].push_back((n + j) * 2 - 1);
				g[(n + j) * 2].push_back(i * 2);
				g[i * 2].push_back((n + j) * 2);
				g[(n + j) * 2 - 1].push_back(i * 2 - 1);
			}
		}
	}
	for (i = 1; i <= (n + m) * 2; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= n + m; i++) {
		if (check[i * 2 - 1] == check[i * 2]) {
			cout << 0;
			return 0;
		}
	}
	cout << 1;
}
