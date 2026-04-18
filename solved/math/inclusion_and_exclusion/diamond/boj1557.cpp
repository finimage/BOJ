#include<bits/stdc++.h>
#define ll long long
using namespace std;

int p[50001];
vector<ll> prime;

void find_prime() {
    int i, j;
    for (i = 2; i <= 50000; i++) p[i] = 1;
    for (i = 2; i <= 50000; i++) {
        if (p[i]) {
            prime.push_back(i);
            for (j = i * 2; j <= 50000; j += i) p[j] = 0;
        }
    }
}

ll f(ll a) {
    int i1, i2, i3, i4, i5, i6, l = prime.size();
    __int128 p1, p2, p3, p4, p5, p6;
    ll cnt = a;
    for (i1 = 0; i1 < l; i1++) {
        p1 = prime[i1] * prime[i1];
        if (a < p1) break;
        cnt -= a / p1;
        for (i2 = i1 + 1; i2 < l; i2++) {
            p2 = p1 * prime[i2] * prime[i2];
            if (a < p2) break;
            cnt += a / p2;
            for (i3 = i2 + 1; i3 < l; i3++) {
                p3 = p2 * prime[i3] * prime[i3];
                if (a < p3) break;
                cnt -= a / p3;
                for (i4 = i3 + 1; i4 < l; i4++) {
                    p4 = p3 * prime[i4] * prime[i4];
                    if (a < p4) break;
                    cnt += a / p4;
                    for (i5 = i4 + 1; i5 < l; i5++) {
                        p5 = p4 * prime[i5] * prime[i5];
                        if (a < p5) break;
                        cnt -= a / p5;
                        for (i6 = i5 + 1; i6 < l; i6++) {
                            p6 = p5 * prime[i6] * prime[i6];
                            if (a < p6) break;
                            cnt += a / p6;
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll le = 1, ri = 2000000001, mid, n, k; cin >> n;
    find_prime();
    while (le <= ri) {
        mid = (le + ri) / 2;
        k = f(mid);
        if (k == n) break;
        else if (k > n) ri = mid - 1;
        else le = mid + 1;
    }
    for (int i = 0; i < prime.size(); i++) {
        if (mid % (prime[i] * prime[i]) == 0) {
            mid--;
            i = -1;
        }
    }
    cout << mid;
}
