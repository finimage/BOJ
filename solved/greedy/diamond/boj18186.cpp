#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll ans, b, c;
int n, arr[1000002], bb[1000002], cc[1000002];

void solve() {
    int i; cin >> n >> b >> c;
    for (i = 1; i <= n; i++) cin >> arr[i];
    if (b <= c) {
        for (i = 1; i <= n; i++) ans += arr[i];
        ans *= b;
        cout << ans;
        return;
    }
    bb[1] = arr[1];
    arr[1] = 0;
    ans += b * bb[1];
    for (i = 1; i <= n; i++) {
        int Min = min(bb[i], arr[i + 1]);
        arr[i + 1] -= Min;
        cc[i + 1] += Min;
        ans += c * Min;
        if (1 < i && i < n) {
            Min = min({bb[i - 1], cc[i], arr[i + 1]});
            arr[i + 1] -= Min;
            cc[i + 1] += Min;
            ans += c * Min;
        }
        bb[i + 1] = arr[i + 1];
        arr[i + 1] = 0;
        ans += b * bb[i + 1];
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
