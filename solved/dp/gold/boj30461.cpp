#include<iostream>
using namespace std;

int arr[2001][2001][2];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, q, i, j, x, y; cin >> n >> m >> q;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			cin >> x;
			arr[i][j][0] = x + arr[i - 1][j - 1][0] + arr[i - 1][j][1];
			arr[i][j][1] = x + arr[i - 1][j][1];
		}
	}
	for (i = 0; i < q; i++) {
		cin >> x >> y;
		cout << arr[x][y][0] << '\n';
	}
}
