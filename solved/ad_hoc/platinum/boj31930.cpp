#include<bits/stdc++.h>
using namespace std;

int val(char c) {
    return (c == 'O' ? 1 : 0);
}

void solve() {
    int n, i, cnt = 0, ans[2], v, k; char c; cin >> n;
    cout << "AK " << 1 << ' ' << n / 2 << endl;
    cin >> c;
    v = val(c);
    if (v == 1) {
        int le = 1, ri = n / 2, mid;
        while (le <= ri) {
            mid = (le + ri) / 2;
            cout << "AK " << le << ' ' << mid << endl;
            cin >> c;
            v = val(c);
            if (v == 1) {
                ans[0] = mid;
                ri = mid - 1;
            }
            else le = mid + 1;
        }
        le = n / 2 + 1;
        ri = n;
        while (le <= ri) {
            mid = (le + ri) / 2;
            cout << "AK " << le << ' ' << mid << endl;
            cin >> c;
            v = val(c);
            if (v == 1) {
                ans[1] = mid;
                ri = mid - 1;
            }
            else le = mid + 1;
        }
        cout << "! " << ans[0] << ' ' << ans[1] << endl;
        return;
    }
    if (n % 2) k = 1;
    else k = 0;
    for (i = 1; i < n / 2; i++) {
        cout << "AK " << 1 + i << ' ' << n - i << endl;
        cin >> c;
        v = val(c);
        if (cnt == 0 && v == 1) {
            cout << "AK " << i << ' ' << i << endl;
            cin >> c;
            v = val(c);
            if (v == 1) ans[cnt++] = i;
            else ans[cnt++] = n - i + 1;
        }
        else if (cnt == 1 && v == 0) {
            if (ans[0] > n / 2) ans[cnt++] = n - i + 1;
            else ans[cnt++] = i;
        }
        if (cnt >= 2) break;
    }
    if (k) {
        if (cnt == 1) {
            cout << "AK " << n / 2 + 1 << ' ' << n / 2 + 1 << endl;
            cin >> c;
            v = val(c);
            if (v == 1) ans[cnt++] = n / 2 + 1;
            else if (ans[0] > n / 2) ans[cnt++] = n / 2 + 2;
            else ans[cnt++] = n / 2;
        }
        if (cnt == 0) {
            ans[cnt++] = n / 2 + 1;
            ans[cnt++] = n / 2 + 2;
        }
    }
    else {
        if (cnt == 1) {
            if (ans[0] > n / 2) ans[cnt++] = n / 2 + 1;
            else ans[cnt++] = n / 2;
        }
    }
    cout << "! " << ans[0] << ' ' << ans[1] << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
