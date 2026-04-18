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

int n, cnt, cnt_, Max;
vector<int> arr, tree, mapping, num, low, check;
vector<vector<int>> g, rev_g;
bool visited[1200004], vis[300004], viss[1200004];
stack<int> st;

void init(int start, int end, int ind) {
    Max = max(Max, ind);
    if (start == end) {
        mapping[end] = ind;
        tree[ind] = arr[end];
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    tree[ind] = max(tree[ind * 2], tree[ind * 2 + 1]);
    g[ind * 2].push_back(ind);
    g[ind * 2 + 1].push_back(ind);
    rev_g[ind].push_back(ind * 2);
    rev_g[ind].push_back(ind * 2 + 1);
}

void res(int start, int end, int ind, int i, int le, int ri) {
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        g[ind].push_back(mapping[i]);
        rev_g[mapping[i]].push_back(ind);
        return;
    }
    int mid = (start + end) / 2;
    res(start, mid, ind * 2, i, le, ri);
    res(mid + 1, end, ind * 2 + 1, i, le, ri);
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
    int i, a, b; cin >> n;
    arr.resize(n + 1);
    for (i = 1; i <= n; i++) cin >> arr[i];
    mapping.resize(n + 1);
    tree.resize(4 * n + 4);
    g.resize(4 * n + 4);
    rev_g.resize(4 * n + 4);
    init(1, n, 1);
    num.resize(Max + 1);
    low.resize(Max + 1);
    check.resize(Max + 1);
    for (i = 1; i <= n; i++) {
        cin >> a >> b;
        if (a <= i && i <= b) vis[i] = 1;
        res(1, n, 1, i, a, b);
    }
    for (i = 1; i <= Max; i++) {
        if (!num[i]) scc(i);
    }
    vector<vector<int>> gg(cnt_ + 1);
    for (i = 1; i <= Max; i++) {
        gg[check[i]].push_back(i);
    }
    vector<int> v(cnt_ + 1), v_(cnt_ + 1);
    for (i = 1; i <= n; i++) {
        if (vis[i]) {
            viss[check[mapping[i]]] = 1;
            v[check[mapping[i]]] = max(v[check[mapping[i]]], arr[i]);
        }
    }
    for (i = cnt_; i > 0; i--) {
        for (auto& iter : gg[i]) {
            v_[check[iter]] = max(v_[check[iter]], tree[iter]);
            if (gg[i].size() > 1) v[check[iter]] = max(v[check[iter]], tree[iter]);
            for (auto& itr : rev_g[iter]) {
                if (gg[i].size() > 1 || viss[i]) v[i] = max(v[i], v_[check[itr]]);
                v[i] = max(v[i], v[check[itr]]);
                v_[i] = max(v_[i], v_[check[itr]]);
            }
        }
    }
    for (i = 1; i <= n; i++) {
        //cout << i << ' ' << check[mapping[i]] << ' ' << mapping[i] << '\n';
        cout << v[check[mapping[i]]] << ' ';
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
