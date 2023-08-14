#include<iostream>
using namespace std;

char arr[10001][501];
bool visited[10001][501];
int r, c;

int dfs(int row, int col) {
	visited[row][col] = 1;
    if (col == c - 1) return 1;
	if (0 <= row - 1 && arr[row - 1][col + 1] == '.') {
		if (!visited[row - 1][col + 1] && dfs(row - 1, col + 1) == 1) return 1;
	}
	if (arr[row][col + 1] == '.') {
		if (!visited[row][col + 1] && dfs(row, col + 1) == 1) return 1;
	}
	if (row + 1 < r && arr[row + 1][col + 1] == '.') {
		if (!visited[row + 1][col + 1] && dfs(row + 1, col + 1) == 1) return 1;
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int i, j, total = 0; cin >> r >> c;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) cin >> arr[i][j];
	}
	for (i = 0; i < r; i++) {
		if (arr[i][0] == '.') total += dfs(i, 0);
	}
	cout << total;
}
