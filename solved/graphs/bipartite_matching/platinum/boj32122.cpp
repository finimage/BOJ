#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

pii arr[10001];
int k = 1, n, grid[101][101];
int check[101][101], dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
bool visited[10001];
vector<int> ck(10001);
vector<vector<int>> g;

int dfs(int ind) {
    for (auto& iter : g[ind]) {
        if (visited[iter]) continue;
        visited[iter] = 1;
        if (!ck[iter]) {
            ck[ind] = iter;
            return ck[iter] = ind;
        }
        if (dfs(ck[iter])) {
            ck[ind] = iter;
            return ck[iter] = ind;
        }
    }
    return 0;
}

bool chk(int sz, int ii) {
    int i, cnt = 0;
    for (i = 1; i <= ii; i++) {
        if (!ck[i] && dfs(i)) memset(visited, 0, sizeof(visited));
    }
    for (i = 1; i <= ii; i++) {
        if (ck[i]) cnt++;
        //cout << ck[i] << ' ';
    }
    //cout << '\n';
    return sz <= cnt / 2;
}

void solve() {
    int i, j; cin >> n;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cin >> grid[i][j];
            arr[grid[i][j]] = {i,j};
        }
    }
    check[arr[1].x][arr[1].y] = 1;
    g.resize(n * n + 1);
    for (i = 2; i < n * n; i++) {
        check[arr[i].x][arr[i].y] = 1;
        for (j = 0; j < 4; j++) {
            int x = arr[i].x + dx[j], y = arr[i].y + dy[j];
            if (1 <= x && x <= n && 1 <= y && y <= n && check[x][y]) {
                g[grid[x][y]].emplace_back(i);
                g[i].emplace_back(grid[x][y]);
            }
        }
        if (chk(k, i)) {
            cout << i << '\n';
            k++;
        }
    }
    cout << n * n;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
#endif
    int T = 1; // cin >> T;
    while (T--) solve();
}
