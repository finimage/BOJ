#include<bits/stdc++.h>
using namespace std;

int n, scnt, ucnt, uucnt, sscnt;
string s, ans;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i; cin >> n >> s;
	for (i = n - 1; i >= 0; i--) {
		if (s[i] == 'S') {
			if (sscnt) {
				ans += 'N';
				sscnt--;
			}
			else scnt++;
		}
		if (s[i] == 'U') {
			if (uucnt) {
				ans += 'N';
				uucnt--;
			}
			else ucnt++;
		}
		if (scnt > ucnt) {
			ans += 'U';
			ans += 'N';
			scnt--;
			uucnt++;
		}
		else if (scnt < ucnt) {
			ans += 'S';
			ans += 'N';
			ucnt--;
			sscnt++;
		}
	}
	cout << ans.size() << '\n';
	cout << ans;
}
