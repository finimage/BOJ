#include<bits/stdc++.h>
using namespace std;

int n, q, port[1000001];
set<int> ss;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int i, a, b, k; cin >> n >> q;
    for (i = 1; i <= n + 1; i++) ss.insert(i);
    for (i = 1; i <= q; i++) {
        cin >> a >> b;
        if (a == 1) {
            k = *ss.lower_bound(b);
            if (k == n + 1) cout << "-1\n";
            else {
                port[k] = i;
                ss.erase(k);
                cout << k << '\n';
            }
        }
        else {
            if (port[b]) {
                cout << port[b] << '\n';
                ss.insert(b);
                port[b] = 0;
            }
            else cout << "-1\n";
        }
    }
}
