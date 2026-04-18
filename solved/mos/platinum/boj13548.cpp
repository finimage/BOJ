#include<bits/stdc++.h>
using namespace std;

struct query {
    int ind, l, r;
};

int n, m, arr[100001], cnt[100001], cntcnt[100001];
vector<query> q;
vector<int> ans;

bool cmp(query& a, query& b) {
    if (a.l / (int)sqrt(n) < b.l / (int)sqrt(n)) return 1;
    else if (a.l / (int)sqrt(n) == b.l / (int)sqrt(n) && a.r < b.r) return 1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i; cin >> n;
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
    cntcnt[0] = 100001;
    while (ri <= q[0].r) {
        cntcnt[cnt[arr[ri]]]--;
        cnt[arr[ri]]++;
        cntcnt[cnt[arr[ri]]]++;
        tmp = max(tmp, cnt[arr[ri]]);
        ri++;
    }
    ri--;
    ans[q[0].ind] = tmp;
    for (i = 1; i < m; i++) {
        while (le < q[i].l) {
            cntcnt[cnt[arr[le]]]--;
            if (cntcnt[cnt[arr[le]]] == 0 && cnt[arr[le]] == tmp) tmp--;
            cnt[arr[le]]--;
            cntcnt[cnt[arr[le]]]++;
            le++;
        }
        while (le > q[i].l) {
            le--;
            cntcnt[cnt[arr[le]]]--;
            cnt[arr[le]]++;
            cntcnt[cnt[arr[le]]]++;
            tmp = max(tmp, cnt[arr[le]]);
        }
        while (ri < q[i].r) {
            ri++;
            cntcnt[cnt[arr[ri]]]--;
            cnt[arr[ri]]++;
            cntcnt[cnt[arr[ri]]]++;
            tmp = max(tmp, cnt[arr[ri]]);
        }
        while (ri > q[i].r) {
            cntcnt[cnt[arr[ri]]]--;
            if (cntcnt[cnt[arr[ri]]] == 0 && cnt[arr[ri]] == tmp) tmp--;
            cnt[arr[ri]]--;
            cntcnt[cnt[arr[ri]]]++;
            ri--;
        }
        ans[q[i].ind] = tmp;
    }
    for (i = 1; i <= m; i++) cout << ans[i] << '\n';
}
