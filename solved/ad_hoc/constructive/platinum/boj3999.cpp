#include<iostream>
using namespace std;

void solve() {
	int i, a, b, c, k, s = 0; cin >> a >> b >> c;
	if (c % 3 == 2) {
		k = c / 3 + 1;
		cout << s << ' ';
		for (i = 0; i < k; i++) {
			s += 3;
			cout << s << ' ';
		}
		s--;
		cout << s << ' ';
		for (i = 1; i < k; i++) {
			s -= 3;
			cout << s << ' ';
		}
		s--;
		cout << s << ' ';
		for (i = 0; i < k; i++) {
			s += 3;
			cout << s << ' ';
		}
		for (i = 3; i < a; i++) {
			s++;
			cout << s << ' ';
		}
		k = (b + 1) / 2;
		for (i = 0; i < k; i++) {
			s += 2;
			cout << s << ' ';
		}
		if (b % 2 == 1) {
			s--;
			cout << s << ' ';
			for (i = 1; i < k; i++) {
				s -= 2;
				cout << s << ' ';
			}
		}
		else {
			s++;
			cout << s << ' ';
			for (i = 0; i < k; i++) {
				s -= 2;
				cout << s << ' ';
			}
		}
	}
	else if (c % 3 == 1) {
		k = c / 3 + 1;
		cout << s << ' ';
		for (i = 0; i < k; i++) {
			s += 3;
			cout << s << ' ';
		}
		s -= 2;
		cout << s << ' ';
		for (i = 1; i < k; i++) {
			s -= 3;
			cout << s << ' ';
		}
		s++;
		cout << s << ' ';
		for (i = 1; i < k; i++) {
			s += 3;
			cout << s << ' ';
		}
		s += 2;
		cout << s << ' ';
		for (i = 2; i < a; i++) {
			s++;
			cout << s << ' ';
		}
		b -= 2;
		k = (b + 1) / 2;
		for (i = 0; i < k; i++) {
			s += 2;
			cout << s << ' ';
		}
		if (b % 2 == 1) {
			s--;
			cout << s << ' ';
			for (i = 1; i < k; i++) {
				s -= 2;
				cout << s << ' ';
			}
		}
		else {
			s++;
			cout << s << ' ';
			for (i = 0; i < k; i++) {
				s -= 2;
				cout << s << ' ';
			}
		}
	}
	else {
		if (b == 3) {
			k = c / 3;
			cout << s << ' ';
			for (i = 0; i < k; i++) {
				s += 3;
				cout << s << ' ';
			}
			s -= 2;
			cout << s << ' ';
			for (i = 1; i < k; i++) {
				s -= 3;
				cout << s << ' ';
			}
			s++;
			cout << s << ' ';
			for (i = 1; i < k; i++) {
				s += 3;
				cout << s << ' ';
			}
			s += 2;
			cout << s << ' ';
			for (i = 3; i < a; i++) {
				s++;
				cout << s << ' ';
			}
			s += 3;
			cout << s << ' ';
			s -= 2;
			cout << s << ' ';
			s++;
			cout << s << ' ';
			s += 3;
			cout << s << ' ';
			s--;
			cout << s << ' ';
		}
		else {
			k = c / 3;
			cout << s << ' ';
			for (i = 0; i < k; i++) {
				s += 3;
				cout << s << ' ';
			}
			s--;
			cout << s << ' ';
			for (i = 1; i < k; i++) {
				s -= 3;
				cout << s << ' ';
			}
			s--;
			cout << s << ' ';
			for (i = 0; i < k; i++) {
				s += 3;
				cout << s << ' ';
			}
			for (i = 3; i < a; i++) {
				s++;
				cout << s << ' ';
			}
			s += 2;
			cout << s << ' ';
			s += 2;
			cout << s << ' ';
			s -= 3;
			cout << s << ' ';
			s += 2;
			cout << s << ' ';
			s += 2;
			cout << s << ' ';
			b -= 4;
			k = (b + 1) / 2;
			for (i = 0; i < k; i++) {
				s += 2;
				cout << s << ' ';
			}
			if (b % 2 == 1) {
				s--;
				cout << s << ' ';
				for (i = 1; i < k; i++) {
					s -= 2;
					cout << s << ' ';
				}
			}
			else {
				s++;
				cout << s << ' ';
				for (i = 0; i < k; i++) {
					s -= 2;
					cout << s << ' ';
				}
			}
		}
	}
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
