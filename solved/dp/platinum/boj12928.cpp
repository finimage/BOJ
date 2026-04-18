#include<bits/stdc++.h>
using namespace std;

int n, s, dp[51][2001];
vector<int> tree[2001][2];

int cal(vector<int>& v) {
	int res = 0;
	for (auto& iter : v) res += (iter - 1) * iter / 2;
	return res;
}

void make_tree(vector<int>& v) {
	int i, l = v.size();
	for (i = 0; i < l; i++) {
		if (i == 0 || v[i - 1] != v[i]) {
			v[i]++;
			int val = cal(v);
			tree[val][1] = v;
			dp[l][val] = 1;
			v[i]--;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j; cin >> n >> s;
	tree[1][0] = {2,1,1};
	dp[3][1] = 1;
	for (i = 3; i < n; i++) {
		for (j = 1; j <= (i - 1) * (i - 2) / 2; j++) {
			if (dp[i][j]) {
				tree[j][0].push_back(1);
				make_tree(tree[j][0]);
			}
		}
		for (j = 1; j <= i * (i - 1) / 2; j++) tree[j][0] = tree[j][1];
	}
	cout << dp[n][s];
}
