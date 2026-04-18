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
    ll Min, Max, Sum;
};

int n, q;
int arr[100001];
Info tree[400004];
pll lazy[400004];

Info merge(Info a, Info b) {
    Info tmp;
    tmp.Sum = a.Sum + b.Sum;
    tmp.Min = min(a.Min, b.Min);
    tmp.Max = max(a.Max, b.Max);
    return tmp;
}

Info init(int start, int end, int ind) {
    lazy[ind] = {-2e15,0};
    if (start == end) {
        return tree[ind] = {arr[end],arr[end],arr[end]};
    }
    int mid = (start + end) / 2;
    Info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = merge(l, r);
}

void lazy_prop(int start, int end, int ind) {
    if (lazy[ind] == pair((ll)-2e15,(ll)0)) return;
    pll k = lazy[ind];
    lazy[ind] = {-2e15,0};
    if (k.x != -2e15) {
        tree[ind].Min = tree[ind].Max = k.x + k.y;
        tree[ind].Sum = tree[ind].Max * (end - start + 1);
        if (start == end) return;
        lazy[ind * 2] = lazy[ind * 2 + 1] = {tree[ind].Max,0};
    }
    else {
        tree[ind].Min += k.y;
        tree[ind].Max += k.y;
        tree[ind].Sum += k.y * (end - start + 1);
        if (start == end) return;
        lazy[ind * 2].y += k.y;
        lazy[ind * 2 + 1].y += k.y;
    }
}

Info update_interval1(int start, int end, int ind, int le, int ri, int x) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        lazy[ind].y += x;
        lazy_prop(start, end, ind);
        return tree[ind];
    }
    int mid = (start + end) / 2;
    Info l = update_interval1(start, mid, ind * 2, le, ri, x);
    Info r = update_interval1(mid + 1, end, ind * 2 + 1, le, ri, x);
    return tree[ind] = merge(l, r);
}

ll cal(ll a, ll d) {
    return (ll)floor((ld)(a) / d);
}

Info update_interval2(int start, int end, int ind, int le, int ri, int d) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        if (cal(tree[ind].Min, d) == cal(tree[ind].Max, d)) {
            lazy[ind].x = cal(tree[ind].Min, d);
            lazy_prop(start, end, ind);
            return tree[ind];
        }
        if (tree[ind].Min + 1 == tree[ind].Max) {
            lazy[ind].y = cal(tree[ind].Min, d) - tree[ind].Min;
            lazy_prop(start, end, ind);
            return tree[ind];
        }
    }
    int mid = (start + end) / 2;
    Info l = update_interval2(start, mid, ind * 2, le, ri, d);
    Info r = update_interval2(mid + 1, end, ind * 2 + 1, le, ri, d);
    return tree[ind] = merge(l, r);
}

ll min_interval(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return 2e15;
    if (le <= start && end <= ri) return tree[ind].Min;
    int mid = (start + end) / 2;
    return min(min_interval(start, mid, ind * 2, le, ri), min_interval(mid + 1, end, ind * 2 + 1, le, ri));
}

ll sum_interval(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind].Sum;
    int mid = (start + end) / 2;
    return sum_interval(start, mid, ind * 2, le, ri) + sum_interval(mid + 1, end, ind * 2 + 1, le, ri);
}

void solve() {
    int i, a, b, c, d; cin >> n >> q;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init(1, n, 1);
    while (q--) {
        cin >> a >> b >> c;
        b++;
        c++;
        if (a == 1) {
            cin >> d;
            update_interval1(1, n, 1, b, c, d);
        }
        else if (a == 2) {
            cin >> d;
            update_interval2(1, n, 1, b, c, d);
        }
        else if (a == 3) {
            cout << min_interval(1, n, 1, b, c) << '\n';
        }
        else {
            cout << sum_interval(1, n, 1, b, c) << '\n';
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
