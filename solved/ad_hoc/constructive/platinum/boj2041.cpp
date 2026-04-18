#include<bits/stdc++.h>
using namespace std;

int n, m, g[1005][1005];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int x = 1, y = 1, st = 1; cin >> n >> m;
    g[1][1] = 1;
    if (n == 1 && m == 1) {
        cout << 1;
        return 0;
    }
    while (1) {
        if ((x + y) % 2) {
            while (y > 1 && x < n) {
                x++;
                y--;
                g[x][y] = g[x - 1][y + 1] + 1;
                if (g[x][y - 1]) st++;
                if (g[x - 1][y]) st++;
            }
            if (x == n) {
                y++;
                g[x][y] = g[x][y - 1] + st;
                if (g[x][y - 1]) st++;
                if (g[x - 1][y]) st++;
            }
            else {
                x++;
                g[x][y] = g[x - 1][y] + st;
                if (g[x][y - 1]) st++;
                if (g[x - 1][y]) st++;
            }
        }
        else {
            while (x > 1 && y < m) {
                x--;
                y++;
                g[x][y] = g[x + 1][y - 1] + 1;
                if (g[x][y - 1]) st++;
                if (g[x - 1][y]) st++;
            }
            if (y == m) {
                x++;
                g[x][y] = g[x - 1][y] + st;
                if (g[x][y - 1]) st++;
                if (g[x - 1][y]) st++;
            }
            else {
                y++;
                g[x][y] = g[x][y - 1] + st;
                if (g[x][y - 1]) st++;
                if (g[x - 1][y]) st++;
            }
        }
        if (x == n && y== m) break;
    }
    for (x = 1; x <= n; x++) {
        for (y = 1; y <= m; y++) cout << g[x][y] << ' ';
        cout << '\n';
    }
}
