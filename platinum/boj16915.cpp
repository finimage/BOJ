#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int n, m, num[200001], low[200001], cnt, cnt_, check[200001];
bool state[100001], visited[100001];
vector<int> link[100001], g[200001];
stack<int> st;

void scc(int ind) {
	cnt++;
	num[ind] = low[ind] = cnt;
	visited[ind] = 1;
	st.push(ind);
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
	int i, a, b; cin >> n >> m;
	for (i = 1; i <= n; i++) cin >> state[i];
	for (i = 1; i <= m; i++) {
		cin >> a;
		while (a--) {
			cin >> b;
			link[b].push_back(i);
		}
	}
	for (i = 1; i <= n; i++) {
		a = link[i][0];
		b = link[i][1];
		if (state[i]) {
			g[a * 2].push_back(b * 2);
			g[b * 2].push_back(a * 2);
			g[a * 2 - 1].push_back(b * 2 - 1);
			g[b * 2 - 1].push_back(a * 2 - 1);
		}
		else {
			g[a * 2].push_back(b * 2 - 1);
			g[b * 2].push_back(a * 2 - 1);
			g[a * 2 - 1].push_back(b * 2);
			g[b * 2 - 1].push_back(a * 2);
		}
	}
	for (i = 1; i <= 2 * m; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= m; i++) {
		if (check[i * 2 - 1] == check[i * 2]) {
			cout << 0;
			return 0;
		}
	}
	cout << 1;
}
