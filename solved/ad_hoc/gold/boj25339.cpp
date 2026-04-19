#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

ll n, q;

void solve() {
    ll ans = 0, a, b, c; cin >> n >> q;
    while (q--) {
        cin >> a >> b >> c;
        if (a == 1) ans = !ans;
        else ans = (c - b + 1) * (c - b) / 2 % 2 ? !ans : ans;
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
