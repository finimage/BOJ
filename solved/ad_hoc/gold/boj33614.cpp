#include<bits/stdc++.h>
using namespace std;

void solve() {
    int p, q, r; cin >> p >> q >> r;
    cout << p - 1 + min(q, r) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
