#include<iostream>
using namespace std;

int d[100001], h[310000];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, l, a, b, i, j, temp, time = 0, tf = 0; cin >> n >> l >> a >> b;
	for (i = 0; i < n; i++) cin >> d[i];
	for (i = 0; i < n; i++) {
		cin >> temp;
		h[d[i]] = max(h[d[i]], temp);
	}
	for (i = 0; i < l; i++) {
		tf = 0;
		for (j = i + 1; j < i + 1 + a; j++) {
			if (min(a, j - i) * b < h[j]) {
				tf = 1;
				break;
			}
		}
		if (tf) {
            cout << -1;
            return 0;
        }
		if (h[i + 1] || h[i + 2]) {
			for (j = i + 1; j < i + 1 + a; j++) h[j] = max(h[j] - b, 0);
		}
		else {
			for (j = i + 3; j < i + 3 + a; j++) {
				if (min(a, j - i - 2) * b < h[j]) {
					tf = 1;
					break;
				}
			}
			if (tf) {
				for (j = i + 1; j < i + 1 + a; j++) h[j] = max(h[j] - b, 0);
			}
			else i++;
		}
		time++;
		l++;
	}
	cout << time;
}
