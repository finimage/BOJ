#include<bits/stdc++.h>
#define ld long double
using namespace std;

int n;
ld b, x[100001], y[100001];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ld le = -2e7, ri = 2e7, mid, sum;
    int i; cin >> n >> b;
    for (i = 0; i < n; i++) cin >> x[i] >> y[i];
    while (le < ri) {
        mid = (le + ri) / 2;
        sum = 0;
        for (i = 0; i < n; i++) sum += (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]);
        if (sum > 0) le = mid;
        else ri = mid;
        if (ri - le <= 0.0000001) {
            printf("%.10Lf", mid);
            break;
        }
    }
}
