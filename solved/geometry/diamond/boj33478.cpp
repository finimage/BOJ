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

ll a, b, c;

void solve() {
    ld s; cin >> a >> b >> c;
    s = (ld)(a + b + c) / 2;
    cout << fixed << setprecision(10);
    cout << sqrt(s * (s - a) * (s - b) * (s - c)) / s / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T = 1; cin >> T;
    while (T--) solve();
}
