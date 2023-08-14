#include<iostream>
#include<queue>
using namespace std;

bool check[7];

void init() {
	for (int i = 0; i < 7; i++) check[i] = 0;
}

void solve() {
	int n, i; cin >> n;
	char a, c;
	int b, d, x;
	queue<int> q[2];
	q[0].push(1);
	for (i = 0; i < n; i++) {
		cin >> a >> b >> c >> d;
		init();
		while (!q[i % 2].empty()) {
			x = q[i % 2].front();
			q[i % 2].pop();
			if (a == '+') {
				if (!check[(x + b) % 7]) {
					check[(x + b) % 7] = 1;
					q[(i + 1) % 2].push((x + b) % 7);
				}
			}
			else {
				if (!check[(x * b) % 7]) {
					check[(x * b) % 7] = 1;
					q[(i + 1) % 2].push((x * b) % 7);
				}
			}
			if (c == '+') {
				if (!check[(x + d) % 7]) {
					check[(x + d) % 7] = 1;
					q[(i + 1) % 2].push((x + d) % 7);
				}
			}
			else {
				if (!check[(x * d) % 7]) {
					check[(x * d) % 7] = 1;
					q[(i + 1) % 2].push((x * d) % 7);
				}
			}

		}
	}
	cout << (check[0] ? "LUCKY\n" : "UNLUCKY\n");
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
}
