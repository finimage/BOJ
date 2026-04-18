#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

int n, q;
int arr[100001];
vector<int> arr_[320];

void init() {
    int i, j = 0;
    for (i = 1; i <= n; i++) {
        if (i % 320 == 1) j++;
        arr_[j].push_back(arr[i]);
    }
    for (i = 1; i < 320; i++) sort(arr_[i].begin(), arr_[i].end());
}

void q1(int a, int b) {
    int ind = (a - 1) / 320 + 1, pre = arr[a];
    arr[a] = b;
    int tmp = lower_bound(arr_[ind].begin(), arr_[ind].end(), pre) - arr_[ind].begin();
    arr_[ind][tmp] = b;
    sort(arr_[ind].begin(), arr_[ind].end());
}

void q2(int le, int ri, int k) {
    int i, indle = (le - 1) / 320 + 1, indri = (ri - 1) / 320 + 1, ans = 0;
    if (indle == indri) {
        for (i = le; i <= ri; i++) ans += arr[i] > k;
        cout << ans << '\n';
        return;
    }
    for (i = le; i <= indle * 320; i++) ans += arr[i] > k;
    for (i = (indri - 1) * 320 + 1; i <= ri; i++) ans += arr[i] > k;
    for (i = indle + 1; i < indri; i++) {
        int tmp = arr_[i].end() - upper_bound(arr_[i].begin(), arr_[i].end(), k);
        ans += tmp;
    }
    cout << ans << '\n';
}

void solve() {
    int i, a, b, c, d; cin >> n;
    for (i = 1; i <= n; i++) cin >> arr[i];
    init();
    cin >> q;
    while (q--) {
        cin >> a >> b >> c;
        if (a == 2) q1(b, c);
        else {
            cin >> d;
            q2(b, c, d);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int T = 1; //cin >> T;
    while (T--) solve();
}
