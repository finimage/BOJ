#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

ll n;
vector<ll> par;
vector<pll> arr, sarr;

ll find_(ll a) {
    if (a == par[a]) return a;
    return par[a] = find_(par[a]);
}

bool union_(ll a, ll b) {
    a = find_(a);
    b = find_(b);
    if (a == b) return 1;
    if (a < b) swap(a, b);
    par[b] = a;
    return 0;
}

bool check(ll dif) {
    ll i; bool tf = 1;
    for (i = 0; i < n; i++) par[i] = i;
    for (i = 1; i < n; i++) {
        if (sarr[i].x - sarr[i - 1].x <= dif) union_(sarr[i].y, sarr[i - 1].y);
    }
    for (i = 1; i < n; i++) {
        if (arr[find_(i - 1)] > arr[find_(i)]) {
            tf = 0;
            break;
        }
    }
    return tf;
}

void solve() {
    ll i, le, ri, mid, ans = 0; cin >> n;
    arr.resize(n);
    par.resize(n);
    for (i = 0; i < n; i++) {
        cin >> arr[i].x;
        arr[i].y = i;
    }
    sarr = arr;
    sort(sarr.begin(), sarr.end());
    le = 0;
    ri = 1000000000000000000;
    while (le <= ri) {
        mid = (le + ri) / 2;
        if (check(mid)) {
            ans = mid;
            ri = mid - 1;
        }
        else le = mid + 1;
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
