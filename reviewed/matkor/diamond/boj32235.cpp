#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

struct Info {
    ll cnt, s, ss;
};

struct info {
    Info v[6][6];
};

ll n, q;
info tree[400004], nono;
string S, matkor = "MATKOR";

info cal(ll le, ll ri, ll mid, info l, info r) {
    info tmp;
    ll i, j, t, lsz = mid - le + 1, rsz = ri - mid;
    for (i = 0; i < 6; i++) {
        for (j = i; j < 6; j++) {
            tmp.v[i][j].cnt = (l.v[i][j].cnt + r.v[i][j].cnt) % MOD;
            tmp.v[i][j].s = (l.v[i][j].s + rsz * l.v[i][j].cnt % MOD + r.v[i][j].s + lsz * r.v[i][j].cnt % MOD) % MOD;
            tmp.v[i][j].ss = (l.v[i][j].ss + l.v[i][j].s * rsz % MOD * 2 + rsz * rsz % MOD * l.v[i][j].cnt % MOD + r.v[i][j].ss + r.v[i][j].s * lsz % MOD * 2 + lsz * lsz % MOD * r.v[i][j].cnt % MOD) % MOD;
            if (i == j) continue;
            else {
                 for (t = i; t < j; t++) {
                    tmp.v[i][j].cnt = (tmp.v[i][j].cnt + (l.v[i][t].cnt * r.v[t + 1][j].cnt) % MOD) % MOD;
                    tmp.v[i][j].s = (tmp.v[i][j].s + l.v[i][t].s * r.v[t + 1][j].cnt % MOD + l.v[i][t].cnt * r.v[t + 1][j].s % MOD) % MOD;
                    tmp.v[i][j].ss = (tmp.v[i][j].ss + l.v[i][t].ss * r.v[t + 1][j].cnt % MOD + l.v[i][t].s * r.v[t + 1][j].s % MOD * 2 + l.v[i][t].cnt * r.v[t + 1][j].ss % MOD) % MOD;
                }   
            }
        }
    }
    return tmp;
}

info init(int start, int end, int ind) {
    if (start == end) {
        char c = S[end - 1];
        for (int j = 0; j < 6; j++) {
            if (c <= matkor[j]) {
                tree[ind].v[j][j].cnt = 1;
                tree[ind].v[j][j].s = matkor[j] - c;
                tree[ind].v[j][j].ss = (ll)(matkor[j] - c) * (ll)(matkor[j] - c);
            }
            else tree[ind].v[j][j].cnt = tree[ind].v[j][j].s = tree[ind].v[j][j].ss = 0;
        }
        return tree[ind];
    }
    int mid = (start + end) / 2;
    info l = init(start, mid, ind * 2), r = init(mid + 1, end, ind * 2 + 1);
    return tree[ind] = cal(start, end, mid, l, r);
}

info update(int start, int end, int ind, int i, char c) {
    if (i < start || end < i) return tree[ind];
    if (start == end) {
        S[end - 1] = c;
        for (int j = 0; j < 6; j++) {
            if (c <= matkor[j]) {
                tree[ind].v[j][j].cnt = 1;
                tree[ind].v[j][j].s = matkor[j] - c;
                tree[ind].v[j][j].ss = (ll)(matkor[j] - c) * (ll)(matkor[j] - c);
            }
            else tree[ind].v[j][j].cnt = tree[ind].v[j][j].s = tree[ind].v[j][j].ss = 0;
        }
        return tree[ind];
    }
    int mid = (start + end) / 2;
    info l = update(start, mid, ind * 2, i, c), r = update(mid + 1, end, ind * 2 + 1, i, c);
    return tree[ind] = cal(start, end, mid, l, r);
}

info res(int start, int end, int ind, int le, int ri) {
    if (ri < start || end < le) return nono;
    if (le <= start && end <= ri) return tree[ind];
    int mid = (start + end) / 2;
    info l = res(start, mid, ind * 2, le, ri), r = res(mid + 1, end, ind * 2 + 1, le, ri);
    if (mid < le) return r;
    if (ri <= mid) return l;
    return cal(max(start, le), min(end, ri), mid, l, r);
}

ll pow_fast(ll a, ll b) {
    ll ret = 1;
	while (b){
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll a, b, c, i; char d; cin >> S >> q;
    n = S.size();
    init(1, n, 1);
    while (q--) {
        cin >> a >> b;
        if (a == 1) {
            cin >> d;
            update(1, n, 1, b, d);
        }
        else {
            cin >> c;
            info tmp = res(1, n, 1, b, c);
            ll cnt = tmp.v[0][5].cnt, s = tmp.v[0][5].s, ss = tmp.v[0][5].ss;
            ll ans = ((cnt * ss % MOD - s * s % MOD) % MOD + MOD) % MOD;
            cout << cnt << ' '; 
            if (cnt != 0) cout << ans * pow_fast(cnt * cnt % MOD, MOD - 2) % MOD << '\n';
            else cout << '\n';
        }
    }
}
