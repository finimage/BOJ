#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
#define x first
#define y second
using namespace std;

ll N, M;
vector<pll> arr;
vector<ll> order, dp, dp_, tree;

bool cmp1(pll a, pll b) {
    if (a.y - a.x * M > b.y - b.x * M) return 1;
    if (a.y - a.x * M == b.y - b.x * M) return a.x < b.x;
    return 0;
}

bool cmp2(pll a, pll b) {
    if (a.y + a.x * M < b.y + b.x * M) return 1;
    if (a.y + a.x * M == b.y + b.x * M) return a.x < b.x;
    return 0;
}

ll find_min(ll start, ll end, ll ind, ll le, ll ri) {
    if (ri < start || end < le) return N;
    if (le <= start && end <= ri) return tree[ind];
    ll mid = (start + end) / 2;
    return min(find_min(start, mid, ind * 2, le, ri), find_min(mid + 1, end, ind * 2 + 1, le, ri));
}

ll update(ll start, ll end, ll ind, ll i, ll val) {
    if (i < start || end < i) return tree[ind];
    if (start == end) return tree[ind] = val;
    ll mid = (start + end) / 2;
    return tree[ind] = min(update(start, mid, ind * 2, i, val), update(mid + 1, end, ind * 2 + 1, i, val));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i; cin >> N >> M;
    arr.resize(N + 1);
    order.resize(N + 1);
    dp.resize(N + 1);
    dp_.resize(N + 1);
    tree.resize(4 * N + 4, N);
    for (i = 1; i <= N; i++) {
        cin >> arr[i].y;
        arr[i].x = i;
        dp[i] = i - 1;
    }
    sort(arr.begin() + 1, arr.end(), cmp1);
    for (i = 1; i <= N; i++) order[arr[i].x] = i;
    sort(arr.begin() + 1, arr.end(), cmp2);
    for (i = 1; i <= N; i++) {
        ll tmp = find_min(1, N, 1, 1, order[arr[i].x]);
        dp[arr[i].x] = min(dp[arr[i].x], tmp + arr[i].x);
        update(1, N, 1, order[arr[i].x], dp[arr[i].x] - arr[i].x - 1);
    }
    for (i = 1; i <= N; i++) dp_[i] = min(dp[i - 1], dp_[i - 1]) + 1;
    cout << min(dp[N], dp_[N]);
}
