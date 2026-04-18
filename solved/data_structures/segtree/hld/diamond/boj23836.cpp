#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct Info {
    ll a, b, c;
    int aa, bb;
};

int n, q, cnt, num[100001], par[100001], sz[100001], top[100001], dep[100001];
vector<vector<int>> g;
ll tree[400004];
Info lazy[400004];

void dfs1(int ind, int pre) {
    par[ind] = pre;
    dep[ind] = dep[pre] + 1;
    sz[ind]++;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs1(iter, ind);
        sz[ind] += sz[iter];
        if (sz[iter] > sz[g[ind][0]]) swap(iter, g[ind][0]);
    }
}

void dfs2(int ind, int pre) {
    num[ind] = ++cnt;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        top[iter] = g[ind][0] == iter ? top[ind] : iter;
        dfs2(iter, ind);
    }
}

void lazy_prop(int start, int end, int ind) {
    if (start == end && end == 4) {
        //cout << lazy[ind].a << ' ' << lazy[ind].b << ' ' << lazy[ind].c << ' ' << lazy[ind].aa << ' ' << lazy[ind].bb << '\n';
    }
    if (lazy[ind].a) {
        ll a = lazy[ind].a, aa = lazy[ind].aa;
        lazy[ind].a = lazy[ind].aa = 0;
        if (start != end) {
            lazy[ind * 2].a += a + aa * (end - (start + end) / 2);
            lazy[ind * 2].aa += aa;
            lazy[ind * 2 + 1].a += a;
            lazy[ind * 2 + 1].aa += aa;
        }
        else tree[ind] += a;
    }
    if (lazy[ind].b) {
        ll b = lazy[ind].b, bb = lazy[ind].bb;
        lazy[ind].b = lazy[ind].bb = 0;
        if (start != end) {
            lazy[ind * 2].b += b - bb * (end - (start + end) / 2);
            lazy[ind * 2].bb += bb;
            lazy[ind * 2 + 1].b += b;
            lazy[ind * 2 + 1].bb += bb;
        }
        else tree[ind] += b;
    }
    if (lazy[ind].c) {
        ll c = lazy[ind].c;
        lazy[ind].c = 0;
        tree[ind] -= c;
        if (start == end) return;
        lazy[ind * 2].c += c;
        lazy[ind * 2 + 1].c += c;
    }
}

void update1(int start, int end, int ind, int le, int ri, int c) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        lazy[ind].a = c + ri - end;
        lazy[ind].aa = 1;
        lazy[ind].c = 1;
        lazy_prop(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    update1(start, mid, ind * 2, le, ri, c);
    update1(mid + 1, end, ind * 2 + 1, le, ri, c);
}

void update2(int start, int end, int ind, int le, int ri, int c) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        lazy[ind].b = c - ri + end;
        lazy[ind].bb = 1;
        lazy[ind].c = 1;
        lazy_prop(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    update2(start, mid, ind * 2, le, ri, c);
    update2(mid + 1, end, ind * 2 + 1, le, ri, c);
}

int path_len(int a, int b) {
    int ans = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        ans += num[a] - num[top[a]] + 1;
        a = par[top[a]];
    }
    if (dep[a] < dep[b]) swap(a, b);
    ans += num[a] - num[b] + 1;
    return ans;
}

void update_path(int a, int b, int c) {
    int aa = 1, bb = c;
    while (top[a] != top[b]) { 
        if (dep[top[a]] < dep[top[b]]) {
            update2(1, n, 1, num[top[b]], num[b], bb);
            bb -= num[b] - num[top[b]] + 1;
            b = par[top[b]];
        }
        else {
            //cout << num[top[a]] << ' ' << num[a] << ' ' << aa;
            update1(1, n, 1, num[top[a]], num[a], aa);
            aa += num[a] - num[top[a]] + 1;
            a = par[top[a]];
        }
    }
    //cout << "*\n";
    if (dep[a] < dep[b]) update2(1, n, 1, num[a], num[b], bb);
    else update1(1, n, 1, num[b], num[a], aa);
}

ll query2(int start, int end, int ind, int i) {
    lazy_prop(start, end, ind);
    if (i < start || end < i) return 0;
    if (start == end) return tree[ind];
    int mid = (start + end) / 2;
    return query2(start, mid, ind * 2, i) + query2(mid + 1, end, ind * 2 + 1, i);
}

void solve() {
    int i, a, b, c; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs1(1, 0);
    top[1] = 1;
    dfs2(1, 0);
    cin >> q;
    while (q--) {
        cin >> a >> b;
        if (a == 1) {
            cin >> c;
            //cout << "path_len " << path_len(b, c) << '\n';
            update_path(b, c, path_len(b, c));
        }
        else cout << query2(1, n, 1, num[b]) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
