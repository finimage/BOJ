#include<iostream>
#include<stack>
#include<vector>
using namespace std;

stack<int> st;
int k, n, num[20001], low[20001], cnt, cnt_, check[20001];
bool visited[20001];
vector<int> g[20001];

void input() {
	int i, a, b; cin >> k >> n;
	for (i = 0; i < n; i++) {
		cin >> a >> b;
		g[abs(a) * 2 - (a > 0 ? 1 : 0)].push_back(abs(b) * 2 - (b > 0 ? 0 : 1));
		g[abs(b) * 2 - (b > 0 ? 1 : 0)].push_back(abs(a) * 2 - (a > 0 ? 0 : 1));
	}
}

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
			int K = st.top();
			st.pop();
			check[K] = cnt_;
			visited[K] = 0;
			if (ind == K) break;
		}
	}
}

void SCC() {
	for (int i = 1; i <= 2 * k; i++) {
		if (!num[i]) scc(i);
	}
}

void solve() {
	int i;
	for (i = 1; i <= k; i++) {
		if (check[i * 2 - 1] == check[i * 2]) {
			cout << 0;
			return;
		}
	}
	cout << 1 << '\n';
	for (i = 1; i <= k; i++) {
		if (check[i * 2 - 1] < check[i * 2]) cout << 0 << ' ';
		else cout << 1 << ' ';
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	SCC();
	solve();
}
