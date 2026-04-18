#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
using namespace std;

ll n;

void solve() {
    cin >> n;
    if (n <= 2) cout << -1;
    else {
        ll i;
        for (i = 1; i <= n; i++) {
            cout << i << ' ' << i * (i - 1) / 2 << '\n';
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
