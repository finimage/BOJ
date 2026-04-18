#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;
 
int n, m;
int output2[100001];
 
void solve() {
    int i; cin >> n >> m;
    for (i = 0; i < m; i++) cin >> output2[i];
    if (n == 2) {
        for (i = 1; i < m; i++) {
            if (output2[i] != output2[i - 1]) {
                cout << "-1\n";
                return;
            }
        }
        cout << "1\n";
        if (output2[0] == 1) {
            cout << "1 0 10\n";
            cout << "1 0 10\n";
            for (i = 0; i < m; i++) cout << "2 1 2\n";
        }
        else {
            cout << "1 0 10\n";
            cout << "1 10 20\n";
            for (i = 0; i < m; i++) cout << "2 1 2\n";
        }
    }
    else {
        cout << "1\n";
        cout << "1 0 10\n";
        cout << "1 0 10\n";
        cout << "1 10 20\n";
        for (i = 0; i < m; i++) {
            if (output2[i] == 1) cout << "2 1 2\n";
            else cout << "2 1 3\n";
        }
        for (i = 3; i < n; i++) cout << "1 0 10\n";
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}

/*
checker 버전
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

struct Q_Info {
    ll a, b, c;
};

struct Info {
    ll val, lr, ind;
};

bool cmp(Info a, Info b) {
    if (a.val == b.val) return a.lr < b.lr;
    return a.val < b.val;
}

ll n, q;
vector<Info> arr;
vector<pll> v;
vector<Q_Info> query;
vector<ll> par;

ll find_(ll a) {
    if (a == par[a]) return a;
    return par[a] = find_(par[a]);
}

ll union_(ll a, ll b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (a > b) swap(a, b);
    par[a] = b;
    return 0;
}

void upt(int k) {
    int i;
    for (i = v[k].x; i < v[k].y; i++) {
        if (find_(i) == i) union_(i, i + 1);
        else i = find_(i) - 1;
    }
}

int is_link(int a, int b) {
    return find_(v[a].x) == find_(v[b].x) ? 1 : 0;
}

void solve() {
    ll i, k = 0; cin >> q;
    query.resize(q);
    for (i = 0; i < q; i++) {
        cin >> query[i].a >> query[i].b >> query[i].c;
        if (query[i].a == 1) {
            arr.push_back({query[i].b,1,++n});
            arr.push_back({query[i].c,0,n});
        }
    }
    v.resize(n + 1);
    n = arr.size();
    sort(arr.begin(), arr.end(), cmp);
    for (auto& iter : arr) {
        (iter.lr ? v[iter.ind].x : v[iter.ind].y) = ++k;
    }
    par.resize(n + 1);
    for (i = 1; i <= n; i++) par[i] = i;
    k = 0;
    for (auto& iter : query) {
        if (iter.a == 1) upt(++k);
        else cout << is_link(iter.b, iter.c) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
*/
