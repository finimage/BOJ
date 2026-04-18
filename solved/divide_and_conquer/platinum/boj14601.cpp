#include<iostream>
using namespace std;

int arr[(1 << 7) + 1][(1 << 7) + 1], cnt;

void rec(int k, int x, int y, int nx, int ny) {
	int n = k;
	k = (1 << k);
	if (k == 2) {
		cnt++;
		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) arr[nx + i][ny + j] = cnt;
		}
		arr[nx + x][ny + y] = -1;
		return;
	}
	if (x <= k / 2 && y <= k / 2) {
		rec(n - 1, x, y, nx, ny);
		rec(n - 1, k / 2, 1, nx, ny + k / 2);
		rec(n - 1, 1, k / 2, nx + k / 2, ny);
		rec(n - 1, 1, 1, nx + k / 2, ny + k / 2);
		cnt++;
		arr[nx + k / 2][ny + k / 2 + 1] = cnt;
		arr[nx + k / 2 + 1][ny + k / 2] = cnt;
		arr[nx + k / 2 + 1][ny + k / 2 + 1] = cnt;
	}
	else if (x <= k / 2 && y > k / 2) {
		rec(n - 1, k / 2, k / 2, nx, ny);
		rec(n - 1, x, y - k / 2, nx, ny + k / 2);
		rec(n - 1, 1, k / 2, nx + k / 2, ny);
		rec(n - 1, 1, 1, nx + k / 2, ny + k / 2);
		cnt++;
		arr[nx + k / 2][ny + k / 2] = cnt;
		arr[nx + k / 2 + 1][ny + k / 2] = cnt;
		arr[nx + k / 2 + 1][ny + k / 2 + 1] = cnt;
	}
	else if (x > k / 2 && y <= k / 2) {
		rec(n - 1, k / 2, k / 2, nx, ny);
		rec(n - 1, k / 2, 1, nx, ny + k / 2);
		rec(n - 1, x - k / 2, y, nx + k / 2, ny);
		rec(n - 1, 1, 1, nx + k / 2, ny + k / 2);
		cnt++;
		arr[nx + k / 2][ny + k / 2] = cnt;
		arr[nx + k / 2][ny + k / 2 + 1] = cnt;
		arr[nx + k / 2 + 1][ny + k / 2 + 1] = cnt;
	}
	else {
		rec(n - 1, k / 2, k / 2, nx, ny);
		rec(n - 1, k / 2, 1, nx, ny + k / 2);
		rec(n - 1, 1, k / 2, nx + k / 2, ny);
		rec(n - 1, x - k / 2, y - k / 2, nx + k / 2, ny + k / 2);
		cnt++;
		arr[nx + k / 2][ny + k / 2] = cnt;
		arr[nx + k / 2][ny + k / 2 + 1] = cnt;
		arr[nx + k / 2 + 1][ny + k / 2] = cnt;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int k, x, y, i, j; cin >> k >> y >> x;
	rec(k, x, y, 0, 0);
	for (i = (1 << k); i >= 1; i--) {
		for (j = 1; j <= (1 << k); j++) cout << arr[i][j] << ' ';
		cout << '\n';
	}
}
