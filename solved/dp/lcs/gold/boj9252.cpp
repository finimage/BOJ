#include<iostream>
using namespace std;

int dp[1001][1001];
string s1, s2;

void show(int x, int y) {
	if (!dp[x][y]) return;
	if (s1[x - 1] == s2[y - 1]) {
		show(x - 1, y - 1);
		cout << s1[x - 1];
	}
	else {
		if (dp[x - 1][y] > dp[x][y - 1]) show(x - 1, y);
		else show(x, y - 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int i, j, l1, l2, t;
	cin >> s1 >> s2;
	l1 = s1.size();
	l2 = s2.size();
	for (i = 1; i <= l1; i++) {
		for (j = 1; j <= l2; j++) {
			if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i][j]);
		}
	}
	cout << dp[l1][l2] << '\n';
	show(l1, l2);
}
