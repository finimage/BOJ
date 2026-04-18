#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll n, k, arr[100001], check[100001];
vector<ll> pprime, prime, primecnt;

ll gcd(ll a, ll b) {
    while (b) {
        ll r = a % b;
        a = b;
        b = r;
    }
    return a;
}

ll res(ll a, ll b) {
    ll ret = 1;
	while (b){
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

ll vp(ll p, ll val) {
    ll ret = 0;
    while (val % p == 0) {
        val /= p;
        ret++;
    }
    return ret;
}

void process(ll GCD) {
    ll i, j;
    for (i = 2; i <= 100000; i++) check[i] = 1;
    for (i = 2; i <= 100000; i++) {
        if (check[i]) {
            pprime.emplace_back(i);
            for (j = i * i; j <= 100000; j += i) check[j] = 0;
        }
    }
    for (auto& iter : pprime) {
        if (GCD % iter == 0) {
            prime.emplace_back(iter);
            while (GCD % iter == 0)  GCD /= iter;
        }
    }
    if (GCD != 1) prime.emplace_back(GCD);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll i, j; cin >> n >> k;
    for (i = 0; i < n; i++) cin >> arr[i];
    ll GCD = arr[1] - arr[0];
    for (i = 2; i < n; i++) GCD = gcd(GCD, arr[i] - arr[i - 1]);
    ll tmp = gcd(GCD, arr[n - 1]);
    while (tmp != 1 && GCD % tmp == 0) {
        GCD /= tmp;
        tmp = gcd(GCD, arr[n - 1]);
    }
    if (GCD == 1 || k == 1) {
        cout << 1;
        return 0;
    }
    process(GCD);
    primecnt.resize(prime.size());
    ll ans = 1, tf = 0;
    if (prime[0] == 2) {
        while (GCD % 2 == 0) {
            GCD /= 2;
            primecnt[0]++;
        }
        tmp = 0;
        for (i = 1; i < n; i++) {
            ll a = abs(arr[i - 1]), b = abs(arr[i]);
            if (arr[i - 1] <= 0 && arr[i] >= 0) {
                if (k * primecnt[0] == 1) tmp = max(tmp, (ll)1);
                else {
                    cout << -1;
                    return 0;
                }
            }
            else {
                ll apb = vp(2, a + b);
                ll amb = vp(2, abs(a - b));
                tmp = max(tmp, max((ll)1, primecnt[0] * k - amb - apb + 1));
            }
        }
        if (tmp > 0) tf = 1;
        ans = res(2, tmp);
    }
    for (i = prime[0] == 2; i < prime.size(); i++) {
        while (GCD % prime[i] == 0) {
            GCD /= prime[i];
            primecnt[i]++;
        }
        tmp = 0;
        for (j = 1; j < n; j++) {
            ll a = abs(arr[j - 1]), b = abs(arr[j]);
            ll apb = vp(prime[i], a + b);
            ll amb = vp(prime[i], abs(a - b));
            if (arr[j - 1] <= 0 && arr[j] >= 0) {
                if (tf) {
                    cout << -1;
                    return 0;
                }
                else tmp = max(tmp, k * primecnt[i] - apb);
            }
            else tmp = max(tmp, k * primecnt[i] - amb);
        }
        ans = ans * res(prime[i] % MOD, tmp) % MOD;
    }
    cout << ans;
}
