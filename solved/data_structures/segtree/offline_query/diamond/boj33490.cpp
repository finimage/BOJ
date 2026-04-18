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
    int ind, c, s;
    bool operator<(const info& a) const {
        if (this->s < a.s) return 1;
        if (this->s == a.s && this->c < a.c) return 1;
        if (this->s == a.s && this->c == a.c && this->ind < a.ind) return 1;
        return 0;
    }
};

map<info, int> mmap;
int n, q;
pii arr[200001];
ll ck[1600016];
pll tree[1600016];
vector<info> query;

pll update(int start, int end, int ind, int i, int s, int c) {
    if (i < start || end < i) return tree[ind];
    if (start == end) {
        return tree[ind] = {s,s + c - 1};
    }
    int mid = (start + end) / 2;
    pll le = update(start, mid, ind * 2, i, s, c);
    pll ri = update(mid + 1, end, ind * 2 + 1, i, s, c);
    if (le == tree[0]) {
        ck[ind] = ck[ind * 2 + 1];
        return tree[ind] = ri;
    }
    if (ri == tree[0]) {
        ck[ind] = ck[ind * 2];
        return tree[ind] = le;
    }
    if (le.y < ri.x) {
        ck[ind] = ri.x - le.y - 1 + ck[ind * 2] + ck[ind * 2 + 1];
        return tree[ind] = {le.x, ri.y};
    }
    if (le.y - ri.x + 1 <= ck[ind * 2 + 1]) {
        ck[ind] = ck[ind * 2] + ck[ind * 2 + 1] - (le.y - ri.x + 1);
        return tree[ind] = {le.x, ri.y};
    }
    ck[ind] = ck[ind * 2];
    return tree[ind] = {le.x, le.y - ri.x + 1 - ck[ind * 2 + 1] + ri.y};
}

void solve() {
    int i; cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> arr[i].x >> arr[i].y;
        mmap[{i,arr[i].x,arr[i].y}] = 0;
    }
    cin >> q;
    query.resize(q);
    for (i = 0; i < q; i++) {
        cin >> query[i].ind >> query[i].c >> query[i].s;
        mmap[query[i]] = 0;
    }
    int cnt = 0;
    for (auto& iter : mmap) iter.y = ++cnt;
    for (i = 1; i <= n; i++) update(1, n + q, 1, mmap[{i,arr[i].x,arr[i].y}], arr[i].y, arr[i].x);
    cout << tree[1].y << '\n';
    for (i = 0; i < q; i++) {
        if (arr[query[i].ind] != pair(query[i].c,query[i].s)) {
            update(1, n + q, 1, mmap[{query[i].ind,arr[query[i].ind].x,arr[query[i].ind].y}], 0, 1);
            arr[query[i].ind] = {query[i].c,query[i].s};
            update(1, n + q, 1, mmap[query[i]], query[i].s, query[i].c);
        }
        cout << tree[1].y << '\n';
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
