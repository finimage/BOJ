#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define INF 1000000000000000001
using namespace std;

struct Info {
    ll Min, Min_ind;
};

struct Info_lazy {
    ll a, c, d;
    vector<ll> b;
    Info_lazy() {
        b.resize(10, 0);
    }
};

vector<ll> b0(10,0);
ll n, q, arr[100001];
Info tree[400004];
Info_lazy lazy[400004];

ll cal_d(ll val, int d, vector<ll> bb) {
    val += bb[0];
    for (int i = 0; i < min(d, 9); i++) {
        val = (ll)sqrt(val);
        val += bb[i + 1];
    }
    return val;
}

bool ck(vector<ll> b, vector<ll> b_) {
    for (int i = 0; i < 10; i++) {
        if (b[i] != b_[i]) return 0;
    }
    return 1;
}

void lazy_prop(int start, int end, int ind) {
    if (lazy[ind].a == 0 && ck(lazy[ind].b, b0) && lazy[ind].c == 0 && lazy[ind].d == 0) return;
    if (lazy[ind].a) {//3번 쿼리가 있었음
        ll a = lazy[ind].a, c = lazy[ind].c, d = lazy[ind].d;
        vector<ll> b = lazy[ind].b;
        tree[ind].Min = cal_d(a + c * tree[ind].Min_ind, d, b);
        lazy[ind].a = lazy[ind].c = lazy[ind].d = 0;
        lazy[ind].b = b0;
        if (start == end) return;
        lazy[ind * 2].a = a;
        lazy[ind * 2].b = b;
        lazy[ind * 2].c = c;
        lazy[ind * 2].d = d;
        lazy[ind * 2 + 1].a = a;
        lazy[ind * 2 + 1].b = b;
        lazy[ind * 2 + 1].c = c;
        lazy[ind * 2 + 1].d = d;
    }
    else {//3번 없었음 -> c도 0일 것
        ll a = lazy[ind].a, c = lazy[ind].c, d = lazy[ind].d;
        vector<ll> b = lazy[ind].b;
        tree[ind].Min = cal_d(tree[ind].Min, d, b);
        lazy[ind].a = lazy[ind].c = lazy[ind].d = 0;
        lazy[ind].b = b0;
        if (start == end) return;
        //자식들은 3번 쿼리 미처리 상태일 수 있음
        for (int i = 0; i < 10; i++) lazy[ind * 2].b[min(i + lazy[ind * 2].d, 9LL)] += b[i];
        lazy[ind * 2].d += d;
        for (int i = 0; i < 10; i++) lazy[ind * 2 + 1].b[min(i + lazy[ind * 2 + 1].d, 9LL)] += b[i];
        lazy[ind * 2 + 1].d += d;
    }
}

Info init(int start, int end, int ind) {
    if (start == end) return tree[ind] = {arr[end],end};
    int mid = (start + end) / 2;
    return tree[ind] = {min(init(start, mid, ind * 2).Min, init(mid + 1, end, ind * 2 + 1).Min), start};
}

ll find_Min(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return INF;
    if (le <= start && end <= ri) return tree[ind].Min;
    int mid = (start + end) / 2;
    return min(find_Min(start, mid, ind * 2, le, ri), find_Min(mid + 1, end, ind * 2 + 1, le, ri));
}

ll q1(int start, int end, int ind, int i) {
    lazy_prop(start, end, ind);
    if (i < start || end < i) return 0;
    if (start == end) return tree[ind].Min;
    int mid = (start + end) / 2;
    return q1(start, mid, ind * 2, i) + q1(mid + 1, end, ind * 2 + 1, i);
}

void q2(int start, int end, int ind, int le, int ri, ll b) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        lazy[ind].b[0] = b;
        lazy_prop(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    q2(start, mid, ind * 2, le, ri, b);
    q2(mid + 1, end, ind * 2 + 1, le, ri, b);
    tree[ind].Min = min(tree[ind * 2].Min, tree[ind * 2 + 1].Min);
}

void q3(int start, int end, int ind, int le, int ri, ll a, ll b) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        vector<ll> b1 = b0;
        b1[0] += b;
        lazy[ind].a = a;
        lazy[ind].c = 1;
        lazy[ind].d = 0;
        lazy[ind].b = b1;
        lazy_prop(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    q3(start, mid, ind * 2, le, ri, a, b);
    q3(mid + 1, end, ind * 2 + 1, le, ri, a, b);
    tree[ind].Min = min(tree[ind * 2].Min, tree[ind * 2 + 1].Min);
}

void q4(int start, int end, int ind, int le, int ri) {
    lazy_prop(start, end, ind);
    if (ri < start || end < le) return;
    if (le <= start && end <= ri) {
        lazy[ind].d++;
        lazy_prop(start, end, ind);
        return;
    }
    int mid = (start + end) / 2;
    q4(start, mid, ind * 2, le, ri);
    q4(mid + 1, end, ind * 2 + 1, le, ri);
    tree[ind].Min = min(tree[ind * 2].Min, tree[ind * 2 + 1].Min);
}

void solve() {
    ll i, a, b, c, d; cin >> n >> q;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init(1, n, 1);
    while (q--) {
        cin >> a >> b;
        if (a == 1) {
            cout << q1(1, n, 1, b) << '\n';
        }
        else if (a == 2) {
            cin >> c >> d;
            //cout << "Min" << ' ' << find_Min(1, n, 1, b, c) << '\n';
            if (find_Min(1, n, 1, b, c) < d) continue;
            q2(1, n, 1, b, c, -d);
        }
        else if (a == 3) {
            cin >> c >> d;
            q3(1, n, 1, b, c, d, -c);
        }
        else {
            cin >> c;
            q4(1, n, 1, b, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
