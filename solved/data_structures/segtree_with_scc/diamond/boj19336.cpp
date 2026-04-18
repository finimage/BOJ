#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct Info {
    int ind, p, r, c;
};

int n, q;
Info arr[200001];
set<int> nodeset, checkset, ckck;
vector<int> g[800004], gg[800004];
ll tree[800004];
int num1[200001], num2[200001];
stack<int> st;
int num[800004], low[800004], check[800004], cnt, cnt_;
bool visited[800004];

bool cmp1(Info a, Info b) {
    return a.p < b.p;
}

void init(int start, int end, int ind) {
    g[ind / 2].push_back(ind);
    if (start == end) {
        num2[end] = ind;
        tree[ind] = arr[end].c;
        nodeset.insert(ind);
        ckck.insert(ind);
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    tree[ind] = tree[ind * 2] + tree[ind * 2 + 1];
}

void nodesetupdate(int start, int end, int ind) {
    if (start == end) return;
    nodeset.insert(ind);
    int mid = (start + end) / 2;
    nodesetupdate(start, mid, ind * 2);
    nodesetupdate(mid + 1, end, ind * 2 + 1);
}

void update(int start, int end, int ind, int le, int ri, int node) {
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        g[node].push_back(ind);
        if (nodeset.count(ind)) return;
        nodesetupdate(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, ind * 2, le, ri, node);
    update(mid + 1, end, ind * 2 + 1, le, ri, node);
}

int bs1(int val) {
    int le = 1, ri = n, mid, res = 1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (val <= arr[mid].p) {
            res = mid;
            ri = mid - 1;
        }
        else le = mid + 1;
    }
    return res;
}

int bs2(int val) {
    int le = 1, ri = n, mid, res = 1;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (arr[mid].p <= val) {
            res = mid;
            le = mid + 1;
        }
        else ri = mid - 1;
    }
    return res;
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

void dfs(int ind) {
    visited[ind] = 1;
    for (auto& iter : g[ind]) {
        if (visited[iter]) continue;
        dfs(iter);
    }
}

void solve() {
    int i, a, b; cin >> n >> q;
    for (i = 1; i <= n; i++) {
        arr[i].ind = i;
        cin >> arr[i].p >> arr[i].r >> arr[i].c;
    }
    sort(arr + 1, arr + n + 1, cmp1);
    for (i = 1; i <= n; i++) num1[arr[i].ind] = i;
    init(1, n, 1);
    for (i = 1; i <= n; i++) update(1, n, 1, bs1(arr[i].p - arr[i].r), bs2(arr[i].p + arr[i].r), num2[i]);
    for (auto& iter : nodeset) {
        if (!num[iter]) scc(iter);
    }
    for (auto& iter : nodeset) gg[check[iter]].push_back(iter);
    vector<map<ll, int>> ckmap(cnt_ + 1);
    ll ans = 0;
    for (i = cnt_; i >= 1; i--) {
        if (!visited[gg[i][0]]) {
            for (auto& iter : gg[i]) {
                if (!ckck.count(iter)) continue;
                if (!ckmap[i].count(tree[iter])) ckmap[i][tree[iter]] = 1;
                else ++ckmap[i][tree[iter]];
            }
            ans += ckmap[i].begin()->x;
            checkset.insert(i);
            dfs(gg[i][0]);
        }
    }
    while (q--) {
        cin >> a >> b;
        if (checkset.count(check[num2[num1[a]]])) {
            ans -= ckmap[check[num2[num1[a]]]].begin()->x;
            if (ckmap[check[num2[num1[a]]]][tree[num2[num1[a]]]] == 1) ckmap[check[num2[num1[a]]]].erase(tree[num2[num1[a]]]);
            else --ckmap[check[num2[num1[a]]]][tree[num2[num1[a]]]];
            tree[num2[num1[a]]] = b;
            if (!ckmap[check[num2[num1[a]]]].count(b)) ckmap[check[num2[num1[a]]]][b] = 1;
            else ++ckmap[check[num2[num1[a]]]][b];
            ans += ckmap[check[num2[num1[a]]]].begin()->x;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
