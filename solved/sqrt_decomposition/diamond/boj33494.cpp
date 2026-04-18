#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define x first
#define y second
#define MOD 1000000007
using namespace std;

int n, k, q;
int arr[2001001];
vector<int> arr2[2520];
int lazy[2520], cnt[2520];
ll sum[2520];

void update(int ind, int start, int end) {
    int i, j = 0; ll tmp = 0;
    for (i = ind * 900 - 899; i <= min(n, ind * 900); i++) {
        if (start <= i && i <= end) arr[i] = (arr[i] + lazy[ind] + 1) % k;
        else arr[i] = (arr[i] + lazy[ind]) % k;
        tmp += arr[i];
        arr2[ind][j++] = arr[i];
    }
    sum[ind] = tmp;
    lazy[ind] = 0;
    tmp = 0;
    sort(arr2[ind].begin(), arr2[ind].begin() + j);
}

void q1(int start, int end) {
    int i;
    int le = (start - 1) / 900 + 1;
    update(le, start, end);
    int ri = (end - 1) / 900 + 1;
    if (le != ri) update(ri, start, end);
    for (i = le + 1; i < ri; i++) lazy[i] = (lazy[i] + 1) % k;
}

void q2(int start, int end) {
    int i; ll res = 0;
    int le = (start - 1) / 900 + 1;
    if (lazy[le]) update(le, -1, -1);
    int ri = (end - 1) / 900 + 1;
    if (le != ri && lazy[ri]) update(ri, -1, -1);
    if (le == ri) {
        for (i = start; i <= end; i++) res += arr[i];
        cout << res << '\n';
        return;
    }
    for (i = start; i <= le * 900; i++) res += arr[i];
    for (i = ri * 900 - 899; i <= end; i++) res += arr[i];
    for (i = le + 1; i < ri; i++) {
        if (lazy[i]) {
            auto tmp = lower_bound(arr2[i].begin(), arr2[i].end(), k - lazy[i]) - arr2[i].begin();
            if (arr2[i][tmp] > k) {
                res += sum[i] + (ll)lazy[i] * cnt[i];
                continue;
            }
            res += sum[i] + (ll)lazy[i] * cnt[i] - (ll)k * (cnt[i] - tmp);
        }
        else res += sum[i];
    }
    cout << res << '\n';
}

void solve() {
    int i, j, a, b, c; cin >> n >> k;
    if (k == 1) {
        for (i = 1; i <= n; i++) cin >> arr[i];
        cin >> q;
        while (q--) {
            cin >> a >> b >> c;
            if (a == 2) cout << 0 << '\n';
        }
        return;
    }
    for (i = 1; i <= 2500; i++) arr2[i].resize(901, k + 1);
    j = 0;
    for (i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] %= k;
        int ind = (i - 1) / 900 + 1;
        sum[ind] += arr[i];
        cnt[ind]++;
        arr2[ind][j++] = arr[i];
        if (j == 900 || i == n) {
            sort(arr2[ind].begin(), arr2[ind].begin() + j);
            j = 0;
        }
    }
    cin >> q;
    while (q--) {
        cin >> a >> b >> c;
        if (a == 1) q1(b, c);
        else q2(b, c);
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
