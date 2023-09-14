#include<iostream>
using namespace std;

char arr[101][101];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, i, j, cnt  = 0, temp; cin >> n;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) cin >> arr[i][j];
	}
	if (n <= 2) {
		cout << 0;
		return 0;
	}
	if (n == 3) {
		if (arr[1][1] == '1') cout << 1;
		else cout << 0;
		return 0;
	}
	if (arr[1][1] == '1') {
		cnt++;
		arr[2][2] = '*';
	}
	if (arr[n][n] == '1') {
		cnt++;
		arr[n - 1][n - 1] = '*';
	}
	if (arr[1][n] == '1') {
		cnt++;
		arr[2][n - 1] = '*';
	}
	if (arr[n][1] == '1') {
		cnt++;
		arr[n - 1][2] = '*';
	}
	for (i = 2; i < n - 1; i++) {
		temp = 0;
		for (j = 0; j < 3; j++) {
			if (arr[i - j + 1][2] == '*') temp++;
		}
		if (arr[i][1] - '0' > temp) {
			cnt++;
			arr[i + 1][2] = '*';
		}
		temp = 0;
		for (j = 0; j < 3; j++) {
			if (arr[2][i - j + 1] == '*') temp++;
		}
		if (arr[1][i] - '0' > temp) {
			cnt++;
			arr[2][i + 1] = '*';
		}
		temp = 0;
		for (j = 0; j < 3; j++) {
			if (arr[n - i + j][n - 1] == '*') temp++;
		}
		if (arr[n - i + 1][n] - '0' > temp) {
			cnt++;
			arr[n - i][n - 1] = '*';
		}
		temp = 0;
		for (j = 0; j < 3; j++) {
			if (arr[n - 1][n - i + j] == '*') temp++;
		}
		if (arr[n][n - i + 1] - '0' > temp) {
			cnt++;
			arr[n - 1][n - i] = '*';
		}
	}
	cout << cnt + (n - 4) * (n - 4);
}
