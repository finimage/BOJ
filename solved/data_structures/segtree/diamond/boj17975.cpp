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
    int Le, Ri, Sum, Max;
};

struct tri {
    int a, x, y;
};

bool cmp1(tri a, tri b) {
    if (a.x < b.x) return 1;
    if (a.x == b.x && a.y < b.y) return 1;
    return 0;
}

bool cmp2(tri a, tri b) {
    if (a.y < b.y) return 1;
    return 0;
}

int n, n1, n2, c1, c2;
vector<int> v;
vector<tri> pp;
vector<info> tree;

info update(int start, int end, int ind, int i, int v) {
    if (i < start || end < i) return tree[ind];
    if (start == end) {
        tree[ind].Le += v;
        tree[ind].Ri += v;
        tree[ind].Sum += v;
        tree[ind].Max += v;
        return tree[ind];
    }
    int mid = (start + end) / 2;
    info l = update(start, mid, ind * 2, i, v), r = update(mid + 1, end, ind * 2 + 1, i, v);
    info res = {0,0,0,0};
    res.Le = max(l.Le, l.Sum + r.Le);
    res.Ri = max(r.Ri, r.Sum + l.Ri);
    res.Sum = l.Sum + r.Sum;
    res.Max = max({l.Ri+r.Le, l.Max, r.Max});
    return tree[ind] = res;
}

void solve() {
    int i, j, t, a, b; cin >> n1;
    for (i = 0; i < n1; i++) {
        cin >> a >> b;
        pp.push_back({1, a,b});
    }
    cin >> n2;
    for (i = 0; i < n2; i++) {
        cin >> a >> b;
        pp.push_back({2, a,b});
    }
    sort(pp.begin(), pp.end(), cmp2);
    a = 1;
    for (i = 1; i < n1 + n2; i++) {
        if (pp[i].y == pp[i - 1].y) {
            if (i == n1 + n2 - 1) pp[i].y = pp[i - 1].y = a;
            else pp[i - 1].y = a;
        }
        else {
            pp[i - 1].y = a++;
            if (i == n1 + n2 - 1) pp[i].y = a;
        }
    }
    n = a;
    sort(pp.begin(), pp.end(), cmp1);
    v.push_back(-1);
    for (i = 1; i < n1 + n2; i++) {
        if (pp[i].x != pp[i - 1].x) v.push_back(i - 1);
    }
    v.push_back(n1 + n2 - 1);
    cin >> c1 >> c2;
    int ans = 0;
    for (i = 1; i < v.size(); i++) {
        tree.clear();
        tree.resize(4 * n + 4, {0,0,0,0});
        t = i;
        a = v[t - 1] + 1;
        for (j = a; j < n1 + n2; j++) {
            update(1, n, 1, pp[j].y, pp[j].a == 1 ? c1 : -c2);
            if (j == v[t]) {
                t++;
                //cout << a << ' ' << j << ' ' << pp[j].y << ' ' << tree[1].Max << '\n';
                ans = max(ans, tree[1].Max);
            }
        }
    }
    cout << ans;
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
