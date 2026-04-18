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

int n, m1, m2, cnt, cnt_;
vector<int> num, low, check, mapping, par, num_;
vector<vector<int>> g;
vector<pii> A;
bool visited[1500015];
stack<int> st;

int find_(int a) {
    if (a == par[a]) return a;
    return par[a] = find_(par[a]);
}

bool union_(int a, int b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (a < b) swap(a, b);
    par[a] = b;
    return 0;
}

void init(int start, int end, int ind) {
    if (start == end) {
        mapping[end] = ind;
        return;
    }
    int mid = (start + end) / 2;
    init(start, mid, ind * 2);
    init(mid + 1, end, ind * 2 + 1);
    g[ind].push_back(ind * 2);
    g[ind].push_back(ind * 2 + 1);
}

void update(int start, int end, int ind, int i, int le, int ri) {
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        g[i].push_back(ind);
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, ind * 2, i, le, ri);
    update(mid + 1, end, ind * 2 + 1, i, le, ri);
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
    int i, a, b; cin >> n >> m1 >> m2;
    A.resize(m1);
    for (i = 0; i < m1; i++) cin >> A[i].x >> A[i].y;
    par.resize(n + 1);
    for (i = 1; i <= n; i++) par[i] = i;
    for (i = 0; i < m2; i++) {
        cin >> a >> b;;
        union_(a, b);
    }
    vector<vector<int>> gg(n + 1);
    for (i = 1; i <= n; i++) gg[find_(i)].push_back(i);
    num_.resize(n + 1);
    vector<pii> interval(n + 1);
    for (i = 1; i <= n; i++) {
        interval[i].x = cnt + 1;
        for (auto& iter : gg[i]) num_[iter] = ++cnt;
        interval[i].y = cnt;
    }
    g.resize(5 * n + 4);
    mapping.resize(n + 1);
    init(1, n, 1);
    cnt = 0;
    for (i = 0; i < m1; i++) {
        a = num_[A[i].x];
        b = num_[A[i].y];
        g[mapping[a]].push_back(b + 4 * n);
        g[mapping[b]].push_back(a + 4 * n);
    }
    for (i = 1; i <= n; i++) {
        if (gg[i].size() < 2) continue;
        for (auto& iter : gg[i]) {
            update(1, n, 1, num_[iter] + 4 * n, interval[i].x, num_[iter] - 1);
            update(1, n, 1, num_[iter] + 4 * n, num_[iter] + 1, interval[i].y);
        }
    }
    gg.clear();
    num.resize(n * 5 + 5);
    low.resize(n * 5 + 5);
    check.resize(n * 5 + 5);
    for (i = 1; i <= n * 5; i++) {
        if (!num[i]) scc(i);
    }
    for (i = 1; i <= n; i++) {
        if (check[num_[i] + 4 * n] == check[mapping[num_[i]]]) {
            cout << "NO";
            return;
        }
    }
    cout << "YES\n";
    for (i = 1; i <= n; i++) {
        if (check[num_[i] + 4 * n] < check[mapping[num_[i]]]) {
            cout << i << ' ';
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
