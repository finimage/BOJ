#include<bits/stdc++.h>
#define ll int
#define ld double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 998244353
using namespace std;

#define cpx complex<ld>
#define poly vector<cpx>

void fft(poly &a, bool inv) {
    ll l = a.size(), i, j = 0, t;

    for (i = 1; i < l; i++) {
        ll bit = l >> 1;
        while (j >= bit) {
            j -= bit;
            bit /= 2;
        }
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (t = 1; t < l; t <<= 1) {
        double val = (inv ? acos(-1) / t : -acos(-1) / t);
        cpx w(cos(val), sin(val));
        for (i = 0; i < l; i += t * 2) {
            cpx tmp(1, 0);
            for (j = 0; j < t; j++) {
                cpx x = a[i + j];
                cpx y = a[i + j + t] * tmp;
                a[i + j] = x + y;
                a[i + j + t] = x - y;
                tmp *= w;
            }
        }
    }

    if (inv) {
        for (i = 0; i < l; i++) a[i] /= l;
    }
}

poly mul(poly& a, poly& b) {
    ll l = 2, i;
    while (l < a.size() + b.size()) l <<= 1;
    a.resize(l);
    fft(a, 0);
    b.resize(l);
    fft(b, 0);
    vector<cpx> c(l);
    for (i = 0; i < l; i++) c[i] = a[i] * b[i];
    fft(c, 1);
    return c;
}

vector<ll> ans;

void solve() {
    ll i; string a, b; cin >> a >> b;
    if (a == "0" || b == "0") {
        cout << 0;
        return;
    }
    poly A(a.size()), B(b.size());
    for (i = 0; i < a.size(); i++) A[i] = cpx(a[i] - '0', 0);
    reverse(A.begin(), A.end());
    for (i = 0; i < b.size(); i++) B[i] = cpx(b[i] - '0', 0);
    reverse(B.begin(), B.end());
    poly C = mul(A, B);
    ans.resize(C.size());
    for (i = 0; i < C.size(); i++) ans[i] = round(C[i].real());
    for (i = 0; i + 1 < C.size(); i++) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    ll tf = 1;
    reverse(ans.begin(), ans.end());
    for (auto& iter : ans) {
        if (tf && iter == 0) continue;
        tf = 0;
        cout << iter;
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
