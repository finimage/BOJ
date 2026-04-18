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

struct Info {
    int Lecnt[2], Ricnt[2], Cnt, Max[2];
};

int n, q, cnt;
int arr[100001], revnum[100001], num[100001], par[100001], sz[100001], top_[100001];
pii top[100001];
int dp[100001][2], dp_[100001][2];
vector<vector<int>> g;
Info tree[400004];
pii it[100001];
int num_[100001], val[100001];
pii tree_[400004];

void dfs1(int ind, int pre) {
    par[ind] = pre;
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
    revnum[cnt] = ind;
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        top_[iter] = g[ind][0] == iter ? top_[ind] : iter;
        dfs2(iter, ind);
    }
}

void dfs3(int ind, int pre) {
    dp[ind][arr[ind]] = val[ind];
    dp_[ind][arr[ind]] = val[ind];
    top[ind] = {num[top_[ind]],num[top_[ind]]};
    for (auto& iter : g[ind]) {
        if (iter == pre) continue;
        dfs3(iter, ind);
        if (iter != g[ind][0]) {
            dp[ind][0] = max(dp[ind][0], dp_[iter][0]);
            dp[ind][1] = max(dp[ind][1], dp_[iter][1]);
        }
        dp_[ind][arr[ind]] = max(dp_[ind][arr[ind]], dp_[iter][arr[ind]]);
    }
}

Info merge(Info a, Info b) {
    Info tmp;
    tmp.Lecnt[0] = a.Lecnt[0];
    if (a.Lecnt[0] == a.Cnt) tmp.Lecnt[0] += b.Lecnt[0];
    tmp.Lecnt[1] = a.Lecnt[1];
    if (a.Lecnt[1] == a.Cnt) tmp.Lecnt[1] += b.Lecnt[1];
    tmp.Ricnt[0] = b.Ricnt[0];
    if (b.Ricnt[0] == b.Cnt) tmp.Ricnt[0] += a.Ricnt[0];
    tmp.Ricnt[1] = b.Ricnt[1];
    if (b.Ricnt[1] == b.Cnt) tmp.Ricnt[1] += a.Ricnt[1];
    tmp.Cnt = a.Cnt + b.Cnt;
    tmp.Max[0] = max(a.Max[0], b.Max[0]);
    tmp.Max[1] = max(a.Max[1], b.Max[1]);
    return tmp;
}

Info init(int start, int end, int ind) {
    if (start == end) {
        return tree[ind] = {!arr[revnum[end]],arr[revnum[end]],!arr[revnum[end]],arr[revnum[end]],1,dp[revnum[end]][0],dp[revnum[end]][1]};
    }
    int mid = (start + end) / 2;
    Info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = merge(l, r);
}

Info update(int start, int end, int ind, int i, int v1, int v2, int v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = {!v,v,!v,v,1, v1, v2};
    int mid = (start + end) / 2;
    Info l = update(start, mid, ind * 2, i, v1, v2, v);
    Info r = update(mid + 1, end, ind * 2 + 1, i, v1, v2, v);
    return tree[ind] = merge(l, r);
}

Info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return tree[0];
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    Info l = res(start, mid, ind * 2, le, ri);
    Info r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (mid < le) return r;
    if (ri <= mid) return l;
    return merge(l, r);
}

pii upt(int start, int end, int ind, int i, int v1, int v2) {
    if (i < start || end < i) return tree_[ind];
    if (start == end) return tree_[ind] = {v1,v2};
    int mid = (start + end) / 2;
    pii l = upt(start, mid, ind * 2, i, v1, v2);
    pii r = upt(mid + 1, end, ind * 2 + 1, i, v1, v2);
    return tree_[ind] = {max(l.x, r.x),max(l.y, r.y)};
}

pii max_(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return {0,0};
    if (le <= start && end <= ri) return tree_[ind];
    int mid = (start + end) / 2;
    pii l = max_(start, mid, ind * 2, le, ri);
    pii r = max_(mid + 1, end, ind * 2 + 1, le, ri);
    return {max(l.x, r.x),max(l.y, r.y)};
}

void update_path(int a) {
    arr[a] = !arr[a];
    pii temp = max_(1, n, 1, it[a].x, it[a].y);
    dp[a][arr[a]] = max(val[a], arr[a] == 0 ? temp.x : temp.y);
    dp[a][!arr[a]] = arr[a] == 0 ? temp.x : temp.y;
    while (top_[a] != 1) {
        update(1, n, 1, num[a], dp[a][0], dp[a][1], arr[a]);
        Info aft = res(1, n, 1, top[top_[a]].x, top[top_[a]].y);
        int val1 = 0, val2 = 0;
        if (aft.Lecnt[0]) {
            val1 = res(1, n, 1, top[top_[a]].x, top[top_[a]].x + aft.Lecnt[0] - 1).Max[0];
        }
        if (aft.Lecnt[1]) {
            val2 = res(1, n, 1, top[top_[a]].x, top[top_[a]].x + aft.Lecnt[1] - 1).Max[1];
        }
        upt(1, n, 1, num_[top_[a]], val1, val2);
        pii tmp = max_(1, n, 1, it[par[top_[a]]].x, it[par[top_[a]]].y);
        dp[par[top_[a]]][arr[par[top_[a]]]] = max(val[par[top_[a]]], arr[par[top_[a]]] == 0 ? tmp.x : tmp.y);
        dp[par[top_[a]]][!arr[par[top_[a]]]] = arr[par[top_[a]]] == 0 ? tmp.x : tmp.y;
        a = par[top_[a]];
    }
    update(1, n, 1, num[a], dp[a][0], dp[a][1], arr[a]);
}

int res_path(int a) {
    while (top_[a] != 1) {
        Info l = res(1, n, 1, top[top_[a]].x, num[a]);
        Info r = res(1, n, 1, num[a], top[top_[a]].y);
        if (l.Lecnt[arr[a]] != l.Cnt || arr[par[top_[a]]] != arr[a]) {
            return res(1, n, 1, num[a] - l.Ricnt[arr[a]] + 1, num[a] + r.Lecnt[arr[a]] - 1).Max[arr[a]];
        }
        a = par[top_[a]];
    }
    Info l = res(1, n, 1, top[top_[a]].x, num[a]);
    Info r = res(1, n, 1, num[a], top[top_[a]].y);
    return res(1, n, 1, num[a] - l.Ricnt[arr[a]] + 1, num[a] + r.Lecnt[arr[a]] - 1).Max[arr[a]];
}

void update_path2(int a, int v) {
    val[a] = v;
    pii temp = max_(1, n, 1, it[a].x, it[a].y);
    dp[a][arr[a]] = max(val[a], arr[a] == 0 ? temp.x : temp.y);
    dp[a][!arr[a]] = arr[a] == 0 ? temp.x : temp.y;
    while (top_[a] != 1) {
        update(1, n, 1, num[a], dp[a][0], dp[a][1], arr[a]);
        Info aft = res(1, n, 1, top[top_[a]].x, top[top_[a]].y);
        int val1 = 0, val2 = 0;
        if (aft.Lecnt[0]) {
            val1 = res(1, n, 1, top[top_[a]].x, top[top_[a]].x + aft.Lecnt[0] - 1).Max[0];
        }
        if (aft.Lecnt[1]) {
            val2 = res(1, n, 1, top[top_[a]].x, top[top_[a]].x + aft.Lecnt[1] - 1).Max[1];
        }
        upt(1, n, 1, num_[top_[a]], val1, val2);
        pii tmp = max_(1, n, 1, it[par[top_[a]]].x, it[par[top_[a]]].y);
        dp[par[top_[a]]][arr[par[top_[a]]]] = max(val[par[top_[a]]], arr[par[top_[a]]] == 0 ? tmp.x : tmp.y);
        dp[par[top_[a]]][!arr[par[top_[a]]]] = arr[par[top_[a]]] == 0 ? tmp.x : tmp.y;
        a = par[top_[a]];
    }
    update(1, n, 1, num[a], dp[a][0], dp[a][1], arr[a]);
}

void solve() {
    int i, a, b, c; cin >> n;
    g.resize(n + 1);
    for (i = 1; i < n; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (i = 1; i <= n; i++) cin >> arr[i];
    for (i = 1; i <= n; i++) cin >> val[i];
    dfs1(1, 0);
    top[1] = {1,1};
    top_[1] = 1;
    dfs2(1, 0);
    dfs3(1, 0);
    for (i = 1; i <= n; i++) top[top_[i]].y = max(top[top_[i]].y, num[i]);
    int j = 1;
    num_[1] = 1;
    for (i = 1; i <= n; i++) {
        it[i].x = j + 1;
        for (auto& iter : g[i]) {
            if (iter == par[i]) continue;
            num_[iter] = ++j;
        }
        it[i].y = j;
    }
    for (i = 1; i <= n; i++) {
        if (i == top_[i]) upt(1, n, 1, num_[i], dp_[i][0], dp_[i][1]);
    }
    init(1, n, 1);
    cin >> q;
    while (q--) {
        cin >> a >> b;
        if (a == 1) update_path(b);
        else if (a == 2) cout << res_path(b) << '\n';
        else {
            cin >> c;
            update_path2(b, c);
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
