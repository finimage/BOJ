#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define pii pair<int, int>
#define x first
#define y second
using namespace std;

bool cmp(pii a, pii b) {
    return a.y < b.y;
}

int n, m, k, num[200001], stsize[200001], tree[800004], cnt;
ll ans;
vector<vector<int>> g;
vector<pii> q, v;

void dfs(int ind, int pre) {
    num[ind] = ++cnt;
    stsize[ind]++;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs(iter, ind);
        stsize[ind] += stsize[iter];
    }
}

int update(int start, int end, int ind, int i) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = 1;
    int mid = (start + end) / 2;
    return tree[ind] = update(start, mid, ind * 2, i) + update(mid + 1, end, ind * 2 + 1, i);
}

int res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    return res(start, mid, ind * 2, le, ri) + res(mid + 1, end, ind * 2 + 1, le, ri);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b, c; cin >> n >> m >> c;
    v.resize(n);
    for (i = 0; i < n; i++) {
        cin >> v[i].y;
        v[i].x = i + 1;
    }
    sort(v.begin(), v.end(), cmp);
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs(1, 0);
    q.resize(m);
    for (i = 0; i < m; i++) cin >> q[i].x >> q[i].y;
    sort(q.begin(), q.end(), cmp);
    for (auto& iter : q) {
        while (k < n && v[k].y <= iter.y) {
            update(1, n, 1, num[v[k].x]);
            k++;
        }
        ans += res(1, n, 1, num[iter.x], num[iter.x] + stsize[iter.x] - 1);
        ans %= MOD;
    }
    cout << ans;
}
