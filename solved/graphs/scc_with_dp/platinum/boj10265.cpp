#include<iostream>
#include<stack>
using namespace std;

stack<int> st;
int n, k, parent[1001], check[1001], dp[1001][1001], num[1001], low[1001], MAX[1001], MIN[1001], cnt, cnt_;
bool visited[1001];

void scc(int index) {
	cnt++;
	num[index] = low[index] = cnt;
	visited[index] = 1;
	st.push(index);
	if (!num[parent[index]]) {
		scc(parent[index]);
		low[index] = min(low[index], low[parent[index]]);
	}
	else if (visited[parent[index]]) low[index] = min(low[index], low[parent[index]]);
	if (num[index] == low[index]) {
		if (st.top() == index) {
			if (parent[index] == index) {
				cnt_++;
				check[index] = cnt_;
				MIN[cnt_]++;
				MAX[cnt_]++;
			}
			visited[index] = 0;
			st.pop();
		}
		else {
			cnt_++;
			while (!st.empty()) {
				int k = st.top();
				st.pop();
				check[k] = cnt_;
				visited[k] = 0;
				MIN[cnt_]++;
				MAX[cnt_]++;
				if (k == index) break;
			}
		}
	}
}

int find_(int a) {
	if (a == parent[a]) return a;
	if (check[a]) return a;
	return parent[a] = find_(parent[a]);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, t, temp; cin >> n >> k;
	for (i = 1; i <= n; i++) cin >> parent[i];
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	for (i = 1; i <= n; i++) {
		temp = find_(i);
		if (!check[i] && check[temp]) MAX[check[temp]]++;
	}
	for (i = 1; i <= cnt_; i++) {
		for (j = MIN[i]; j <= MAX[i]; j++) {
			dp[i][j] = j;
			for (t = 1; t <= k; t++) {
				dp[i][t] = max(dp[i][t], dp[i - 1][t]);
				if (t >= j) dp[i][t] = max(dp[i][t], dp[i - 1][t - j] + dp[i][j]);
			}
		}
	}
	cout << dp[cnt_][k];
}
