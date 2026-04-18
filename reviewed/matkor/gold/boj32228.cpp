#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n, m, arr[1000001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, ans; cin >> n >> m;
    for (i = 0; i < n; i++) cin >> arr[i];
    ans = m;
    for (i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            ans = ans * (i - 1) / i;
            while (m % i == 0) m /= i;
        }
    }
    if (m != 1) ans = ans * (m - 1) / m;
    cout << ans << '\n';
}
