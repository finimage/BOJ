#include<iostream>
#include<cmath>
#define ll long long
using namespace std;

int ans[10], check[10] = {0,1,20,300,4000,50000,600000,7000000,80000000,900000000};

void solve(int n, string s, int l) {
    int i, t = (int)pow(10, l - 1);
    ll k = (ll)l * (ll)(n - t + 1);
    t = 9;
    for (i = 1; i < l; i++) {
        k += (ll)i * t;
        t *= 10;
    }
    for (i = 1; i < 10; i++) k -= (ll)ans[i];
    cout << k << ' ';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n = 0, i, j, t, k, l;
    string s; cin >> s;
    l = s.size();
    for (i = 0; i < l; i++) n = n * 10 + s[i] - '0';
    for (i = 0; i < l; i++) {
        k = s[i] - '0';
        if (i == l - 1) {
            for (j = 1; j <= k; j++) ans[j]++;
            continue;
        }
        for (j = 1; j < k; j++) {
            for (t = 1; t < 10; t++) ans[t] += check[l - i - 1];
            ans[j] += (int)pow(10, l - i - 1);
        }
        if (k != 0) {
            for (t = 1; t < 10; t++) ans[t] += check[l - i - 1];
            ans[k] += n % (int)pow(10, l - i - 1) + ((l - i - 1) ? 1 : 0);
        }
    }
    solve(n, s, l);
    for (i = 1; i < 10; i++) cout << ans[i] << ' ';
}
