#include<iostream>
#include<stack>
#include<vector>
using namespace std;

stack<int> st;
int k, n, num[10001], low[10001], cnt, cnt_, check[10001];
bool visited[10001];
vector<int> g[10001];

void input() {
	int i, a, b, c;
	char A, B, C; cin >> k >> n;
	for (i = 0; i < n; i++) {
		cin >> a >> A >> b >> B >> c >> C;
		g[a * 2 - (A == 'R' ? 0 : 1)].push_back(b * 2 - (B == 'R' ? 1 : 0));
		g[a * 2 - (A == 'R' ? 0 : 1)].push_back(c * 2 - (C == 'R' ? 1 : 0));
		g[b * 2 - (B == 'R' ? 0 : 1)].push_back(a * 2 - (A == 'R' ? 1 : 0));
		g[b * 2 - (B == 'R' ? 0 : 1)].push_back(c * 2 - (C == 'R' ? 1 : 0));
		g[c * 2 - (C == 'R' ? 0 : 1)].push_back(b * 2 - (B == 'R' ? 1 : 0));
		g[c * 2 - (C == 'R' ? 0 : 1)].push_back(a * 2 - (A == 'R' ? 1 : 0));
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
			cout << -1;
			return;
		}
	}
	for (i = 1; i <= k; i++) {
		if (check[i * 2 - 1] < check[i * 2]) cout << 'R';
		else cout << 'B';
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	SCC();
	solve();
}
