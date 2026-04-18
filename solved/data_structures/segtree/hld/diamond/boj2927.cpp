#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 998244353
using namespace std;

struct info {
    int a, b, c;
};

int n, q, cnt;
vector<info> query;
vector<pii> edge;
vector<vector<int>> g;
vector<int> top, par, stsize, dep, num, parent;
int pen[30001], tree[120004], tree2[120004];

void pre() {
    g.resize(n + 1);
    top.resize(n + 1);
    par.resize(n + 1);
    stsize.resize(n + 1);
    dep.resize(n + 1);
    num.resize(n + 1);
    parent.resize(n + 1);
}

int find_(int a) {
    if (a == parent[a]) return a;
    return parent[a] = find_(parent[a]);
}

bool union_(int a, int b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (a < b) swap(a, b);
    parent[a] = b;
    return 0;
}

void dfs1(int ind, int pre) {
    par[ind] = pre;
    dep[ind] = dep[pre] + 1;
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
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        top[iter] = iter == g[ind][0] ? top[ind] : iter;
        dfs2(iter, ind);
    }
}

void make_tree() {
    int i;
    for (i = 1; i <= n; i++) parent[i] = i;
    for (auto& iter : edge) {
        if (union_(iter.x, iter.y)) continue;
        g[iter.x].push_back(iter.y);
        g[iter.y].push_back(iter.x);
    }
    for (i = 1; i <= n; i++) {
        if (union_(1, i)) continue;
        g[i].push_back(1);
        g[1].push_back(i);
    }
    dfs1(1, 1);
    dfs2(1, 1);
    for (i = 1; i <= n; i++) parent[i] = i;
}

int update(int start, int end, int ind, int i, int v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = v;
    int mid = (start + end) / 2;
    return tree[ind] = update(start, mid, ind * 2, i, v) + update(mid + 1, end, ind * 2 + 1, i, v);
}

int sum_interval(int start, int end, int ind, int le, int ri) {
    if (le <= start && end <= ri) return tree[ind];
    if (ri < start || end < le) return 0;
    int mid = (start + end) / 2;
    return sum_interval(start, mid, ind * 2, le, ri) + sum_interval(mid + 1, end, ind * 2 + 1, le, ri);
}

int update_connect(int start, int end, int ind, int i) {
    if (i < start || end < i) return tree2[ind];
    if (start == end) return tree2[ind] = 1;
    int mid = (start + end) / 2;
    return tree2[ind] = update_connect(start, mid, ind * 2, i) + update_connect(mid + 1, end, ind * 2 + 1, i);
}

int sum_connect(int start, int end, int ind, int le, int ri) {
    if (le <= start && end <= ri) return tree2[ind];
    if (ri < start || end < le) return 0;
    int mid = (start + end) / 2;
    return sum_connect(start, mid, ind * 2, le, ri) + sum_connect(mid + 1, end, ind * 2 + 1, le, ri);
}

int sum_path(int a, int b) {
    int ans = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        if (num[a] - num[top[a]] + 1 != sum_connect(1, n, 1, num[top[a]], num[a])) {
            return -1;
        }
        ans += sum_interval(1, n, 1, num[top[a]], num[a]);
        a = par[top[a]];
    }
    if (dep[a] > dep[b]) swap(a, b);
    if (num[b] - num[a] != sum_connect(1, n, 1, num[a] + 1, num[b])) {
        return -1;
    }
    ans += sum_interval(1, n, 1, num[a], num[b]);
    return ans;
}

void solve() {
    int i, a, b, c; string s; cin >> n;
    for (i = 1; i <= n; i++) cin >> pen[i];
    cin >> q;
    query.resize(q);
    for (i = 0; i < q; i++) {
        cin >> s >> a >> b;
        if (s == "bridge") {
            query[i] = {0, a, b};
            edge.push_back({a,b});
        }
        else if (s == "penguins") query[i] = {1, a, b};
        else query[i] = {2, a, b};
    }
    pre();
    make_tree();
    for (i = 1; i <= n; i++) update(1, n, 1, num[i], pen[i]);
    for (i = 0; i < q; i++) {
        auto [c, a, b] = query[i];
        if (c == 0) {
            if (union_(a, b)) cout << "no\n";
            else {
                cout << "yes\n";
                if (par[a] == b) update_connect(1, n, 1, num[a]);
                else update_connect(1, n, 1, num[b]);
            }
        }
        else if (c == 1) {
            update(1, n, 1, num[a], b);
        }
        else {
            c = sum_path(a, b);
            if (c == -1) cout << "impossible\n";
            else cout << c << '\n';
        }
    }
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
