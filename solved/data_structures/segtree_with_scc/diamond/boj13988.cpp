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

struct info {
    int x, le, ri;
};

bool cmp(info a, info b) {
    return a.x < b.x;
}

struct infor {
    int Max, Maxind, Min, Minind;
};

int n, m, cnt, cnt_;
vector<info> arr;
vector<vector<int>> g;
vector<int> num, low, check;
vector<infor> tree;
vector<bool> visited;
vector<pii> v, vv;
stack<int> st;

int bs1(int val) {
    int le = 1, ri = n, mid, res = n;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (val <= arr[mid].x) {
            ri = mid - 1;
            res = mid;
        }
        else le = mid + 1;
    }
    return res;
}

int bs2(int val) {
    int le = 1, ri = n, mid, res = n + 1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (val < arr[mid].x) {
            ri = mid - 1;
            res = mid;
        }
        else le = mid + 1;
    }
    return res;
}

void init(int start, int end, int ind) {
    if (start == end) {
        tree[ind].Min = arr[end].x - arr[end].le;
        tree[ind].Max = arr[end].x + arr[end].ri;
        tree[ind].Maxind = tree[ind].Minind = end;
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    infor l = tree[ind * 2], r = tree[ind * 2 + 1], res;
    if (l.Max > r.Max) {
        res.Max = l.Max;
        res.Maxind = l.Maxind;
    }
    else {
        res.Max = r.Max;
        res.Maxind = r.Maxind;
    }
    if (l.Min <= r.Min) {
        res.Min = l.Min;
        res.Minind = l.Minind;
    }
    else {
        res.Min = r.Min;
        res.Minind = r.Minind;
    }
    tree[ind] = res;
}

int find_Maxind(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return -1;
    if (le <= start && end <= ri) return tree[ind].Maxind;
    int mid = (start + end) / 2;
    int l = find_Maxind(start, mid, ind * 2, le, ri);
    int r = find_Maxind(mid + 1, end, ind * 2 + 1, le, ri);
    if (l == -1) return r;
    if (r == -1) return l;
    if (arr[l].x + arr[l].ri > arr[r].x + arr[r].ri) return l;
    return r;
}

int find_Minind(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return -1;
    if (le <= start && end <= ri) return tree[ind].Minind;
    int mid = (start + end) / 2;
    int l = find_Minind(start, mid, ind * 2, le, ri);
    int r = find_Minind(mid + 1, end, ind * 2 + 1, le, ri);
    if (l == -1) return r;
    if (r == -1) return l;
    if (arr[l].x - arr[l].le <= arr[r].x - arr[r].le) return l;
    return r;
}

void scc(int ind) {
    num[ind] = low[ind] = ++cnt;
    visited[ind] = 1;
    st.push(ind);
    for (auto& iter : g[ind]) {
        if (!num[iter]) {
            scc(iter);
            low[ind] = min(low[ind], low[iter]);
        }
        else if (visited[iter]) low[ind] = min(low[ind], low[iter]);
    }
    if (num[ind] == low[ind]) {
        cnt_++;
        while (!st.empty()) {
            int k = st.top();
            st.pop();
            visited[k] = 0;
            check[k] = cnt_;
            if (k == ind) break;
        }
    }
}

void solve() {
    int i, x, le, ri; cin >> n >> m;
    arr.resize(n + 1);
    for (i = 1; i <= n; i++) {
        cin >> x >> le >> ri;
        arr[i] = {x,le,ri};
    }
    sort(arr.begin() + 1, arr.end(), cmp);
    tree.resize(4 * n + 4);
    init(1, n, 1);
    g.resize(n + 1);
    for (i = 1; i <= n; i++) {
        le = bs1(arr[i].x - arr[i].le);
        ri = bs2(arr[i].x + arr[i].ri);
        g[i].push_back(find_Maxind(1, n, 1, le, ri - 1));
        g[i].push_back(find_Minind(1, n, 1, le, ri - 1));
    }
    num.resize(n + 1);
    low.resize(n + 1);
    check.resize(n + 1);
    visited.resize(n + 1);
    for (i = 1; i <= n; i++) {
        if (!num[i]) scc(i);
    }
    vector<vector<int>> gg(cnt_ + 1);
    for (i = 1; i <= n; i++) {
        gg[check[i]].push_back(i);
    }
    v.resize(cnt_ + 1, {2e9 + 1, -2e9 - 1});
    for (i = 1; i <= cnt_; i++) {
        int tmple = arr[gg[i][0]].x - arr[gg[i][0]].le, tmpri = arr[gg[i][0]].x + arr[gg[i][0]].ri;
        for (auto& iter : gg[i]) {
            tmple = min(tmple, arr[iter].x - arr[iter].le);
            tmpri = max(tmpri, arr[iter].x + arr[iter].ri);
            for (auto& itr : g[iter]) {
                tmple = min(tmple, v[check[itr]].x);
                tmpri = max(tmpri, v[check[itr]].y);
            }
        }
        v[i] = {tmple, tmpri};
    }
    gg.clear();
    vv.resize(2 * n);
    for (i = 0; i < n; i++) {
        le = v[check[i + 1]].x;
        ri = v[check[i + 1]].y;
        vv[i * 2] = {le,1};
        vv[i * 2 + 1] = {ri + 1, -1};
    }
    sort(vv.begin(), vv.end());
    v.clear();
    v.resize(m);
    for (i = 0; i < m; i++) {
        cin >> v[i].x;
        v[i].y = i;
    }
    sort(v.begin(), v.end());
    cnt = 0;
    vector<int> ans(m);
    int j = 0;
    for (auto& iter : v) {
        for (i = j; i < 2 * n; i++) {
            if (iter.x < vv[i].x) {
                j = i;
                break;
            }
            cnt += vv[i].y;
        }
        ans[iter.y] = cnt;
    }
    for (i = 0; i < m; i++) cout << ans[i] << '\n';
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
