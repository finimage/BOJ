#include<iostream>
#define ll long long
using namespace std;

int arr[2][10001];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	ll time = 0, temp, n, t = 1; cin >> n;
	arr[0][1] = 2 * n - 3;
	arr[0][n] = 2 * n - 2;
	arr[1][1] = 2 * n - 1;
	arr[1][n] = 2 * n;
	for (int i = 2; i <= n - 1; i++) {
		arr[0][i] = 2 * n - 2 - i;
		arr[1][i] = n - i;
	}
	temp = n * (2 * n + 1);
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= n; j++) {
			temp -= arr[i][j];
			time += temp * t;
			t++;
		}
	}
	if (n == 1) {
		cout << 2 << '\n' << 1 << '\n' << 2;
		return 0;
	}
	cout << time << '\n';
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= n; j++) cout << arr[i][j] << ' ';
		cout << '\n';
	}
}
