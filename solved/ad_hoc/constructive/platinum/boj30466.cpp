#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

ll n, ans, k, cntcnt;
vector<pii> v;
vector<int> arr;
vector<vector<int>> g;
queue<int> q;

void bfs(int start) {
    arr.resize(n + 1);
    q.push(start);
    int cnt = 1;
    while (!q.empty()) {
        int a = q.front();
        arr[a] = cnt++;
        q.pop();
        for (auto& iter : g[a]) q.push(iter);
    }
}

void dfs(int ind) {
    cntcnt++;
    ans += abs(arr[ind] - cntcnt);
    for (auto& iter : g[ind]) dfs(iter);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, j, tmp, a = 1; cin >> n;
    g.resize(n + 1);
    tmp = n - 1;
    for (i = 2; i <= n; i++) {
        k = (tmp - 1) / 2;
        for (j = i; j <= i + k; j++) {
            v.push_back({a,j});
            g[a].push_back(j);
        }
        tmp -= k + 1;
        a = i;
        i += k;
    }
    bfs(1);
    dfs(1);
    cout << ans << '\n';
    for (auto& iter : v) cout << iter.x << ' ' << iter.y << '\n';
}
