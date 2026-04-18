#include<bits/stdc++.h>
#define pii pair<int, int>
#define l first
#define r second
using namespace std;

struct query {
    int ind, l, r;
};

int n, k, m, arr[100001], cnt[100001], sqrtcnt[350];
deque<int> dq[100001];
vector<query> q;
vector<int> ans;

bool cmp(query& a, query& b) {
    if (a.l / (int)sqrt(n) == b.l / (int)sqrt(n) && a.r < b.r) return 1;
    else if (a.l / (int)sqrt(n) < b.l / (int)sqrt(n)) return 1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i; cin >> n >> k;
    for (i = 1; i <= n; i++) cin >> arr[i];
    cin >> m;
    q.resize(m);
    ans.resize(m + 1);
    for (i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].ind = i + 1;
    }
    sort(q.begin(), q.end(), cmp);
    int le = q[0].l, ri = q[0].l, tmp = 0;
    while (ri <= q[0].r) {
        dq[arr[ri]].push_back(ri);
        tmp = max(tmp, dq[arr[ri]].back() - dq[arr[ri]].front());
        ri++;
    }
    ri--;
    ans[q[0].ind] = tmp;
    for (i = 0; i <= n; i++) {
        if (!dq[i].empty()) {
            int temp = dq[i].back() - dq[i].front();
            cnt[temp]++;
            sqrtcnt[temp / (int)sqrt(n)]++;
        }
    }
    cnt[0] += 100000001;
    sqrtcnt[0] += 100000001;
    for (i = 1; i < m; i++) {
        while (ri < q[i].r) {
            ri++;
            int temp;
            if (!dq[arr[ri]].empty()) {
                temp = dq[arr[ri]].back() - dq[arr[ri]].front();
                cnt[temp]--;
                sqrtcnt[temp / (int)sqrt(n)]--;
            }
            dq[arr[ri]].push_back(ri);
            temp = dq[arr[ri]].back() - dq[arr[ri]].front();
            cnt[temp]++;
            sqrtcnt[temp / (int)sqrt(n)]++;
        }
        while (ri > q[i].r) {
            int temp = dq[arr[ri]].back() - dq[arr[ri]].front();
            cnt[temp]--;
            sqrtcnt[temp / (int)sqrt(n)]--;
            dq[arr[ri]].pop_back();
            if (!dq[arr[ri]].empty()) {
                temp = dq[arr[ri]].back() - dq[arr[ri]].front();
                cnt[temp]++;
                sqrtcnt[temp / (int)sqrt(n)]++;
            }
            ri--;
        }
        while (le < q[i].l) {
            int temp = dq[arr[le]].back() - dq[arr[le]].front();
            cnt[temp]--;
            sqrtcnt[temp / (int)sqrt(n)]--;
            dq[arr[le]].pop_front();
            if (!dq[arr[le]].empty()) {
                temp = dq[arr[le]].back() - dq[arr[le]].front();
                cnt[temp]++;
                sqrtcnt[temp / (int)sqrt(n)]++;
            }
            le++;
        }
        while (le > q[i].l) {
            le--;
            int temp;
            if (!dq[arr[le]].empty()) {
                temp = dq[arr[le]].back() - dq[arr[le]].front();
                cnt[temp]--;
                sqrtcnt[temp / (int)sqrt(n)]--;
            }
            dq[arr[le]].push_front(le);
            temp = dq[arr[le]].back() - dq[arr[le]].front();
            cnt[temp]++;
            sqrtcnt[temp / (int)sqrt(n)]++;
        }
        int j, end_ = 0;
        for (j = (int)sqrt(n) + 1; j >= 0; j--) {
            if (sqrtcnt[j]) {
                end_ = j;
                break;
            }
        }
        for (j = min(100000, (end_ + 1) * (int)sqrt(n) - 1); j >= end_ * (int)sqrt(n); j--) {
            if (cnt[j]) {
                tmp = j;
                break;
            }
        }
        ans[q[i].ind] = tmp;
    }
    for (i = 1; i <= m; i++) cout << ans[i] << '\n';
}
