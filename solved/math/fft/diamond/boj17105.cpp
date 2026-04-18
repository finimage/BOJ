#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 998244353
using namespace std;

#define cpx complex<double>
#define poly vector<cpx>

void fft(poly &a, bool inv) {
    int l = a.size(), i, j = 0, t;
    for (i = 1; i < l; i++) {
        int bit = l >> 1;
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
    int l = 2, i;
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

vector<int> sieve, ans1, ans2, ans3;
poly C;

void solve() {
    int n; cin >> n;
    cout << ans1[n] << '\n';
}

void pre() {
    int n, i, j; n = 1000000;
    sieve.resize(n, 1);
    sieve[0] = sieve[1] = 0;
    for (i = 2; i < n; i++) {
        if (sieve[i]) {
            for (j = i * 2; j < n; j += i) sieve[j] = 0;
        }
    }
    ans1.resize(n);
    for (i = 2; i < n; i++) {
        if (3 * i >= n) break;
        if (sieve[i]) ans1[3 * i]++;
    }
    poly A(n), B(n), D;
    for (i = 0; i < n; i++) A[i] = B[i] = cpx(sieve[i], 0);
    C = mul(A, B);
    A.resize(n);
    B.resize(n);
    for (i = 0; i < n; i++) {
        A[i] = cpx((int)(round(C[i].real()) + 1) / 2, 0);
        B[i] = cpx(sieve[i], 0);
    }
    D = mul(A, B);
    ans2.resize(n);
    for (i = 5; i < n; i++) ans2[i] = round(D[i].real());
    A.resize(n);
    B.resize(n);
    for (i = 0; i < n; i++) {
        A[i] = cpx((int)round(C[i].real()) / 2, 0);
        B[i] = cpx(sieve[i], 0);
    }
    D.clear();
    D = mul(A, B);
    ans3.resize(n);
    for (i = 5; i < n; i++) ans3[i] = round(D[i].real());
    for (i = 5; i < n; i++) {
        ans3[i] = ans2[i] - ans3[i] - ans1[i];
        ans1[i] += (ans2[i] - 2 * ans3[i] - ans1[i]) / 3 + ans3[i];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifdef LOCAL_DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    pre();
    int T = 1; cin >> T;
    while (T--) solve();
}
