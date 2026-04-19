#include<bits/stdc++.h>
using namespace std;

int l, k, c, stk;
vector<int> v;
set<int> ss;

int check(int val) {
    int st = l, ccnt = 0, i;
    for (i = k - 1; i >= 0; i--) {
        if (st - v[i] > val) return c + 1;
        else {
            if (i > 0 && st - v[i - 1] > val) {
                stk = v[i];
                ccnt++;
                st = v[i];
            } 
        }
    }
    return ccnt;
}

void bs() {
    int le = 1, ri = l, mid, ret = 0, cnt;
    while (le <= ri) {
        mid = (le + ri) / 2;
        cnt = check(mid);
        if (cnt <= c) {
            ret = mid;
            ri = mid - 1;
        } 
        else le = mid + 1;
    }
    cout << ret << ' ';
    if (check(ret) == c) cout << stk;
    else cout << v[1];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int i, a; cin >> l >> k >> c;
    for (i = 1; i <= k; i++) {
        cin >> a;
        ss.insert(a);
    }
    ss.insert(0);
    ss.insert(l);
    k = ss.size();
    v.resize(k);
    i = 0;
    for (auto& iter : ss) v[i++] = iter;
    bs();
}
