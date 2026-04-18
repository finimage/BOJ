#include<iostream>
#define ll long long
using namespace std;

void solve() {
    ll x = 0, a = 0, b = 0, le, ri, mid, cnt = 0, t = 30;
    bool tf = 1;
    char tmp;
    while (tf) {
        le = 0, ri = (1 << t);
        while (le <= ri) {
            mid = (le + ri) / 2;
            cnt++;
            cout << "? " << a << ' ' << mid << endl;
            cin >> tmp;
            if (tmp == '0') {
                b = mid;
                x = b * b + a;
                tf = 0;
                break;
            }
            else if (tmp == '+') {
                le = mid + 1;
                b = mid;
            }
            else ri = mid - 1;
        }
        a += b * b;
        t = t / 2 + 1;
    }
    cout << "! " << x << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
