#include<iostream>
#include<cstring>
using namespace std;

int n, dp[16][16][1 << 15];
char arr[16][16];

void find(int node, int pre, int visited) {
	dp[pre][node][visited] = 1;
	for (int i = 0; i < n; i++) {
		if (visited & (1 << i)) continue;
		if (arr[node][i] < arr[pre][node]) continue;
		if (dp[node][i][visited ^ (1 << i)] == -1) find(i, node, visited ^ (1 << i));
		dp[pre][node][visited] = max(dp[pre][node][visited], dp[node][i][visited ^ (1 << i)] + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) cin >> arr[i][j];
	}
	arr[0][0] = '0';
	memset(dp, -1, sizeof(dp));
	find(0, 0, 1);
	cout << dp[0][0][1];
}
