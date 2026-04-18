#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

int k, n, m, tf;
char grid[101][101];
pii box;
string order;
int dx[4] = {1,0,0,-1}, dy[4] = {0,1,-1,0};
int moving[100][100][4][4][10][10];

int mapping(char c) {
    if (c == 'L') return 0;
    if (c == 'R') return 1;
    if (c == 'U') return 2;
    return 3;
}

bool check(int x, int y, int a, int b) {
    if (x <= a && a < x + k && y <= b && b < y + k) return 1;
    return 0;
}

void bfs(int x, int y, int z, int a, int b) {
    queue<pii> q;
    q.push({a,b});
    vector<vector<int>> visited(n + 1, vector<int>(n + 1));
    visited[a][b] = 1;
    int i;
    while (!q.empty()) {
        int a_ = q.front().x;
        int b_ = q.front().y;
        q.pop();
        for (i = 0; i < 4; i++) {
            int na = a_ + dx[i];
            int nb = b_ + dy[i];
            if (check(x, y, na, nb)) {
                if (grid[na][nb] == 'w') {
                    if (visited[na][nb]) continue;
                    visited[na][nb] = visited[a_][b_] + 1;
                    q.push({na,nb});
                }
            }
        }
    }
    for (i = y; i < y + k; i++) {
        int na = x - 1, nb = i;
        if (na > 0 && grid[na][nb] == 'w' && visited[na + 1][nb]) {
            if (moving[x][y][z][2][z < 2 ? a - x : b - y][i - y]) moving[x][y][z][2][z < 2 ? a - x : b - y][i - y] = min(moving[x][y][z][2][z < 2 ? a - x : b - y][i - y], visited[na + 1][nb]);
            else moving[x][y][z][2][z < 2 ? a - x : b - y][i - y] = visited[na + 1][nb];
        }
        na = x + k;
        if (na <= n && grid[na][nb] == 'w' && visited[na - 1][nb]) {
            if (moving[x][y][z][3][z < 2 ? a - x : b - y][i - y]) moving[x][y][z][3][z < 2 ? a - x : b - y][i - y] = min(moving[x][y][z][3][z < 2 ? a - x : b - y][i - y], visited[na - 1][nb]);
            else moving[x][y][z][3][z < 2 ? a - x : b - y][i - y] = visited[na - 1][nb];
        }
    }
    for (i = x; i < x + k; i++) {
        int na = i, nb = y - 1;
        if (nb > 0 && grid[na][nb] == 'w' && visited[na][nb + 1]) {
            if (moving[x][y][z][0][z < 2 ? a - x : b - y][i - x]) moving[x][y][z][0][z < 2 ? a - x : b - y][i - x] = min(moving[x][y][z][0][z < 2 ? a - x : b - y][i - x], visited[na][nb + 1]);
            else moving[x][y][z][0][z < 2 ? a - x : b - y][i - x] = visited[na][nb + 1];
        }
        nb = y + k;
        if (nb <= n && grid[na][nb] == 'w' && visited[na][nb - 1]) {
            if (moving[x][y][z][1][z < 2 ? a - x : b - y][i - x]) moving[x][y][z][1][z < 2 ? a - x : b - y][i - x] = min(moving[x][y][z][1][z < 2 ? a - x : b - y][i - x], visited[na][nb - 1]);
            else moving[x][y][z][1][z < 2 ? a - x : b - y][i - x] = visited[na][nb - 1];
        }
    }
    visited.clear();
}

void ckck(int x, int y, int z) {
    int i;
    if (z == 0) {
        for (i = x; i < x + k; i++) {
            if (grid[i][y] == 'w') bfs(x, y, z, i, y);
        }
    }
    else if (z == 1) {
        for (i = x; i < x + k; i++) {
            if (grid[i][y + k - 1] == 'w') bfs(x, y, z, i, y + k - 1);
        }
    }
    else if (z == 2) {
        for (i = y; i < y + k; i++) {
            if (grid[x][i] == 'w') bfs(x, y, z, x, i);
        }
    }
    else {
        for (i = y; i < y + k; i++) {
            if (grid[x + k - 1][i] == 'w') bfs(x, y, z, x + k - 1, i);
        }
    }
}

void pre() {
    int i, j, t;
    int x = box.x, y = box.y;
    bool visited[101][101][4];
    if (order[0] == 'L') visited[x][y][0] = 1;
    else if (order[0] == 'R') visited[x][y][1] = 1;
    else if (order[0] == 'U') visited[x][y][2] = 1;
    else visited[x][y][3] = 1;
    for (i = 0; i < m; i++) {
        if (order[i] == 'L') visited[x][--y][0] = 1;
        else if (order[i] == 'R') visited[x][++y][1] = 1;
        else if (order[i] == 'U') visited[--x][y][2] = 1;
        else visited[++x][y][3] = 1;
    }
    for (i = 1; i <= n - k + 1; i++) {
        for (j = 1; j <= n - k + 1; j++) {
            for (t = 0; t < 4; t++) {
                if (visited[i][j][t]) ckck(i, j, t);
            }
        }
    }
}

void solve() {
    int i, j, t; cin >> n >> k;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) cin >> grid[i][j];
    }
    cin >> box.x >> box.y >> m >> order;
    pre();
    vector<int> v[2];
    char pre = order[0];
    v[1].resize(k);
    for (i = 1; i <= m; i++) {
        v[0].clear();
        v[0].resize(k, 1e9);
        int a = mapping(pre), b = mapping(order[i - 1]);
        for (j = 0; j < k; j++) {
            if (v[1][j] == 1e9) continue;
            for (t = 0; t < k; t++) {
                if (moving[box.x][box.y][a][b][j][t]) {
                    v[0][t] = min(v[0][t], v[1][j] + moving[box.x][box.y][a][b][j][t]);
                }
            }
        }
        if (b == 0) box.y--;
        else if (b == 1) box.y++;
        else if (b == 2) box.x--;
        else box.x++;
        v[1] = v[0];
        pre = order[i - 1];
    }
    int ans = 1e9;
    for (i = 0; i < k; i++) ans = min(ans, v[1][i]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; //cin >> T;
    while (T--) solve();
}
