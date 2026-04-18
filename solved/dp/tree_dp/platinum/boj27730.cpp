#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

int n[2], node[2], cnt[100001][2];
ll val[100001][2], Min[2];
vector<vector<pii>> g[2];

void dfs(int ind, int pre, int k) {
    cnt[ind][k] = 1;
    for (auto& iter : g[k][ind]) {
        if (iter.x == pre) continue;
        dfs(iter.x, ind, k);
        val[ind][k] += val[iter.x][k] + (ll)iter.y * cnt[iter.x][k];
        cnt[ind][k] += cnt[iter.x][k];
    }
}

void find_(int ind, int pre, int k, ll c) {
    for (auto& iter : g[k][ind]) {
        if (iter.x == pre) continue;
        ll tmp = val[1][k] + (ll)iter.y * (n[k] - 2 * cnt[iter.x][k]) + c;
        if (Min[k] > tmp) {
            Min[k] = tmp;
            node[k] = iter.x;
        }
        find_(iter.x, ind, k, c + (ll)iter.y * (n[k] - 2 * cnt[iter.x][k]));
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, a, b, c;
    for (i = 0; i < 2; i++) {
        cin >> n[i];
        g[i].resize(n[i] + 1);
        for (j = 1; j < n[i]; j++) {
            cin >> a >> b >> c;
            g[i][a].push_back({b,c});
            g[i][b].push_back({a,c});
        }
        dfs(1, 0, i);
        Min[i] = val[1][i];
        node[i] = 1;
        find_(1, 0, i, 0);
    }
    cout << node[0] << ' ' << node[1] << '\n' << Min[1] * n[0] + Min[0] * n[1] + (ll)n[0] * n[1];
}
