#include<iostream>
#define ll long long
using namespace std;

struct info {
    ll v, s, e;
};

info a, b, c;


ll f(info a, info b, info c) {
    ll k = a.v * b.v, ans = 1e11, tmp;
    tmp = c.s;
    while (k--) {
        if (a.s <= tmp % a.v && tmp % a.v <= a.e && b.s <= tmp % b.v && tmp % b.v <= b.e) {
            ans = min(ans, tmp);
            break;
        }
        tmp += c.v;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> a.v >> a.s >> a.e;
    cin >> b.v >> b.s >> b.e;
    cin >> c.v >> c.s >> c.e;
    ll ans = min(min(f(a,b,c), f(b,c,a)), f(c,a,b));
    cout << (ans == 1e11 ? -1 : ans);
}
