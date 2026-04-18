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
    int Min, Max, sMax, Cnt; ll Sum;
};

int n, q;
int arr[1000001];
Info tree[4000004];
pii lazy[4000004];

Info merge(Info a, Info b) {
    Info tmp;
    tmp.Sum = a.Sum + b.Sum;
    tmp.Min = min(a.Min, b.Min);
    tmp.Max = max(a.Max, b.Max);
    tmp.Cnt = a.Max > b.Max ? a.Cnt : a.Max < b.Max ? b.Cnt : a.Cnt + b.Cnt;
    if (a.Max == a.Min && b.Max == b.Min) {
        tmp.sMax = min(a.Max, b.Max);
    }
    else if (a.Max == a.Min) {
        tmp.sMax = a.Max > b.Max ? b.Max : a.Max < b.Max ? max(a.Max, b.sMax) : b.sMax;
    }
    else if (b.Max == b.Min) {
        tmp.sMax = b.Max > a.Max ? a.Max : b.Max < a.Max ? max(b.Max, a.sMax) : a.sMax;
    }
    else {
        tmp.sMax = a.Max > b.Max ? max(a.sMax, b.Max) : a.Max < b.Max ? max(a.Max, b.sMax) : max(a.sMax, b.sMax);
    }
    return tmp;
}

Info init(int start, int end, int ind) {
    lazy[ind] = {-1,-1};
    if (start == end) {
        return tree[ind] = {arr[end],arr[end],arr[end],1,arr[end]};
    }
    int mid = (start + end) / 2;
    Info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = merge(l, r);
}

void lazy_prop(int start, int end, int ind) {
    if (lazy[ind] == pair(-1,-1)) return;
    pii k = lazy[ind];
    lazy[ind] = {-1,-1};
    if (k.x == -1) {
        tree[ind] = {k.y,k.y,k.y,end-start+1,(ll)k.y*(end-start+1)};
        if (start == end) return;
        lazy[ind * 2] = lazy[ind * 2 + 1] = k;
    }
    else {
        tree[ind].Sum -= (ll)tree[ind].Cnt * (tree[ind].Max - k.y);
        tree[ind].Max = k.y;
        if (start == end) return;
        if (tree[ind * 2].Min >= k.y) lazy[ind * 2] = {-1,k.y};
        else if (k.y < tree[ind * 2].Max) lazy[ind * 2] = k;
        if (tree[ind * 2 + 1].Min >= k.y) lazy[ind * 2 + 1] = {-1,k.y};
        else if (k.y < tree[ind * 2 + 1].Max) lazy[ind * 2 + 1] = k;
    }
}

Info update_interval(int start, int end, int ind, int le, int ri, int x) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return tree[ind];
    if (le <= start && end <= ri) {
        if (tree[ind].Min >= x) {
            lazy[ind] = {-1,x};
            lazy_prop(start, end, ind);
            return tree[ind];
        }
        if (tree[ind].Max <= x) {
            return tree[ind];
        }
        if (tree[ind].sMax < x) {
            lazy[ind] = {1,x};
            lazy_prop(start, end, ind);
            return tree[ind];
        }
    }
    int mid = (start + end) / 2;
    Info l = update_interval(start, mid, ind * 2, le, ri, x);
    Info r = update_interval(mid + 1, end, ind * 2 + 1, le, ri, x);
    return tree[ind] = merge(l, r);
}

int max_interval(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind].Max;
    int mid = (start + end) / 2;
    return max(max_interval(start, mid, ind * 2, le, ri), max_interval(mid + 1, end, ind * 2 + 1, le, ri));
}

ll sum_interval(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return 0;
    if (le <= start && end <= ri) return tree[ind].Sum;
    int mid = (start + end) / 2;
    return sum_interval(start, mid, ind * 2, le, ri) + sum_interval(mid + 1, end, ind * 2 + 1, le, ri);
}

void solve() {
    int i, a, b, c, d; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init(1, n, 1);
    cin >> q;
    while (q--) {
        cin >> a >> b >> c;
        if (a == 1) {
            cin >> d;
            update_interval(1, n, 1, b, c, d);
        }
        else if (a == 2) {
            cout << max_interval(1, n, 1, b, c) << '\n';
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
