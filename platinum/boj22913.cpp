#include<iostream>
#define ll long long
using namespace std;

ll ans;
int check[10] = { 0, }, l;
int value[11] = { 9,8,7,6,5,4,3,2,1,0,-1 };

ll res(ll num1, ll num2, int l1, int l2) {
	int i, j;
	for (i = 0; i < 10; i++) {
		for (j = 1; j <= check[i]; j++) {
			num1 = num1 * 10 + i;
			l1--;
			if (l1 == 0) break;
		}
		if (l1 == 0) break;
	}
	for (i = 9; i >= 0; i--) {
		for (j = 1; j <= check[i]; j++) {
			num2 = num2 * 10 + i;
			l2--;
			if (l2 == 0) break;
		}
		if (l2 == 0) break;
	}
	return num1 - num2;
}

void res1(int l1, int l2, int num_check) {
	if (value[num_check] == -1) {
		int start = 0;
		if (l / 2 == l1) start = 1;
		int i, j, dif = 11;
		for (i = start; i < 9; i++) {
			for (j = i + 1; j < 10; j++) {
				if (check[i] && check[j]) dif = min(dif, j - i);
			}
		}
		for (i = start; i < 9; i++) {
			for (j = i + 1; j < 10; j++) {
				if (check[i] && check[j] && j - i == dif) {
					check[j]--;
					check[i]--;
					ans = min(ans, res(j, i, l1 - 1, l2 - 1));
					check[j]++;
					check[i]++;
				}
			}
		}
		return;
	}
	res1(l1, l2, num_check + 1);
	if (l / 2 == l1 && num_check == 9) return;
	for (int i = 2; i <= check[value[num_check]]; i += 2) {
		check[value[num_check]] -= i;
		res1(l1 - i / 2, l2 - i / 2, num_check + 1);
		check[value[num_check]] += i;
	}
}

ll res2(int l1, int l2) {
	ll num1 = 0, num2 = 0;
	int i, j;
	for (i = 1; i < 10; i++) {
		if (check[i]) break;
	}
	check[i]--;
	num1 = i;
	for (i = 0; i < 10; i++) {
		for (j = 1; j <= check[i]; j++) {
			num1 = num1 * 10 + i;
			l1--;
			if (l1 == 0) break;
		}
		if (l1 == 0) break;
	}
	for (i = 9; i >= 0; i--) {
		for (j = 1; j <= check[i]; j++) {
			num2 = num2 * 10 + i;
			l2--;
			if (l2 == 0) break;
		}
		if (l2 == 0) break;
	}
	return num1 - num2;
}

ll solve() {
	int i, tf = 1;
	string s; cin >> s;
	for (i = 0; i < 10; i++) check[i] = 0;
	l = 0;
	for (auto& iter : s) {
		l++;
		check[iter - '0']++;
	}
	if (l % 2 == 0) {
		for (i = 0; i < 10; i++) {
			if (check[i] % 2 == 1) tf = 0;
		}
		if (tf) return 0;
		ans = 9223372036854775807;
		res1(l / 2, l / 2, 0);
		return ans;
	}
	else return res2(l / 2, l / 2);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T, i; cin >> T;
	for (i = 1; i <= T; i++) cout << "Case #" << i << ": " << solve() << '\n';
}
