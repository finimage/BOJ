#include<bits/stdc++.h>
using namespace std;

int n, q, dep[200001], stsize[200001], parent[200001], top[200001], num[200001], cnt, tree[800004];
vector<vector<int>> g;

void dfs1(int ind) {
    stsize[ind]++;
    for (auto& iter : g[ind]) {
        dep[iter] = dep[ind] + 1;
        dfs1(iter);
        stsize[ind] += stsize[iter];
        if (stsize[g[ind][0]] < stsize[iter]) swap(g[ind][0], iter);
    }
}

void dfs2(int ind) {
    num[ind] = ++cnt;
    for (auto& iter : g[ind]) {
        top[iter] = g[ind][0] == iter ? top[ind] : iter;
        dfs2(iter);
    }
}

int res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    return res(start, mid, ind * 2, le, ri) + res(mid + 1, end, ind * 2 + 1, le, ri);
}

int update(int start, int end, int ind, int i) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = 1;
    int mid = (start + end) / 2;
    return tree[ind] = update(start, mid, ind * 2, i) + update(mid + 1, end, ind * 2 + 1, i);
}

int res_path(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        ret += res(1, n, 1, num[top[a]], num[a]);
        a = parent[top[a]];
    }
    if (dep[a] < dep[b]) swap(a, b);
    return ret + res(1, n, 1, num[b] + 1, num[a]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b, c; cin >> n >> q;
    g.resize(n + 1);
    for (i = 2; i <= n; i++) {
        cin >> a;
        g[a].push_back(i);
        parent[i] = a;
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    while (q--) {
        cin >> a >> b >> c;
        if (c == 1) {
            if (res_path(a, b)) {
                cout << "NO\n";
                update(1, n, 1, num[b]);
            }
            else {
                cout << "YES\n";
                update(1, n, 1, num[a]);
            }
        }
        else {
            if (res_path(a, b)) cout << "NO\n";
            else cout << "YES\n";
        }
    }
}
