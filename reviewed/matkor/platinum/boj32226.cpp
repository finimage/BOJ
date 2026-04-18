#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

ld cal1(ld a, ld b, ld c) {
    return (b * b + c * c - a * a) / (2 * b * c);
}

ld cal2(ld t, ld a) {
    return a * a * (t - sin(t)) / 2;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll aa, bb, cc; cin >> aa >> bb >> cc;
    ld a = aa, b = bb, c = cc, p = 3.1415926535897932384626;
    ld t1 = acos(cal1(a, b, c)), t2 = acos(cal1(b, c, a)), t3 = acos(cal1(c, a, b));
    ld ans = 0;
    if (a * a + b * b > c * c) {
        ans += cal2(p - 2 * t1, a) + cal2(p - 2 * t2, b) + cal2(2 * t1 + 2 * t2 - p, c);
        ld a_ = 2 * a * sin(p / 2 - t1), b_ = 2 * b * sin(p / 2 - t2), c_ = 2 * c * sin(t1 + t2 - p / 2);
        ld s = (a_ + b_ + c_) / 2;
        ans += sqrt(s * (s - a_) * (s - b_) * (s - c_));
    }
    else ans += cal2(2 * t1, b) + cal2(2 * t2, a);
    cout << fixed << setprecision(15);
    cout << ans;
}
