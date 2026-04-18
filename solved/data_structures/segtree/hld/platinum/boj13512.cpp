#include<bits/stdc++.h>
using namespace std;

int n, q, parent[100001], dep[100001], stsize[100001], num[100001], inum[100001], top[100001], cnt, tree[400004];
vector<vector<int>> g;

void dfs1(int ind, int pre) {
    dep[ind] = dep[pre] + 1;
    parent[ind] = pre;
    stsize[ind]++;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs1(iter, ind);
        stsize[ind] += stsize[iter];
        if (stsize[g[ind][0]] < stsize[iter]) swap(g[ind][0], iter);
    }
}

void dfs2(int ind, int pre) {
    num[ind] = ++cnt;
    inum[cnt] = ind;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        top[iter] = iter == g[ind][0] ? top[ind] : iter;
        dfs2(iter, ind);
    }
}

int update(int start, int end, int ind, int i) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = tree[ind] > 0 ? 0 : inum[i];
    int mid = (start + end) / 2;
    int le = update(start, mid, ind * 2, i), ri = update(mid + 1, end, ind * 2 + 1, i);
    if (le == 0 && ri == 0) return tree[ind] = 0;
    else if (le > 0 && ri > 0) return tree[ind] = dep[le] < dep[ri] ? le : ri;
    else if (le > 0) return tree[ind] = le;
    return tree[ind] = ri;
}

int res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    int l = res(start, mid, ind * 2, le, ri), r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (l == 0 && r == 0) return 0;
    else if (l > 0 && r > 0) return (dep[l] < dep[r] ? l : r);
    else if (l > 0) return l;
    return r;
}

int res_path(int a) {
    int b = 1, ans = -1, tmp;
    while (top[a] != top[b]) {
        tmp = res(1, n, 1, num[top[a]], num[a]);
        if (tmp) ans = tmp;
        a = parent[top[a]];
    }
    tmp = res(1, n, 1, num[b], num[a]);
    if (tmp) ans = tmp;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a, b; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].emplace_back(b);
        g[b].emplace_back(a);
    }
    dfs1(1, 0);
    top[1] = 1;
    dfs2(1, 0);
    cin >> q;
    while (q--) {
        cin >> a >> b;
        if (a == 1) update(1, n, 1, num[b]);
        else cout << res_path(b) << '\n';
    }
}
