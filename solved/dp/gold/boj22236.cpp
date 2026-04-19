#include<iostream>
#define ll long long
using namespace std;

ll co[4001][4001], MOD;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll d, i, j; cin >> d >> MOD;
	co[0][0] = co[1][0] = co[1][1] = 1;
	if (d == 2) {
		cout << 1;
		return 0;
	}
	for (i = 2; i <= d; i++) {
		co[i][0] = 1;
		for (j = 1; j <= i; j++) co[i][j] = (co[i - 1][j - 1] + co[i - 1][j]) % MOD;
	}
	cout << (co[d - 2][(d - 2) / 2] - co[d - 2][(d - 2) / 2 - 1] + MOD) % MOD;
}
