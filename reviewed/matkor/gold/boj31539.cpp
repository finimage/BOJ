#include<bits/stdc++.h>
#define ld long double
using namespace std;

int n;
ld b, x[100001], y[100001], A, B, C;

ld cal(ld a) {
    int i;
    ld sum = 0;
    for (i = 0; i < n; i++) sum += (y[i] - b - a * x[i]) * (y[i] - b - a * x[i]) * (y[i] - b - a * x[i]) * (y[i] - b - a * x[i]);
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i; cin >> n >> b;
    for (i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        A += 12 * x[i] * x[i] * x[i] * x[i];
        B += 24 * x[i] * x[i] * x[i] * (b - y[i]);
        C += 12 * x[i] * x[i] * (b - y[i]) * (b - y[i]);
    }
    ld D = B * B - 4 * A * C;
    ld le = -2e7, ri = 2e7, mid, sum;
    if (D <= 0) {
        while (le < ri) {
            mid = (le + ri) / 2;
            sum = 0;
            for (i = 0; i < n; i++) sum -= 4 * x[i] * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]);
            if (sum > 0) ri = mid;
            else le = mid;
            if (ri - le <= 0.0000001) {
                printf("%.10Lf", mid);
                break;
            }
        }
    }
    else {
        ld a_ = (-B - sqrt(D)) / 2 / A, b_ = (-B + sqrt(D)) / 2 / A, ans1, ans2, asum = 0, bsum = 0;
        for (i = 0; i < n; i++) asum -= 4 * x[i] * (y[i] - b - a_ * x[i]) * (y[i] - b - a_ * x[i]) * (y[i] - b - a_ * x[i]);
        for (i = 0; i < n; i++) bsum -= 4 * x[i] * (y[i] - b - a_ * x[i]) * (y[i] - b - b_ * x[i]) * (y[i] - b - b_ * x[i]);
        if (asum > 0 && bsum > 0) {
            while (le < a_) {
                mid = (le + a_) / 2;
                sum = 0;
                for (i = 0; i < n; i++) sum -= 4 * x[i] * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]);
                if (sum > 0) a_ = mid;
                else le = mid;
                if (a_ - le <= 0.0000001) {
                    printf("%.10Lf", mid);
                    break;
                }
            }
        }
        else if (asum > 0 && bsum < 0) {
            while (le < a_) {
                mid = (le + a_) / 2;
                sum = 0;
                for (i = 0; i < n; i++) sum -= 4 * x[i] * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]);
                if (sum > 0) a_ = mid;
                else le = mid;
                if (a_ - le <= 0.0000001) {
                    ans1 = mid;
                    break;
                }
            }
            while (b_ < ri) {
                mid = (b_ + ri) / 2;
                sum = 0;
                for (i = 0; i < n; i++) sum -= 4 * x[i] * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]);
                if (sum > 0) ri = mid;
                else b_ = mid;
                if (ri - b_ <= 0.0000001) {
                    ans2 = mid;
                    break;
                }
            }
            if (cal(ans1) < cal(ans2)) printf("%.10Lf", ans1);
            else printf("%.10Lf", ans2);
        }
        else {
            while (b_ < ri) {
                mid = (b_ + ri) / 2;
                sum = 0;
                for (i = 0; i < n; i++) sum -= 4 * x[i] * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]) * (y[i] - b - mid * x[i]);
                if (sum > 0) ri = mid;
                else b_ = mid;
                if (ri - b_ <= 0.0000001) {
                    printf("%.10Lf", mid);
                    break;
                }
            }
        }
    }
}
