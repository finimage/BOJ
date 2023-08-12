#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

stack<int> st;
vector<int> graph[51], plus_cost;
int n, num[51], low[51], cnt, cnt_, check[51], pre[51], cost[51];
bool visited[51];

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
			if (k == index) break;
		}
	}
}

void topological_sorting() {
	for (int i = 1; i <= n; i++) {
		for (auto& iter : graph[i]) {
			if (check[i] == check[iter]) continue;
			pre[check[iter]]++;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, total = 0, pre_cnt = 0; cin >> n;
	char temp;
	for (i = 1; i <= n; i++) cin >> cost[i];
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			cin >> temp;
			if (temp == 'Y') graph[i].push_back(j);
		}
	}
	for (i = 1; i <= n; i++) {
		if (!num[i]) scc(i);
	}
	topological_sorting();
	for (i = 1; i <= cnt_; i++) {
		if (!pre[i]) {
			int val = 1001, ind = 0;
			for (j = 1; j <= n; j++) {
				if (check[j] == i) {
					if (val > cost[j]) {
						val = cost[j];
						ind = j;
					}
				}
			}
			for (j = 1; j <= n; j++) {
				if (check[j] == i && ind != j) plus_cost.push_back(cost[j]);
			}
			total += val;
			pre_cnt++;
		}
		else {
			for (j = 1; j <= n; j++) {
				if (check[j] == i) plus_cost.push_back(cost[j]);
			}
		}
	}
	double ans = (double)total / pre_cnt;
	sort(plus_cost.begin(), plus_cost.end());
	for (auto& iter : plus_cost) {
		if ((double)(total + iter) / (pre_cnt + 1) < ans) {
			pre_cnt++;
			total += iter;
			ans = (double)total / pre_cnt;
		}
		else break;
	}
	printf("%0.15f", ans);
}
