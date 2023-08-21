#include<iostream>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, t, i, a, b; cin >> n >> t;
	if (t == 0) {
		if (n % 2 == 0) {
			cout << "! " << n / 2 << endl;
			for (i = 0; i < n / 2; i++) {
				cin >> a >> b;
				cout << b << ' ' << a << endl;
			}
		}
		else {
			cout << "! " << n / 2 + 1 << endl;
			for (i = 0; i < n / 2; i++) {
				cin >> a >> b;
				cout << b << ' ' << a << endl;
			}
			cin >> a >> b;
		}
	}
	else {
		if (n % 2 == 0) {
			cout << "! " <<  n / 2 + 1 << endl;
			cout << 1 << ' ' << 1 << endl;
			for (i = 1; i < n / 2; i++) {
				cin >> a >> b;
				cout << b << ' ' << a << endl;
			}
			cin >> a >> b;
		}
		else {
			cout << "! " << n / 2 + 1 << endl;
			for (i = 0; i < n / 2; i++) {
				cin >> a >> b;
				cout << b << ' ' << a << endl;
			}
		}
	}
}
