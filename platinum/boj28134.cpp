#include<iostream>
#include<vector>
#include<stack>
#include<unordered_set>
#define ll long long
using namespace std;

stack<int> st;
unordered_set<int> path_check[200001];
int N, child[200001], parent[200001], low[200001], num[200001], cnt, check;
bool visited[200001], cir_check[200001], tf;
vector<int> graph[200001], v;
ll ans = 9223372036854775807, ans_, p_s1[400001], p_s2[400001], p_s3[400001];

void scc(int index) {
	cnt++;
	num[index] = low[index] = cnt;
	visited[index] = 1;
	st.push(index);
	for (auto& iter : graph[index]) {
		if (path_check[index].count(iter)) continue;
		path_check[index].insert(iter);
		path_check[iter].insert(index);
		if (!num[iter]) {
			scc(iter);
			low[index] = min(low[index], low[iter]);
		}
		else if (visited[iter]) low[index] = min(low[index], low[iter]);
	}
	if (num[index] == low[index]) {
		if (st.top() == index) {
			visited[st.top()] = 0;
			st.pop();
			return;
		}
		while (!st.empty()) {
			int k = st.top();
			st.pop();
			visited[k] = 0;
			v.push_back(k);
			cir_check[k] = 1;
			if (k == index) break;
		}
	}
}

void dfs(int a) {
	visited[a] = 1;
	child[a] = 1;
	for (auto& iter : graph[a]) {
		if (visited[iter] || cir_check[iter]) continue;
		dfs(iter);
		child[a] += child[iter];
	}
	if (!cir_check[a]) ans_ += (ll)(N - child[a]) * child[a];
}

void input() {
	int i, a, b; cin >> N;
	for (i = 1; i <= N; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

void find_cir() {
	for (int i = 1; i <= N; i++) {
		if (!num[i]) scc(i);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	input();
	find_cir();
	int i, l = v.size();
	for (auto& iter : v) dfs(iter);
	for (i = 1; i <= 2 * l; i++) {
		p_s1[i] = (ll)child[v[(i - 1) % l]] + p_s1[i - 1];
		p_s2[i] = p_s1[i] + p_s2[i - 1];
		p_s3[i] = p_s1[i] * p_s1[i] + p_s3[i - 1];
	}
	for (i = 1; i <= l; i++) {
		ans = min(ans, (p_s1[i - 1] + p_s1[l + i - 1]) * (p_s2[l + i - 2] - p_s2[i - 1]) - (p_s3[l + i - 2] - p_s3[i - 1]) - (ll)(l - 1) * p_s1[i - 1] * p_s1[l + i - 1]);
	}
	cout << ans + ans_;
}
