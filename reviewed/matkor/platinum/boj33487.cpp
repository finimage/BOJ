#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 998244353
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll n, l;
ll arr[1000001];

bool check(ld val) {
    ll i, sum = 0, ck = 1;
    vector<bool> v(n + 2);
    for (i = n; i > 0; i--) {
        sum += arr[i];
        if (sum + n - i > l) {
            sum -= arr[i];
            ck = i;
            break;
        }
        v[i] = 1;
    }
    ll a = n, b = n, dif = 0;
    ld aa = sum, bb = sum;
    v[n + 1] = 1;
    for (i = ck; i > 0; i--) {
        aa += arr[i];
        while (a > i && aa + val * (a - i) > l) {
            aa -= arr[a];
            if (v[a + 1]) dif++;
            a--;
        }
        bb += arr[i];
        while (b > i && bb + b - i > l) {
            bb -= arr[b];
            if (v[b + 1]) dif--;
            b--;
        }
        if (dif > 0) v[i] = 1;
        else if (arr[i] == 1) {
            if (l - 1 < val && v[i + 1]) v[i] = 1;
        }
        else {
            if ((ld)(l - arr[i]) / (arr[i] - 1) < val && v[i + 1]) v[i] = 1;
        }
    }
    return v[1];
}

void solve() {
    ll i; cin >> n >> l;
    ll sum = 0; ld Max = 0;
    for (i = 1; i <= n; i++) {
        cin >> arr[i];
        sum += arr[i];
        if (i < n) {
            if (arr[i] > 1) Max = max(Max, (ld)(l - arr[i]) / (arr[i] - 1));
            else Max = max(Max, (ld)l - arr[i]);
        }
    }
    cout << fixed << setprecision(10);
    if (n == 1) {
        cout << 0;
        return;
    }
    if (Max < 1) {
        cout << Max;
        return;
    }
    if (sum + n - 1 <= l) {
        cout << 1;
        return;
    }
    ld le = 1, ri = l, mid, cmp = 1e-9, ans;
    for (i = 0; i < 60; i++) {
        mid = (ri + le) / 2;
        if (check(mid)) ans = ri = mid;
        else le = mid;
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
