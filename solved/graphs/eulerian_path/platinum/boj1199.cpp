#include<iostream>
#include<stack>
using namespace std;

int n, arr[1001][1001], check[1001], plus_;
stack<int> graph[1001];

void euler(int node) {
	while (!graph[node].empty()) {
		int k = graph[node].top();
		graph[node].pop();
		if (arr[node][k]) {
			arr[node][k]--;
			arr[k][node]--;
			euler(k);
		}
	}
	cout << node << ' ';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, tf = 0, a; cin >> n;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			cin >> a;
			arr[i][j] = a;
			check[i] += arr[i][j];
			while (a--) graph[i].push(j);
		}
		if (check[i] % 2 == 1) tf = 1;
	}
	if (tf) cout << -1;
	else euler(1);
}
