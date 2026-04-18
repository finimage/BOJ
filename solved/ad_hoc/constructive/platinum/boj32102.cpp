#include<bits/stdc++.h>
#define pic pair<int, char>
#define x first
#define y second
using namespace std;

char grid[2001][2001];
pic arr[3] = {{0,'R'},{0,'G'},{0,'B'}};

int main() {
    int n, m, i, j, k; cin >> n >> m >> arr[0].x >> arr[1].x >> arr[2].x;
    sort(arr, arr + 3, greater<>());
    k = n / 2 * (m / 2) + (n + 1) / 2 * ((m + 1) / 2);
    if (arr[0].x > k) {
        cout << "NO";
        return 0;
    }
    k = 0;
    swap(arr[1], arr[2]);
    int tf = 0;
    if (n < m) {
        swap(n, m);
        tf = 1;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if ((i + j) % 2 == 0) {
                grid[i][j] = arr[k].y;
                arr[k].x--;
                if (arr[k].x == 0) k++;
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if ((i + j) % 2) {
                grid[i][j] = arr[k].y;
                arr[k].x--;
                if (arr[k].x == 0) k++;
            }
        }
    }
    cout << "YES\n";
    if (tf) {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) cout << grid[j][i];
            cout << '\n';
        }
    }
    else {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) cout << grid[i][j];
            cout << '\n';
        }
    }
}
